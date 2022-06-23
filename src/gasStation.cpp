#include <gasStation.hpp>

namespace ExxonMobil {

	GasStation::GasStation(unsigned int max_run_time) : mScenarioTime(max_run_time), mStop(false) {
		queue.reserve(MAX_VEHICLES);
		for(size_t x=0;x < MAX_VEHICLES;++x) {
			queue.emplace_back([this,x] { fillUpService(this->mCar[x]); }); /* Create Car Thread and Add it to Car Lane */
		} 
		run();
	}

	GasStation::~GasStation() {
		for( auto& car_th: queue) {
			if(car_th.joinable()) {
				car_th.join(); /* Join the car thread */
			}
		}   
	}

	void GasStation::run() {
		std::this_thread::sleep_for(std::chrono::seconds(mScenarioTime));
		mStop = true; /* Stop all running threads */
		mCondVar.notify_all();
		generate_report();
	}

	void GasStation::fillUpService(Vehicle& car) {
		while(!mStop) {
			if(car.checkTurn(queue.front())) {
				if(mPump[0].getAvailability()) {
					mPump[0].setAvalability(false);
					fillUpServiceHelper(mPump[0],car);
				}
				else if(mPump[1].getAvailability()) {
					mPump[1].setAvalability(false);
					fillUpServiceHelper(mPump[1],car);

				}
			} else {
				std::unique_lock<std::mutex> lock(mMutexTurn);
				mCondVar.wait(lock, [this,&car](){ return (mStop || car.checkTurn(queue.front())); });
			}
		}
	}


	void GasStation::fillUpServiceHelper(Pump& pump,Vehicle& car) {
		if(mStop) 
			return;

		{
			std::lock_guard<std::mutex> lck (mMutexBuffer);
			car.rejoinLane(queue);
		}

		mCondVar.notify_all();
		car.fillGas();
		pump.setAvalability(true);
		mCondVar.notify_all();
		car.addFillUpCnt();
		pump.addFillUpCnt();
	}

	void GasStation::generate_report() const {
		std::cout << "Scenario Time:\t" << mScenarioTime << " seconds\n\n";
		std::cout << "Car\t" << "FillUp Count" << "\n";  /* Generate report for each car and it's fillUp count */
		for(size_t x=0;x<MAX_VEHICLES;++x) {
			std::cout << x+1 << "\t" << mCar[x].getFillUpCnt() << "\n";
		}

		std::cout<<"\n";

		std::cout << "Pump\t" << "FillUp Count" << std::endl; /* Generate report for each pump and it's fillUp count */
		for(size_t x=0;x<MAX_PUMPS;++x) {
			std::cout << x+1  << "\t" << mPump[x].getFillUpCnt() << "\n";
		}
	}

} /* End of namespace ExxonMobil */

int main(int argc, const char** argv) {
	ExxonMobil::GasStation sample(30);
	return 0;
}
