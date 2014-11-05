#ifndef ABOT_FOUNDATION_SIGNAL_H
#define ABOT_FOUNDATION_SIGNAL_H

#include "Abot/Foundation.h"

namespace Abot {

	template<typename... A>
	class Signal : public std::enable_shared_from_this <Signal<A...> > {
	private:
		template <typename... B>
		class SignalSlot;

	public:
		typedef std::shared_ptr<Signal<A...>>			SignalPtr;
		typedef std::shared_ptr<SignalSlot<A...>>		SignalSlotPtr;

	private:
		typedef std::function<void(A...)> CallbackFunction;
		typedef std::pair<float, CallbackFunction> Callback;
		typedef typename std::list<Callback>::iterator CallbackIterator;
		typedef typename std::list<std::pair<float, uint32_t>>::iterator SlotIterator;

		std::list<Callback> callbacks;
		std::list<std::pair<float, uint32_t>> slotIds;
		uint32_t nextSlotId;

		bool locked;
		std::list<std::pair<Callback, uint32_t>> toAdd;
		std::list<std::pair<CallbackIterator, SlotIterator>> toRemove;
		std::list<uint32_t> toRemoveSlotId;
		bool signalListDirty;

	public:
		
	private:
		Signal() : std::enable_shared_from_this<Signal<A...>>(),
			nextSlotId(0),
			locked(false),
			signalListDirty(false) {

		}

		void RemoveConnectionById(const uint32_t connectionId) {
			auto connectionIdIt = slotIds.begin();
			auto callbackIt = callbacks.begin();

			while ((*connectionIdIt).second != connectionId)
			{
				connectionIdIt++;
				callbackIt++;
			}

			RemoveConnectionByIterator(connectionIdIt, callbackIt);
		}

		void RemoveConnectionByIterator(SlotIterator connectionIdIt, CallbackIterator callbackIt) {
			if (locked) {
				auto addIt = std::find_if(toAdd.begin(), toAdd.end(), [&](std::pair<Callback, uint32_t>& add) {
					return add.second == (*connectionIdIt).second;
				});

				if (addIt != toAdd.end()) {
					toAdd.erase(addIt);
				} else {
					toRemove.push_back(std::pair<CallbackIterator, SlotIterator>(callbackIt, connectionIdIt));
					toRemoveSlotId.push_back(connectionIdIt->second);
				}
			} else {
				callbacks.erase(callbackIt);
				slotIds.erase(connectionIdIt);
			}
		}

	public:
		static SignalPtr Create() {
			return std::shared_ptr<Signal<A...>>(new Signal<A...>());
		}

		inline uint32_t	GetCallbacksCount() const {
			return callbacks.size();
		}

		void SortSignals() {
			callbacks.sort([&](const Callback& callback1, const Callback& callback2) -> bool {
				return callback1.first > callback2.first;
			});

			slotIds.sort([&](const std::pair<float, uint32_t>& slot1, const std::pair<float, uint32_t>& slot2) -> bool {
				return slot1.first > slot2.first;
			});
		}

		SignalSlotPtr Connect(CallbackFunction callback, float priority = 0) {
			auto connection = SignalSlot<A...>::Create(Signal<A...>::shared_from_this(), nextSlotId++);
			
			if (locked) {
				toAdd.push_back(std::pair<Callback, uint32_t>(std::pair<float, CallbackFunction>(priority, callback), connection->id));
			} else {
				callbacks.push_back(std::pair<float, CallbackFunction>(priority, callback));
				slotIds.push_back(std::pair<float, uint32_t>(priority, connection->id));

				if (callbacks.size() >= 2) {
					auto prec = std::prev(callbacks.end(), 2);

					if (priority > prec->first)
						SortSignals();
				}
			}
			
			return connection;
		}

		void Execute(A... arguments) {
			locked = true;
			for (auto& callback : callbacks)
				callback.second(arguments...);
			locked = false;

			for (auto& callbackIt : toRemove) {
				callbacks.erase(callbackIt.first);
				slotIds.erase(callbackIt.second);
			}

			for (auto& callbackAndConnectionId : toAdd) {

				callbacks.push_back(callbackAndConnectionId.first);
				slotIds.push_back(std::pair<float, uint32_t>(callbackAndConnectionId.first.first, callbackAndConnectionId.second));

				if (callbacks.size() >= 2) {
					auto prec = std::prev(callbacks.end(), 2);

					if (callbackAndConnectionId.first.first > prec->first)
						signalListDirty = true;
				}
			}

			if (signalListDirty) {
				signalListDirty = false;
				SortSignals();
			}

			toAdd.clear();
			toRemove.clear();
		}

		private:
			template <typename... T>
			class SignalSlot : public std::enable_shared_from_this<SignalSlot<T...>> {
				friend class Signal<T...>;

			public:
				typedef std::shared_ptr<SignalSlot<T...>>	SignalSlotPtr;

			public:
				std::shared_ptr<Signal<T...>> GetSignal() {
					return signal;
				}

				void Disconnect() {
					if (signal != nullptr) {
						signal->RemoveConnectionById(id);
						signal = nullptr;
					}
				}

				~SignalSlot() {
					Disconnect();
				}

			private:
				std::shared_ptr<Signal<T...>>	signal;
				const uint32_t				id;

			private:
				inline static SignalSlotPtr Create(std::shared_ptr<Signal<T...>> signal, const uint32_t id) {
					return std::shared_ptr<SignalSlot<T...>>(new SignalSlot(signal, id));
				}

				SignalSlot(std::shared_ptr<Signal<T...>> signal, const uint32_t id) :
					signal(signal),
					id(id) {
				}
			};



	};
}


#endif //ABOT_FOUNDATION_SIGNAL_H