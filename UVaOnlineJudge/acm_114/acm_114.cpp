#include <stdio.h>
#include <string.h>
using namespace std;

#define AXISMAX 55

struct MAP {
	int type;
	int value;
	int cost;
};

int main () {
	int i, j;

	MAP map[AXISMAX][AXISMAX];
	memset(map, 0, sizeof(map));
	int m, n;
	scanf ("%d%d", &m, &n);
	
	int wall_cost;
	scanf ("%d", &wall_cost);
	
	/* 牆壁是外圍的邊 所以是(1,1)~(m,1)~(m,n)~(1,n)~(1,1) */
	
	for (i=1; i<=m; i++) {
		map[i][1].type = 1;
		map[i][1].cost = wall_cost;
		map[i][n].type = 1;
		map[i][n].cost = wall_cost;
	}
	for (j=1; j<=n; j++) {
		map[1][j].type = 1;
		map[1][j].cost = wall_cost;
		map[m][j].type = 1;
		map[m][j].cost = wall_cost;
	}
	
	int p;
	scanf ("%d", &p);
	int bumper_x, bumper_y, bumper_value, bumper_cost;
	for (i=0; i<p; i++) {
		scanf ("%d%d%d%d", &bumper_x, &bumper_y, &bumper_value, &bumper_cost);
		map[bumper_x][bumper_y].type = 2;
		map[bumper_x][bumper_y].value = bumper_value;
		map[bumper_x][bumper_y].cost = bumper_cost;
	}
	
	int direction[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
	int x, y, ball_direction, life;
	int next_x, next_y;
	int score, total_score=0;
	while (scanf ("%d%d%d%d", &x, &y, &ball_direction, &life) != EOF) {
		score = 0;
		
		while (life > 0) {
			next_x = x+direction[ball_direction][0];
			next_y = y+direction[ball_direction][1];
		
			life -= 1;
			if (life == 0)
				continue;
			
			if (map[next_x][next_y].type != 0) {
				score += map[next_x][next_y].value;
				life -= map[next_x][next_y].cost;
				ball_direction = (ball_direction-1+4)%4;
			}
			else {
				x = next_x;
				y = next_y;
			}
		}
		total_score += score;
		printf ("%d\n", score);
	}
	printf ("%d\n", total_score);
	
	return 0;
}