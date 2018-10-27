#include <stdio.h>
using namespace std;

int main () {
	double charge_table[5][3] = {{0.10, 0.06, 0.02},
							  {0.25, 0.15, 0.05},
							  {0.53, 0.33, 0.13},
							  {0.87, 0.47, 0.17},
							  {1.44, 0.80, 0.30}};
	int time_zone[24] = {2, 2, 2, 2, 2, 2, 2, 2,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 1, 1, 1, 1,
						 2, 2};
	
	char charge_step[10], phone_number[10];
	int start_hour, start_minute, end_hour, end_minute;
	
	while (scanf ("%s", charge_step) != EOF) {
		if (charge_step[0] == '#')
			break;
		
		scanf ("%s%d%d%d%d", phone_number, &start_hour, &start_minute, &end_hour, &end_minute);
		
		int time_spent[3]={0};
		if (start_hour == end_hour) {
			if (start_minute < end_minute) {
				if (start_hour >= 8 && start_hour <= 17)
					time_spent[0] = end_minute-start_minute;
				else if (start_hour >= 18 && start_hour <= 21)
					time_spent[1] = end_minute-start_minute;
				else
					time_spent[2] = end_minute-start_minute;
			}
			else {
				if (start_hour >= 8 && start_hour <= 17)
					time_spent[0] = (60-start_minute) + end_minute;
				else if (start_hour >= 18 && start_hour <= 21)
					time_spent[1] = (60-start_minute) + end_minute;
				else
					time_spent[2] = (60-start_minute) + end_minute;
			}
		}
		else {
			if (start_hour >= 8 && start_hour <= 17)
				time_spent[0] += 60-start_minute;
			else if (start_hour >= 18 && start_hour <= 21)
				time_spent[1] += 60-start_minute;
			else
				time_spent[2] += 60-start_minute;
			
			if (end_hour >= 8 && end_hour <= 17)
				time_spent[0] += end_minute;
			else if (end_hour >= 18 && end_hour <= 21)
				time_spent[1] += end_minute;
			else
				time_spent[2] += end_minute;
		}
		
		if ((start_hour < end_hour) || (start_hour == end_hour && start_minute < end_minute)) {
			for (int i=start_hour+1; i<end_hour; i++) {
				time_spent[time_zone[i]] += 60;
			}
		}
		else {
			for (int i=start_hour+1; i<24; i++) {
				time_spent[time_zone[i]] += 60;
			}
			for (int i=0; i<end_hour; i++) {
				time_spent[time_zone[i]] += 60;
			}
		}
		
		int charge_step_position = charge_step[0]-'A';
		double cost = time_spent[0]*charge_table[charge_step_position][0]
					+ time_spent[1]*charge_table[charge_step_position][1]
					+ time_spent[2]*charge_table[charge_step_position][2];
		
		printf ("%10s%6d%6d%6d%3s%8.2f\n", phone_number, time_spent[0], time_spent[1], time_spent[2], charge_step, cost);
	}

	return 0;
}