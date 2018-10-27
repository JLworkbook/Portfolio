#include <stdio.h>

int main() {
	int i;
	
	int bin[9], bin_sum;
	char glass_class[6][4] = {{"BCG"},{"BGC"},{"CBG"},{"CGB"},{"GBC"},{"GCB"}};
	int move_bin_times[6], temp_max, max_index;
	while (scanf("%d", &bin[0]) != EOF) {
		for (i=1; i<9; i++) {
			scanf("%d", &bin[i]);
		}
		
		bin_sum = 0;
		for (i=0; i<9; i++)
			bin_sum += bin[i];
			
		move_bin_times[0] = bin[0]+bin[5]+bin[7];
		move_bin_times[1] = bin[0]+bin[4]+bin[8];
		move_bin_times[2] = bin[2]+bin[3]+bin[7];
		move_bin_times[3] = bin[2]+bin[4]+bin[6];
		move_bin_times[4] = bin[1]+bin[3]+bin[8];
		move_bin_times[5] = bin[1]+bin[5]+bin[6];
		
		temp_max = 0;
		max_index = 0;
		for (i=0; i<6; i++) {
			if (temp_max < move_bin_times[i]) {
				max_index = i;
				temp_max = move_bin_times[i];
			}
		}
		printf ("%s %d\n", glass_class[max_index], bin_sum-move_bin_times[max_index]);
	}
	
	return 0;
}