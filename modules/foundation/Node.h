#ifndef ABOT_FOUNDATION_NODE_H
#define ABOT_FOUNDATION_NODE_H

#include "Abot/Foundation.h"

namespace Abot {	

	class Node : public std::enable_shared_from_this<Node> {
	protected:
		std::string name;
		std::vector<std::shared_ptr<Node>> nodes;

	private:
		static uint32_t id;
		uint32_t layouts;
		uint32_t depth;
		NodePtr root;
		NodePtr parent;
		ContainerPtr container;
		std::list<ComponentPtr> components;

		std::shared_ptr<Signal<NodePtr, NodePtr, NodePtr>> onNodeAdded;
		std::shared_ptr<Signal<NodePtr, NodePtr, NodePtr>> onNodeRemoved;
		std::shared_ptr<Signal<NodePtr, NodePtr>> onLayoutsChanged;
		std::shared_ptr<Signal<NodePtr, NodePtr, ComponentPtr>> onComponentAdded;
		std::shared_ptr<Signal<NodePtr, NodePtr, ComponentPtr>> onComponentRemoved;

	public:
		static NodePtr Create() {
			NodePtr node;
			
			node = std::shared_ptr<Node>(new Node());
			node->root = node;


			return node;
		}

		static NodePtr Create(const std::list<NodePtr>& children) {
			NodePtr node;

			node = Create();

			for (auto child : children) {
				node->AddNode(child);
			}

			return node;
		}

		static NodePtr Create(const std::string& name) {
			NodePtr node;

			node = Create();
			node->SetName(name);

		}

		inline const std::string& GetName() const {
			return name;
		}

		inline void SetName(const std::string& name) {
			this->name = name;
		}

		inline uint32_t GetLayouts() const {
			return layouts;
		}

		inline void SetLayouts(uint32_t layouts);

		inline NodePtr GetParent() const {
			return parent;
		}

		inline NodePtr GetRoot() const {
			return root;
		}

		inline ContainerPtr  GetData() const {
			return container;
		}

		inline std::shared_ptr<Signal<NodePtr, NodePtr, NodePtr>> OnNodeAdded() const {
			return onNodeAdded;
		}

		inline std::shared_ptr<Signal<NodePtr, NodePtr, NodePtr>> OnNodeRemoved() const {
			return onNodeRemoved;
		}

		inline std::shared_ptr<Signal<NodePtr, NodePtr>> OnLayoutsChanged() const {
			return onLayoutsChanged;
		}

		inline std::shared_ptr<Signal<NodePtr, NodePtr, ComponentPtr>> OnComponentAdded() const {
			return onComponentAdded;
		}

		inline std::shared_ptr<Signal<NodePtr, NodePtr, ComponentPtr>> OnComponentRemoved() const {
			return onComponentRemoved;
		}

		inline const std::vector<NodePtr>& GetNodes() const {
			return nodes;
		}
		NodePtr AddNode(NodePtr node);

		NodePtr RemoveNode(NodePtr node);

		NodePtr RemoveAllNodes();

		bool HasNode(NodePtr node);

		NodePtr AddComponent(ComponentPtr component);

		NodePtr RemoveComponent(ComponentPtr component);

		bool HasComponent(ComponentPtr component);

		template<typename T>
		inline bool HasComponent() {
			return compoent<T>() != nullptr;
		}

		template <typename T>
		std::vector<std::shared_ptr<T>> GetComponents() {
			std::vector<std::shared_ptr<T>> results;

			for (auto component : components)
			{
				std::shared_ptr<T> typedComponent = std::dynamic_pointer_cast<T>(component);

				if (typedComponent != nullptr)
					results.push_back(typedComponent);
			}

			return results;
		}
		template <typename T>
		std::vector<std::shared_ptr<T>> GetComponent(const uint32_t index = 0) {
			unit32_t counter;

			counter = 0;
			for (auto component : _components)
			{
				std::shared_ptr<T> typedComponent = std::dynamic_pointer_cast<T>(component);

				if (typedComponent != nullptr)
				{
					if (counter == index)
						return typedComponent;
					else
						++counter;
				}
			}

			return nullptr;
		}

		virtual ~Node(){
		}

		protected:
			Node();

			void UpdateRoot();
	};

}
#endif //ABOT_FOUNDATION_NODE_H