#include <stdio.h>
#include <vector>
using namespace std;

struct Card {
	char number;
	char suit;
};

int main() {
	char str[4];
	while (scanf("%s", str) != EOF) {
		if (str[0] == '#')
			break;
		
		Card temp_card;
		
		vector<vector<Card>> card_list(52, vector<Card>(0, temp_card));

		temp_card.number = str[0];
		temp_card.suit = str[1];
		card_list[0].push_back(temp_card);
		for (int i=1; i<52; i++) {
			scanf("%s", str);
			temp_card.number = str[0];
			temp_card.suit = str[1];
			card_list[i].push_back(temp_card);
		}
		
		bool stop_flag=false;
		while (!stop_flag) {
			stop_flag = true;
			for (int i=1; i<card_list.size(); i++) {
				if (i >= 3) {
					if (card_list[i].back().number == card_list[i-3].back().number || card_list[i].back().suit == card_list[i-3].back().suit) {
						card_list[i-3].push_back(card_list[i].back());
						card_list[i].pop_back();
						if (card_list[i].size() == 0) {
							card_list.erase(card_list.begin()+i);
						}
						stop_flag=false;
						break;
					}
				}
				
				if (card_list[i].back().number == card_list[i-1].back().number || card_list[i].back().suit == card_list[i-1].back().suit) {
					card_list[i-1].push_back(card_list[i].back());
					card_list[i].pop_back();
					if (card_list[i].size() == 0) {
						card_list.erase(card_list.begin()+i);
					}
					stop_flag=false;
					break;
				}
			}
		}
		
		printf ("%d pile", card_list.size());
		if (card_list.size() > 1)
			printf ("s");
		printf (" remaining:");
		for (int i=0; i<card_list.size(); i++) {
			printf (" %d", card_list[i].size());
		}
		printf ("\n");
	}
	
	return 0;
}