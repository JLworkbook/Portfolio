#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

#define MAXCOUNTRY 22
#define MAXN 102

struct Point {
	float x;
	float y;
};

Point down_point;

int my_compare(const void *a, const void *b);
vector<Point> find_country_ouder_side (int n, float country[MAXN][2]);
int check_missle_landing (float missle_x, float missle_y, vector<Point> smallest_side_country);
float count_area (vector<Point> smallest_side_country);

int main() {
	int i, j;
	
	int country_num=0;
	float country_list[MAXCOUNTRY][MAXN][2];
	vector<Point> smallest_side_country_list[MAXCOUNTRY];
	int building_num[MAXCOUNTRY];
	
	int n; 
	float x, y;
	while (scanf ("%d", &n) != EOF) {
		if (n == -1)
			break;
		
		building_num[country_num] = n;
		for (i=0; i<n; i++) {
			scanf ("%f%f", &x, &y);
			country_list[country_num][i][0] = x;
			country_list[country_num][i][1] = y;
		}
		country_num++;
	}
	
	for (i=0; i<country_num; i++) {
		smallest_side_country_list[i] = find_country_ouder_side (building_num[i], country_list[i]);
	}
	
	/*
	for (i=0; i<country_num; i++) {
		for (j=0; j<smallest_side_country_list[i].size(); j++) {
			printf (" (%f, %f)", smallest_side_country_list[i][j].x, smallest_side_country_list[i][j].y);
		}
		printf ("\n");
	}
	*/
	
	int disconnect_country[MAXCOUNTRY]={0};
	while (scanf ("%f%f", &x, &y) != EOF) {
		for (i=0; i<country_num; i++) {
			if (!disconnect_country[i]) {
				if (check_missle_landing (x, y, smallest_side_country_list[i]) ) {
					disconnect_country[i] = 1;
				}
			}
		}
	}
	
	float area_sum=0.0;
	for (i=0; i<country_num; i++) {
		if (disconnect_country[i])
			area_sum += count_area (smallest_side_country_list[i]);
	}
	
	printf ("%.2f\n", area_sum);
	
	return 0;
}

/* 極角排序 */
int my_compare(const void *a, const void *b) {
    Point c = *(Point *)a;
	Point d = *(Point *)b;
	
	if (c.x == down_point.x && c.y == down_point.y)
		return -1;
	
	float c_slope, d_slope;
	if (down_point.y == c.y && down_point.y == d.y) {
		return (c.x > d.x);
	}
	else if (down_point.y == c.y) {
		return -1;
	}
	else if (down_point.y == d.y) {
		return 1;
	}
	else {
		c_slope = (c.x - down_point.x)/(c.y - down_point.y);
		d_slope = (d.x - down_point.x)/(d.y - down_point.y);
		if (c_slope == d_slope)
			return (c.x > d.x);
		else if (c_slope > d_slope)
			return -1;
		else 
			return 1;
	}
}

/* 找出每個國家組成最小邊長的所有點 */
vector<Point> find_country_ouder_side (int n, float country[MAXN][2]) {
	int i;
	
	down_point.x = country[0][0];
	down_point.y = country[0][1];
	for (i=1; i<n; i++) {
		if ( (country[i][1] < down_point.y) || ( (country[i][1] == down_point.y) && (country[i][0] < down_point.x))) {
			down_point.y = country[i][1];
			down_point.x = country[i][0];
		}
	}
	
	vector<Point> sort_country;
	for (i=0; i<n; i++) {
		Point tmp_point;
		tmp_point.x = country[i][0];
		tmp_point.y = country[i][1];
		sort_country.push_back(tmp_point);
	}
	
	/* 極角排序 */
	qsort ((void *)&sort_country[0], n, sizeof(sort_country[0]), my_compare);
	
	Point tmp_point_2;
	tmp_point_2.x = sort_country[0].x;
	tmp_point_2.y = sort_country[0].y;
	sort_country.push_back(tmp_point_2);
	
	/*
	for (i=0; i<=n; i++) {
		printf ("(%f, %f)\n", sort_country[i].x, sort_country[i].y);
	}
	printf ("\n");
	*/
	
	/* 用 Graham scan 找出凸包 */
	vector<Point> smallest_side_country;
	float direction;
	smallest_side_country.push_back(sort_country[0]);
	smallest_side_country.push_back(sort_country[1]);
	int s_size=2;
	for (i=2; i<=n; i++) {
		direction = (smallest_side_country[s_size-1].x-smallest_side_country[s_size-2].x)*(sort_country[i].y-smallest_side_country[s_size-1].y) - (sort_country[i].x-smallest_side_country[s_size-1].x)*(smallest_side_country[s_size-1].y-smallest_side_country[s_size-2].y);
		while (direction <= 0) {
			smallest_side_country.pop_back();
			s_size--;
			if (s_size < 2) {
				break;
			}
			direction = (smallest_side_country[s_size-1].x-smallest_side_country[s_size-2].x)*(sort_country[i].y-smallest_side_country[s_size-1].y) - (sort_country[i].x-smallest_side_country[s_size-1].x)*(smallest_side_country[s_size-1].y-smallest_side_country[s_size-2].y);
		}
		smallest_side_country.push_back(sort_country[i]);
		s_size++;
	}

	return smallest_side_country;
}

/* 用交叉相乘確認飛彈有沒有落在多邊形上 */
int check_missle_landing (float missle_x, float missle_y, vector<Point> smallest_side_country) {
	int i;
	
	float direction;
	for (i=0; i<smallest_side_country.size()-1; i++) {
		direction = (smallest_side_country[i+1].x-smallest_side_country[i].x)*(missle_y-smallest_side_country[i].y) - (smallest_side_country[i+1].y-smallest_side_country[i].y)*(missle_x-smallest_side_country[i].x);
		if (direction < 0) {
			return 0;
		}
	}
	return 1;
}

/* 計算國土面積 */
float count_area (vector<Point> smallest_side_country) {
	int i;
	
	float area=0.0;
	for (i=0; i<smallest_side_country.size()-1; i++) {
		area += (smallest_side_country[i].x*smallest_side_country[i+1].y) - (smallest_side_country[i+1].x*smallest_side_country[i].y);
	}
	area /= 2.0;
	
	return area;
}
