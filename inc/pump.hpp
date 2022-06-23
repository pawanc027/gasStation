#ifndef PUMP_HPP
#define PUMP_HPP

#include <iostream>
#include <atomic>

namespace ExxonMobil {

	static const size_t MAX_PUMPS = 2;

	class Pump {

		public:
			Pump():mPumpFillUpCnt(0),mAvailable(true) { 
			}

			~Pump() { }

			void   addFillUpCnt() { ++mPumpFillUpCnt; }
			void   setAvalability(bool value) { mAvailable = value; }

			size_t getFillUpCnt() const { return mPumpFillUpCnt; }
			bool   getAvailability() const { return mAvailable; }

		private:
			std::atomic<unsigned int> mPumpFillUpCnt;
			std::atomic<bool>   mAvailable;

	};

} /* End of namespace ExxonMobil */

#endif
