#include <stdio.h>
#include <vector>
using namespace std;

int main () {
	char type[10];
	int region[26][4], region_num=0;
	int icon[52][2], icon_num=0;
	bool icon_visible[52], first_click=true;
	
	for (int i=0; i<52; i++)
		icon_visible[i] = true;
	
	int click_x, click_y;
	
	while (scanf ("%s", type) != EOF) {
		if (type[0] == '#')
			break;
		
		if (type[0] == 'R') {
			scanf ("%d%d%d%d", &region[region_num][0], &region[region_num][1], &region[region_num][2], &region[region_num][3]);
			region_num++;
		}
		else if (type[0] == 'I') {
			scanf ("%d%d", &icon[icon_num][0], &icon[icon_num][1]);
			icon_num++;
		}
		else {
			if (first_click) {
				for (int i=0; i<icon_num; i++) {
					for (int j=0; j<region_num; j++) {
						if (icon[i][0] >= region[j][0] && icon[i][0] <= region[j][2] && icon[i][1] >= region[j][1] && icon[i][1] <= region[j][3]) {
							icon_visible[i] = false;
							break;
						}
					}
				}
				first_click = false;
			}
			
			scanf ("%d%d", &click_x, &click_y);
			
			bool is_in_region=false;
			for (int i=region_num-1; i>=0; i--) {
				if (click_x >= region[i][0] && click_x <= region[i][2] && click_y >= region[i][1] && click_y <= region[i][3]) {
					printf ("%c\n", ('A'+i));
					is_in_region = true;
					break;
				}
			}
			if (!is_in_region) {
				vector<int> closest_icons;
				int closest = 500000, temp;
				for (int i=0; i<icon_num; i++) {
					if (icon_visible[i]) {
						temp = (icon[i][0]-click_x)*(icon[i][0]-click_x) + (icon[i][1]-click_y)*(icon[i][1]-click_y);
						if (temp < closest) {
							closest = temp;
							closest_icons.clear();
							closest_icons.push_back(i);
						}
						else if (temp == closest) {
							closest_icons.push_back(i);
						}
					}
				}
				
				for (int i=0; i<closest_icons.size(); i++) {
					printf ("%3d", closest_icons[i]+1);
				}
				printf ("\n");
			}
		}
	}
	
	return 0;
}
