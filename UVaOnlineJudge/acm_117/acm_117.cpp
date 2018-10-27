#include <stdio.h>
#include <string.h>
using namespace std;

#define ALPHABET 26
#define ROADMAX 2147480000

/* 找出兩個奇數點之間的最小路徑+所有路徑的總長度即為答案 */

void initialize (int &road_total_length, int road_map[ALPHABET][ALPHABET], int dimention[ALPHABET]);
int dijkstra (int road_map[ALPHABET][ALPHABET], int dimention[ALPHABET]);

int main () {
	int i, j;
	
	int road_map[ALPHABET][ALPHABET];
	for (i=0; i<ALPHABET; i++) {
		for (j=0; j<ALPHABET; j++) {
			road_map[i][j] = ROADMAX;
		}
	}
	
	char tmp_input[1000];
	int dimention[ALPHABET]={0}, odd_vertex[2], odd_index;
	int road_length, start_vertex, end_vertex;
	int road_total_length;
	
	initialize (road_total_length, road_map, dimention);
	
	while (scanf ("%s", tmp_input) != EOF) {
		if (strcmp (tmp_input, "deadend") == 0) {
			road_total_length += dijkstra (road_map, dimention); 
			printf ("%d\n", road_total_length);
			
			initialize (road_total_length, road_map, dimention);
		}
		else {
			road_length = strlen(tmp_input);
			start_vertex = (int)(tmp_input[0]-'a');
			end_vertex = (int)(tmp_input[road_length-1]-'a');
			
			road_map[start_vertex][end_vertex] = road_length;
			road_map[end_vertex][start_vertex] = road_length;
			road_total_length += road_length;
			dimention[start_vertex]++;
			dimention[end_vertex]++;
		}	
	}
	
	return 0;
}

void initialize (int &road_total_length, int road_map[ALPHABET][ALPHABET], int dimention[ALPHABET]) {
	int i, j;
	
	road_total_length = 0;
	for (i=0; i<ALPHABET; i++) {
		dimention[i] = 0;
		for (j=0; j<ALPHABET; j++) {
			road_map[i][j] = -1;
		}
	}
	
	return;
}

int dijkstra (int road_map[ALPHABET][ALPHABET], int dimention[ALPHABET]) {
	int i, j, k;
	
	int visit[ALPHABET]={0}, distance[ALPHABET];
	int odd_vertex[2], odd_num=0;
	for (i=0; i<ALPHABET; i++) {
		distance[i] = ROADMAX;
		if (dimention[i] == 0) {
			visit[i] = 1;
		}
		else if (dimention[i]%2 == 1) {
			odd_vertex[odd_num++] = i;
		}
	}
	if (odd_num == 0)
		return 0;
	
	distance[odd_vertex[0]] = 0;
	int tmp_min, min_vertex;
	for (k=0; k<ALPHABET; k++) {
		tmp_min = ROADMAX;
		min_vertex = -1;
		for (i=0; i<ALPHABET; i++) {
			if (!visit[i] && distance[i] < tmp_min) {
				min_vertex = i;
				tmp_min = distance[i];
			}
		}
		
		if (min_vertex == -1)
			break;
		
		visit[min_vertex] = 1;
		
		for (i=0; i<ALPHABET; i++) {
			if (!visit[i] && (road_map[min_vertex][i] != -1) && (distance[min_vertex]+ road_map[min_vertex][i] < distance[i]) ) {
				distance[i] = distance[min_vertex]+ road_map[min_vertex][i];
			}
		}
	}
	
	return distance[odd_vertex[1]];
}