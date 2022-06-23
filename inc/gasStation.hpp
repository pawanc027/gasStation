#ifndef GASSTATION_HPP
#define GASSTATION_HPP

#include <vehicle.hpp>
#include <pump.hpp>

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

namespace ExxonMobil {

	class GasStation {

		public:
			GasStation(unsigned int max_run_time = 1);
			~GasStation();

		protected:
			void run();
			void fillUpService(Vehicle& car);
			void fillUpServiceHelper(Pump& pump,Vehicle& car);
			void generate_report() const;

		private:
			unsigned int mScenarioTime;
			std::vector<std::thread> queue;
			Vehicle mCar[MAX_VEHICLES];
			Pump mPump[MAX_PUMPS];
			std::mutex  mMutexBuffer, mMutexTurn;
			std::condition_variable mCondVar;
			std::atomic<bool> mStop;
	};

} /* End of namespace ExxonMobil */

#endif
