#ifndef ABOT_FOUNDATION_GROUP_H
#define ABOT_FOUNDATION_GROUP_H

#include "Abot/Foundation.h"


namespace Abot {


	class Group : public std::enable_shared_from_this <Group> {
	private:
		std::vector <NodePtr> nodes;

	public:
		inline static GroupPtr Create(const std::list<NodePtr>& nodes) {
			GroupPtr group;

			group = Create();
			group->nodes.insert(group->nodes.end(), nodes.begin(), nodes.end());

				return group;
		}
		inline static GroupPtr Create(const std::vector<NodePtr>& nodes) {
			GroupPtr group;

			group = Create();
			group->nodes.insert(group->nodes.end(), nodes.begin(), nodes.end());

			return group;
		}
		inline static GroupPtr Create(NodePtr node) {
			GroupPtr group;

			group = Create();
			group->nodes.push_back(node);

			return group;
		}
		inline static GroupPtr Create() {
			GroupPtr group;

			group = std::shared_ptr<Group>(new Group());

			return group;
		}
		inline const std::vector <NodePtr> GetNodes() {
			return nodes;
		}

		GroupPtr GetDescendants(bool andSelf = false, bool depthFirst = true, GroupPtr group = nullptr);

		GroupPtr GetAncestors(bool andSelf = false, GroupPtr group = nullptr);

		GroupPtr GetChildren(bool andSelf = false, GroupPtr group = nullptr);

		GroupPtr GetGroupFrom(std::function<bool(NodePtr)> filter, GroupPtr group = nullptr);

		GroupPtr GetRoots(GroupPtr group = nullptr);

	private:
		Group() : nodes() {

		}

	};

}


#endif //ABOT_FOUNDATION_GROUP_H