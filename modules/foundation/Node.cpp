#include "Node.h"
#include "Container.h"
#include "SignalSlot.h"
#include "Group.h"
#include "Component.h"

namespace Abot { 

	uint32_t Node::id = 0;

	Node::Node() :
		name("Node_" + std::to_string(Node::id++)),
		layouts(1),
		root(nullptr),
		parent(nullptr),
		container(Container::Create()),
		onNodeAdded(Signal<NodePtr, NodePtr, NodePtr>::Create()),
		onNodeRemoved(Signal<NodePtr, NodePtr, NodePtr>::Create()),
		onComponentAdded(Signal<NodePtr, NodePtr, ComponentPtr>::Create()),
		onComponentRemoved(Signal<NodePtr, NodePtr, ComponentPtr>::Create()),
		onLayoutsChanged(Signal<NodePtr, NodePtr>::Create()){
	}

	void Node::SetLayouts(uint32_t layouts) {
		if (this->layouts != layouts) {
			this->layouts = layouts;

			// bubble down
			auto descendants = Group::Create(shared_from_this())->GetDescendants(true);
			for (auto descendant : descendants->GetNodes()) {
				descendant->onLayoutsChanged->Execute(descendant, shared_from_this());
			}

			// bubble up
			auto ancestors = Group::Create(shared_from_this())->GetAncestors();
			for (auto ancestor : ancestors->GetNodes()) {
				ancestor->onLayoutsChanged->Execute(ancestor, shared_from_this());
			}
		}
	}

	NodePtr Node::AddNode(NodePtr node){
		if (node->parent)
			node->parent->RemoveNode(node);

		nodes.push_back(node);

		node->parent = shared_from_this();
		node->UpdateRoot();

		// bubble down
		auto descendants = Group::Create(node)->GetDescendants(true);
		for (auto descendant : descendants->GetNodes())
			descendant->onNodeAdded->Execute(descendant, node, shared_from_this());

		// bubble up
		auto ancestors = Group::Create(shared_from_this())->GetAncestors(true);
		for (auto ancestor : ancestors->GetNodes())
			ancestor->onNodeAdded->Execute(ancestor, node, shared_from_this());

		return shared_from_this();
	}

	NodePtr Node::RemoveNode(NodePtr node) {
		auto it = std::find(nodes.begin(), nodes.end(), node);

		if (it == nodes.end())
			throw std::invalid_argument("node");

		nodes.erase(it);

		node->parent = nullptr;
		node->UpdateRoot();

		// bubble down
		auto descendants = Group::Create(node)->GetDescendants(true);
		for (auto descendant : descendants->GetNodes())
			descendant->onNodeRemoved->Execute(descendant, node, shared_from_this());

		// bubble up
		auto ancestors = Group::Create(shared_from_this())->GetAncestors(true);
		for (auto ancestor : ancestors->GetNodes())
			ancestor->onNodeRemoved->Execute(ancestor, node, shared_from_this());

		return shared_from_this();
	}

	NodePtr	Node::RemoveAllNodes() {
		int numNodes = nodes.size();

		for (int i = numNodes - 1; i >= 0; --i)
			RemoveNode(nodes[i]);

		return shared_from_this();
	}

	bool Node::HasNode(NodePtr node) {
		return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
	}

	NodePtr Node::AddComponent(ComponentPtr component) {
		if (!component)
			throw std::invalid_argument("component");

		if (HasComponent(component))
			throw std::logic_error("The same component cannot be added twice.");

		components.push_back(component);
		
		component->targets.push_back(shared_from_this());

		component->OnTargetAdded()->Execute(component, shared_from_this());

		// bubble down
		auto descendants = Group::Create(shared_from_this())->GetDescendants(true);
		for (auto descendant : descendants->GetNodes())
			descendant->onComponentAdded->Execute(descendant, shared_from_this(), component);

		// bubble up
		auto ancestors = Group::Create(shared_from_this())->GetAncestors();
		for (auto ancestor : ancestors->GetNodes())
			ancestor->onComponentAdded->Execute(ancestor, shared_from_this(), component);

		return shared_from_this();
	}

	NodePtr Node::RemoveComponent(ComponentPtr component)
	{
		if (!component)
			throw std::invalid_argument("component");

		std::list<ComponentPtr>::iterator it = std::find(
			components.begin(), components.end(), component
			);

		if (it == components.end())
			throw std::invalid_argument("component");

		components.erase(it);
		component->targets.erase(
			std::find(component->targets.begin(), component->targets.end(), shared_from_this())
			);

		component->onTargetRemoved->Execute(component, shared_from_this());

		// bubble down
		auto descendants = Group::Create(shared_from_this())->GetDescendants(true);
		for (auto descendant : descendants->GetNodes())
			descendant->onComponentRemoved->Execute(descendant, shared_from_this(), component);

		// bubble up
		auto ancestors = Group::Create(shared_from_this())->GetAncestors();
		for (auto ancestor : ancestors->GetNodes())
			ancestor->onComponentRemoved->Execute(ancestor, shared_from_this(), component);

		return shared_from_this();
	}

	bool Node::HasComponent(ComponentPtr component)
	{
		return std::find(components.begin(), components.end(), component) != components.end();
	}

	void Node::UpdateRoot()
	{
		root = parent ? (parent->root ? parent->root : parent) : shared_from_this();
		depth = parent ? parent->depth + 1 : 0;

		for (auto child : nodes)
			child->UpdateRoot();
	}
}