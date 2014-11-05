#ifndef ABOT_FOUNDATION_COMPONENT_H
#define ABOT_FOUNDATION_COMPONENT_H

#include "Abot/Foundation.h"

namespace Abot {


	class Component {
		friend class Node;
	private:
		std::vector<NodePtr> targets;
		std::shared_ptr<Signal<ComponentPtr, NodePtr>> onTargetAdded;
		std::shared_ptr<Signal<ComponentPtr, NodePtr>> onTargetRemoved;

	private:


	public:
		inline std::vector<NodePtr> GetTargets() const {
			return targets;
		}

		inline uint32_t GetTargetsCount() const {
			return targets.size();
		}

		inline NodePtr GetTarget(uint32_t index) const {
			return targets[index];
		}

		inline std::shared_ptr<Signal<ComponentPtr, NodePtr>> OnTargetAdded() {
			return onTargetAdded;
		}

		inline std::shared_ptr<Signal<ComponentPtr, NodePtr>> OnTargetRemoved() {
			return onTargetRemoved;
		}	

		inline std::shared_ptr<Signal<ComponentPtr, NodePtr>> OnTargetAdded() const {
			return onTargetAdded;
		}

		inline std::shared_ptr<Signal<ComponentPtr, NodePtr>> OnTargetRemoved() const {
			return onTargetRemoved;
		}

	private:
	public:
		Component() :
			onTargetAdded(Signal<ComponentPtr, NodePtr>::Create()),
			onTargetRemoved(Signal<ComponentPtr, NodePtr>::Create()) {

		}
		virtual ~Component() = 0;

		
	};

	
}


#endif //ABOT_FOUNDATION_COMPONENT_H