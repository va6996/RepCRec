//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_GLOBALCLOCK_H
#define REPCREC_GLOBALCLOCK_H

#include "iostream"

using namespace std;

/**
 * Class representing global synchronized clock used by all managers
 */
class GlobalClock {
public:
		static int time;

		/**
		 * Increase the time by 1 unit
		 */
		static void tick() {
			time++;
			cout << "---------------Time " << time << "---------------\n";
		}

		/**
		 * Get current value of time
		 * @return the result
		 */
		static int getTime() {
			return time;
		}
};


#endif //REPCREC_GLOBALCLOCK_H
