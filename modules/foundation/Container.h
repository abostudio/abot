#ifndef ABOT_FOUNDATION_CONTAINER_H
#define ABOT_FOUNDATION_CONTAINER_H

#include "Abot/Foundation.h"

namespace Abot {

	
	class Container : public std::enable_shared_from_this <Container> {
	private:
		
	private:
		
		
	public:
		static std::shared_ptr<Container> Create() {
			std::shared_ptr<Container> container;

			container = std::shared_ptr<Container>(new Container());

			return container;
		}
			

	};
}


#endif //ABOT_FOUNDATION_CONTAINER_H