#include <stdio.h>
#include <string.h>
using namespace std;

#define WORLDSIZE 52

int main () {
	int i;
	
	int world[WORLDSIZE][WORLDSIZE]={0};
	int move[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};
	char direction_word[5] = "NWSE";
	
	int world_width, world_height;
	scanf ("%d%d", &world_width, &world_height);
	
	int now_x, now_y, now_direction;
	int tmp_x, tmp_y;
	char tmp_char[2];
	char instruction[1002];
	while (scanf ("%d%d%s", &now_x, &now_y, tmp_char) != EOF) {
		switch (tmp_char[0]) {
			case 'N': now_direction=0; break;
			case 'W': now_direction=1; break;
			case 'S': now_direction=2; break;
			case 'E': now_direction=3; break;
			default: break;
		}
		
		scanf ("%s", instruction);
		int lost_flag = 0;
		for (i=0; i<strlen(instruction); i++) {
			if (instruction[i] == 'F') {
				tmp_x = now_x + move[now_direction][0];
				tmp_y = now_y + move[now_direction][1];
				if (tmp_x < 0 || tmp_x > world_width || tmp_y < 0 || tmp_y > world_height) {
					if (world[now_x][now_y])
						continue;
					else {
						lost_flag = 1;
						world[now_x][now_y] = 1;
						break;
					}
				}
				else {
					now_x = tmp_x;
					now_y = tmp_y;
				}
			}
			else if (instruction[i] == 'L') {
				now_direction = (now_direction+1)%4;
			}
			else if (instruction[i] == 'R') {
				now_direction = (now_direction-1+4)%4;
			}
		}
		
		printf ("%d %d %c", now_x, now_y, direction_word[now_direction]);
		if (lost_flag)
			printf (" LOST");
		printf ("\n");
	}
	
	return 0;
}
