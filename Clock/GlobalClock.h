//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_GLOBALCLOCK_H
#define REPCREC_GLOBALCLOCK_H

#include "iostream"

using namespace std;

class GlobalClock {
public:
		static int time;

		static void tick() {
			time++;
			cout << "---------------Time " << time << "---------------\n";
		}

		static int getTime() {
			return time;
		}
};


#endif //REPCREC_GLOBALCLOCK_H
