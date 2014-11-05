
#ifndef ABOT_FOUNDATION_DEFINED
#define ABOT_FOUNDATION_DEFINED

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <signal.h>
#include <direct.h>
#include <inttypes.h>

#include <cstddef>
#include <ctime>
#include <cstring>
#include <string>
#include <memory>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <thread>
#include <fstream>
#include <exception>
#include <algorithm>  

#include <array>
#include <cmath>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <forward_list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <ctime>
#include <type_traits>
#include <cfloat>
#include <climits>
#include <future>
#include <thread>
#include <chrono>


namespace Abot {

	template <typename T>
	class Convertible {
	public:
		typedef std::shared_ptr<Convertible> Ptr;

	public:

		bool
			equal(std::shared_ptr<T> convertible) {
			return false;
		}
	};

	template <typename T>
	inline
		typename std::enable_if<std::is_convertible<T, Convertible<T>>::value, bool>::type
		operator==(std::shared_ptr<T> &first,
		std::shared_ptr<T> &other) {
		return first->equals(other);
	}

	template <typename T>
	inline
		typename std::enable_if<std::is_convertible<T, Convertible<T>>::value, bool>::type
		operator!=(std::shared_ptr<T> &first,
		std::shared_ptr<T> &other) {
		return !(first->equals(other));
	}

	template <typename... A>
	class Signal;

	

	class Container;

	class Application;

	class Scene;

	class Component;

	class Node;

	class Group;
	
	typedef std::shared_ptr<Scene>													ScenePtr;
	typedef std::shared_ptr<Node>													NodePtr;
	typedef std::shared_ptr<Component>												ComponentPtr;


	typedef std::shared_ptr<Container>						ContainerPtr;

	typedef std::shared_ptr<Group> GroupPtr;
	
	class Application {
	public:
		static void Start(int width = 800, int height = 600);

	};
}


template<typename T>
std::shared_ptr<T>
operator*(std::shared_ptr<T> a, float b) {
	return (*a) * b;
}

template<typename T>
std::shared_ptr<T>
operator*(std::shared_ptr<T> a, std::shared_ptr<T> b) {
	return *a * b;
}

template<typename T>
std::shared_ptr<T>
operator-(std::shared_ptr<T> a, std::shared_ptr<T> b) {
	return *a - b;
}

template<typename T>
std::shared_ptr<T>
operator+(std::shared_ptr<T> a, std::shared_ptr<T> b) {
	return *a + b;
}

template<typename T>
std::shared_ptr<T>
operator/(std::shared_ptr<T> a, std::shared_ptr<T> b) {
	return *a / b;
}

template<typename T>
std::shared_ptr<T>
operator*=(std::shared_ptr<T> a, std::shared_ptr<T> b) {
	return *a *= b;
}

template<typename T>
std::shared_ptr<T>
operator+=(std::shared_ptr<T> a, std::shared_ptr<T> b) {
	return *a += b;
}

template<typename T>
std::shared_ptr<T>
operator-=(std::shared_ptr<T> a, std::shared_ptr<T> b) {
	return *a -= b;
}

namespace std
{
	template <class T>
	inline
		void
		hash_combine(std::size_t & seed, const T& v) {
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
}

#endif //ABOT_FOUNDATION_DEFINED

