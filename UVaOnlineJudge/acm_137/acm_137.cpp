/* 線段交點：http://paulbourke.net/geometry/pointlineplane/ */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	double x;
	double y;
};

void intersection (Point p1, Point p2, Point q1, Point q2, vector<Point> &polygon_overlap);
double cross (Point p1, Point p2, Point q1, Point q2);
double area (vector<Point> &polygon);

Point p_min;
bool myCompare (Point a, Point b){
	if (a.y == p_min.y && b.y == p_min.y)
		return a.x < b.x;
	else if (a.y == p_min.y)
		return a.x > 0.0;
	else if (a.y == p_min.y)
		return b.x > 0.0;
	else {
		double temp = (a.x-p_min.x)/(a.y-p_min.y) - (b.x-p_min.x)/(b.y-p_min.y);
		if (temp == 0)
			return a.x < b.x;
		else
			return temp > 0;
	}
}

int main() {
	int number1, number2;
	while (scanf ("%d", &number1) != EOF) {
		if (number1 == 0)
			break;
		
		vector<Point> polygon1, polygon2, polygon_overlap;
		
		Point temp_point;
		for (int i=0; i<number1; i++) {
			scanf ("%lf%lf", &temp_point.x, &temp_point.y);
			polygon1.push_back(temp_point);
		}
		
		scanf ("%d", &number2);
		for (int i=0; i<number2; i++) {
			scanf ("%lf%lf", &temp_point.x, &temp_point.y);
			polygon2.push_back(temp_point);
		}
		
		/* 找出所有邊的交點 */
		Point p1, p2, q1, q2;
		for (int i=0; i<number1; i++) {
			p1 = polygon1[i];
			p2 = polygon1[(i+1)%number1];
			for (int j=0; j<number2; j++) {
				q1 = polygon2[j];
				q2 = polygon2[(j+1)%number2];
				
				intersection (p1, p2, q1, q2, polygon_overlap);
			}
		}
		
		/* 找出在另一個凸邊形的內部的點 */
		for (int i=0; i<number1; i++) {
			for (int j=0; j<number2; j++) {
				q1 = polygon2[j];
				q2 = polygon2[(j+1)%number2];
				double direction = cross (q1, polygon1[i], q1, q2);
				if (direction == 0) {
					if (min(q1.x, q2.x) <= polygon1[i].x && polygon1[i].x <= max(q1.x, q2.x) && 
						min(q1.y, q2.y) <= polygon1[i].y && polygon1[i].y <= max(q1.y, q2.y) ) {
						polygon_overlap.push_back(polygon1[i]);
						break;
					}
				}
				else if (direction < 0)
					break;
				else if (j == number2-1)
					polygon_overlap.push_back(polygon1[i]);
			}
		}
		
		for (int i=0; i<number2; i++) {
			for (int j=0; j<number1; j++) {
				q1 = polygon1[j];
				q2 = polygon1[(j+1)%number1];
				double direction = cross (q1, polygon2[i], q1, q2);
				if (direction == 0) {
					if (min(q1.x, q2.x) <= polygon2[i].x && polygon2[i].x <= max(q1.x, q2.x) && 
						min(q1.y, q2.y) <= polygon2[i].y && polygon2[i].y <= max(q1.y, q2.y) ) {
						for (int k=0; k<polygon_overlap.size(); k++) {
							if (polygon2[i].x == polygon_overlap[k].x && polygon2[i].y == polygon_overlap[k].y)
								break;
							if (k == polygon_overlap.size()-1)
								polygon_overlap.push_back(polygon2[i]);
						}
						break;
					}
				}
				else if (direction < 0)
					break;
				else if (j == number1-1)
					polygon_overlap.push_back(polygon2[i]);
			}
		}
		
		/* 排序重疊的點 */
		if (polygon_overlap.size() > 0) {
			p_min.x = polygon_overlap[0].x;
			p_min.y = polygon_overlap[0].y;
			for (int i=0; i<polygon_overlap.size(); i++) {
				if (polygon_overlap[i].y < p_min.y) {
					p_min.x = polygon_overlap[i].x;
					p_min.y = polygon_overlap[i].y;
				}
				else if (polygon_overlap[i].y == p_min.y && polygon_overlap[i].x < p_min.x) {
					p_min.x = polygon_overlap[i].x;
				}
			}
			
			sort (polygon_overlap.begin(), polygon_overlap.end(), myCompare);
		}

		/*
		for (int i=0; i<polygon_overlap.size(); i++) {
			printf ("%f, %f\n", polygon_overlap[i].x, polygon_overlap[i].y);
		}
		printf ("\n");
		*/
		
		double answer = area(polygon1)+area(polygon2)-2.0*area(polygon_overlap);
		printf ("%8.2f", answer);
	}
	printf ("\n");

	return 0;
}

void intersection (Point p1, Point p2, Point q1, Point q2, vector<Point> &polygon_overlap) {
	double temp = (q2.y-q1.y)*(p2.x-p1.x) - (q2.x-q1.x)*(p2.y-p1.y);
	if (temp != 0.0) {
		double ua = ((q2.x-q1.x)*(p1.y-q1.y) - (q2.y-q1.y)*(p1.x-q1.x) ) / temp;
		double ub = ((p2.x-p1.x)*(p1.y-q1.y) - (p2.y-p1.y)*(p1.x-q1.x) ) / temp;
		
		if (ua > 0 && ua < 1 && ub >0 && ub < 1) {
			Point intersection_point;
			intersection_point.x = p1.x + ua*(p2.x-p1.x);
			intersection_point.y = p1.y + ua*(p2.y-p1.y);
			
			polygon_overlap.push_back(intersection_point);
		}
	}
	
	return;
}

double cross (Point p1, Point p2, Point q1, Point q2) {
	return (p1.x-p2.x)*(q1.y-q2.y) - (q1.x-q2.x)*(p1.y-p2.y);
}

double area (vector<Point> &polygon) {
	double area=0.0;
	for (int i=0; i<polygon.size(); i++) {
		area += polygon[i].x*polygon[(i+1)%polygon.size()].y - polygon[(i+1)%polygon.size()].x*polygon[i].y;
	}
	if (area < 0)
		area *= -1.0;
	
	return 0.5*area;
}
