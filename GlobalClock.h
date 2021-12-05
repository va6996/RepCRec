//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_GLOBALCLOCK_H
#define REPCREC_GLOBALCLOCK_H


class GlobalClock {
	static int time;

public:
		GlobalClock();

		void tick() {
			time++;
		}

		static int getTime() {
			return time;
		}
};


#endif //REPCREC_GLOBALCLOCK_H
