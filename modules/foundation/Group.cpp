#include "Group.h"
#include "Node.h"

namespace Abot {

	GroupPtr Group::GetDescendants(bool andSelf, bool depthFirst, GroupPtr group) {
		if (group == nullptr) {
			group = Create();
		}

		std::list<NodePtr> nodesStack;

		for (auto node : nodes) {
			nodesStack.push_front(node);

			while (nodesStack.size() != 0) {
				auto descendant = nodesStack.front();

				nodesStack.pop_front();

				if (descendant != node || andSelf) {
					group->nodes.push_back(descendant);
				}

				nodesStack.insert(
					depthFirst ? nodesStack.begin() : nodesStack.end(),
					descendant->GetNodes().begin(),
					descendant->GetNodes().end()
					);
			}
		}

		return group;
	}

	GroupPtr Group::GetAncestors(bool andSelf, GroupPtr group) {
		if (group == nullptr) {
			group = Create();
		}
		for (auto node : nodes) {
			if (andSelf)
				group->nodes.push_back(node);

			while (node != nullptr) {
				if (node->GetParent() != nullptr)
					group->nodes.push_back(node->GetParent());
				node = node->GetParent();
			}
		}

		return group;
	}

	GroupPtr Group::GetChildren(bool andSelf, GroupPtr group) {
		if (group == nullptr) {
			group = Create();
		}

		for (auto node : nodes) {
			if (andSelf)
				group->nodes.push_back(node);

			group->nodes.insert(group->nodes.end(), node->GetNodes().begin(), node->GetNodes().end());
		}

		return group;
	}

	GroupPtr Group::GetGroupFrom(std::function<bool(std::shared_ptr<Node>)> filter, GroupPtr group) {
		if (group == nullptr)
			group = Create();

		for (auto node : nodes) {
			if (filter(node)) {
				group->nodes.push_back(node);
			}
		}
		return group;
	}

	GroupPtr Group::GetRoots(GroupPtr group) {
		if (group == nullptr)
			group = Create();

		for (auto node : nodes)
			if (std::find(group->nodes.begin(), group->nodes.end(), node->GetRoot()) == group->nodes.end())
				group->nodes.push_back(node->GetRoot());

		return group;
	}

}
