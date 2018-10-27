#include <stdio.h>
#include <string.h>
using namespace std;

#define NAMESIZE 14
#define MAXPEOPLENUM 12

int find_people (int group_people_num, char name_list[MAXPEOPLENUM][NAMESIZE], char name[NAMESIZE]);

int main () {
	int i, j;

	int group_people_num, group_num=0;
	
	char name_list[MAXPEOPLENUM][NAMESIZE];
	char giver[NAMESIZE], receiver[NAMESIZE], tmp_name[NAMESIZE];
	int giver_index, receiver_index;
	
	int money_list[MAXPEOPLENUM], gift_money, give_people_num, per_get_money;
	
	while (scanf ("%d", &group_people_num) != EOF) {
		for (i=0; i<group_people_num; i++) {
			scanf ("%s", name_list[i]);
			money_list[i] = 0;
		}
		for (i=0; i<group_people_num; i++) {
			scanf ("%s", giver);
			giver_index = find_people (group_people_num, name_list, giver);
			
			scanf ("%d%d", &gift_money, &give_people_num);
			if (give_people_num == 0)
				per_get_money = 0;
			else
				per_get_money = gift_money/give_people_num;
			
			for (j=0; j<give_people_num; j++) {
				scanf ("%s", receiver);
				receiver_index = find_people (group_people_num, name_list, receiver);
				money_list[receiver_index] += per_get_money;
			}
			money_list[giver_index] -= per_get_money*give_people_num;
		}
		group_num++;
		if (group_num > 1) {
			printf ("\n");
		}
		
		for (i=0; i<group_people_num; i++) {
			printf ("%s %d\n", name_list[i], money_list[i]);
		}
	}
	
	return 0;
}

int find_people (int group_people_num, char name_list[MAXPEOPLENUM][NAMESIZE], char name[NAMESIZE]) {
	int i;
	
	for (i=0; i<group_people_num; i++) {
		if (strcmp(name_list[i], name) == 0)
			return i;
	}
	
	return -1;
}
