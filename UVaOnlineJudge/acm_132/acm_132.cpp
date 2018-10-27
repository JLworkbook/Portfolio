#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int min_x, min_y;

struct Point {
	int id;
	int x;
	int y;
};

bool point_cmp (Point a, Point b) {
	if (a.y == min_y && b.y == min_y) {
		return a.x < b.x;
	}
	else if (a.y == min_y) {
		return true;
	}
	else if (b.y == min_y) {
		return false;
	}
	else {
		double slope_a = (1.0*(a.x-min_x))/(1.0*(a.y-min_y));
		double slope_b = (1.0*(b.x-min_x))/(1.0*(b.y-min_y));
		if (slope_a == slope_b) {
			return a.x < b.x;
		}
		else
			return slope_a > slope_b;
	}
}

int cross (Point a, Point b, Point c);
int dot (Point a, Point b, Point c);

int main () {
	char object_name[25];
	while (scanf ("%s", object_name) != EOF) {
		if (strcmp (object_name, "#") == 0)
			break;
		
		Point mass_centre;
		scanf ("%d%d", &mass_centre.x, &mass_centre.y);
		
		vector<Point> vertexes;
		int temp_id=1;
		Point temp_point;
		while (scanf ("%d%d", &temp_point.x, &temp_point.y) != EOF) {
			if (temp_point.x == 0 && temp_point.y == 0)
				break;
			temp_point.id = temp_id++;
			vertexes.push_back(temp_point);
		}
		
		min_y=vertexes[0].y;
		min_x=vertexes[0].x;
		for (int i=1; i<vertexes.size(); i++) {
			if (vertexes[i].y < min_y || (vertexes[i].y == min_y && vertexes[i].x < min_x)) {
				min_y = vertexes[i].y;
				min_x = vertexes[i].x;
			}
		}
		
		sort (vertexes.begin(), vertexes.end(), point_cmp);
		
		/*
		for (int i=0; i<vertexes.size(); i++) {
			printf ("%d ", vertexes[i].id);
		}
		printf ("\n");
		*/
		
		map<int, map<int, int> > collinear;
		vector<Point> convex_hull;
		for (int i=0; i<vertexes.size(); i++) {
			
			while (convex_hull.size() >= 2) {
				int direction = cross (convex_hull[convex_hull.size()-2], convex_hull[convex_hull.size()-1], vertexes[i]);
				if (direction > 0)
					break;
				else if (direction == 0) {
					if (collinear.find(convex_hull[convex_hull.size()-2].id) != collinear.end() && collinear[convex_hull[convex_hull.size()-2].id].find(vertexes[i].id) != collinear[convex_hull[convex_hull.size()-2].id].end()) {
						collinear[convex_hull[convex_hull.size()-2].id][vertexes[i].id] = max(collinear[convex_hull[convex_hull.size()-2].id][vertexes[i].id], convex_hull[convex_hull.size()-1].id);
					}
					else {
						if (collinear.find(convex_hull[convex_hull.size()-2].id) != collinear.end() && collinear[convex_hull[convex_hull.size()-2].id].find(convex_hull[convex_hull.size()-1].id) != collinear[convex_hull[convex_hull.size()-2].id].end()) {
							collinear[convex_hull[convex_hull.size()-2].id][vertexes[i].id] = max(convex_hull[convex_hull.size()-1].id, collinear[convex_hull[convex_hull.size()-2].id][convex_hull[convex_hull.size()-1].id]);
						}
						else
							collinear[convex_hull[convex_hull.size()-2].id][vertexes[i].id] = convex_hull[convex_hull.size()-1].id;
					}
				}
				convex_hull.pop_back();
			}
			convex_hull.push_back (vertexes[i]);
		}
		convex_hull.push_back(vertexes[0]);
		
		/*
		for (int i=0; i<convex_hull.size(); i++) {
			printf ("%d ", convex_hull[i].id);
		}
		printf ("\n");
		*/
		
		/* 質心要在兩點之間，但不用考慮是否在質心之上 */
		int min_base=temp_id, temp_base;
		for (int i=0; i<convex_hull.size()-1; i++) {
			if (dot(convex_hull[i], convex_hull[i+1], mass_centre) > 0 && dot(convex_hull[i+1], convex_hull[i], mass_centre) > 0) {
				/*
				int above_line = cross (convex_hull[i], convex_hull[i+1], mass_centre);
				*/
				temp_base = max(convex_hull[i].id, convex_hull[i+1].id);
				for (int j=0; j<vertexes.size(); j++) {
					if (vertexes[j].id != convex_hull[i].id && vertexes[j].id != convex_hull[i+1].id) {
						if (cross (convex_hull[i], convex_hull[i+1], vertexes[j]) == 0) {
							temp_base = max (temp_base, vertexes[j].id);
						}
					}
				}
				/*
					temp_base = max(convex_hull[i].id, convex_hull[i+1].id);
					if (collinear.find(convex_hull[i].id) != collinear.end() && collinear[convex_hull[i].id].find(convex_hull[i+1].id) != collinear[convex_hull[i].id].end()) {
						temp_base = max(temp_base, collinear[convex_hull[i].id][convex_hull[i+1].id]);
					}
				*/
				if (temp_base < min_base)
					min_base = temp_base;
				
			}
		}
		printf ("%s %d\n", object_name, min_base);
	}

	return 0;
}

int cross (Point a, Point b, Point c) {
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x); 
}

int dot (Point a, Point b, Point c) {
	return (b.x-a.x)*(c.x-a.x) + (b.y-a.y)*(c.y-a.y);
}