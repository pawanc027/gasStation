#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>

namespace ExxonMobil {

	static const size_t MAX_VEHICLES = 10;
	static const size_t FILLUP_TIME = 30;  /* FillUp time in milliseconds */

	class Vehicle {

		public:
			Vehicle():mVehicleFillUpCnt(0) { 
			}

			~Vehicle() { }

			void   addFillUpCnt() { ++mVehicleFillUpCnt; }
			size_t getFillUpCnt() const { return mVehicleFillUpCnt; }
			bool checkTurn(const std::thread& top) const { return (top.get_id() == std::this_thread::get_id());} /* Check if it's the vehicle turn for FillUp */
			void fillGas() const { std::this_thread::sleep_for(std::chrono::milliseconds(FILLUP_TIME)); } /* Vehicle FillUp time */
			void rejoinLane(std::vector<std::thread>& threads) {  /* Post FillUp, The car re-join the lane */
				std::rotate(threads.begin(),threads.begin()+1,threads.end()); /* Post FillUp, The car re-join the lane */
			}

		private:
			std::atomic<unsigned int> mVehicleFillUpCnt;
	};
} /* End of namespace ExxonMobil */

#endif
