#include <stdio.h>
#include <vector>
using namespace std;

enum Pattern {
	HIGHEST_CARD,
	ONE_PAIR,
	TWO_PAIRS,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH
};

struct Card {
	int value;
	char suit;
};

Card str_to_Card (char str[5]);
void print_card (Card card);
void judge_rank (vector<Card> &card_vector, int &max_rank);
void find_best_hand (vector<Card> &hand_vector, vector<Card> &card_vector, int &max_rank);

int main () {
	char str[5];
	while (scanf ("%s", str) != EOF) {
		Card hand[5], deck[5];
		
		Card temp_card = str_to_Card(str);
		hand[0] = temp_card;
		for (int i=1; i<5; i++) {
			scanf ("%s", str);
			temp_card = str_to_Card(str);
			hand[i] = temp_card;
		}
		
		for (int i=0; i<5; i++) {
			scanf ("%s", str);
			temp_card = str_to_Card(str);
			deck[i] = temp_card;
		}
		
		int max_rank=0, rank;
		for (int i=0; i<=5; i++) {
			vector<Card> hand_vector, card_vector;
			for (int j=0; j<5; j++) {
				hand_vector.push_back(hand[j]);
			}
			for (int j=0; j<i; j++) {
				card_vector.push_back(deck[j]);
			}
			find_best_hand (hand_vector, card_vector, max_rank);
		}
		
		printf ("Hand: ");
		for (int i=0; i<5; i++) {
			print_card (hand[i]);
			printf (" ");
		}
		printf ("Deck: ");
		for (int i=0; i<5; i++) {
			print_card (deck[i]);
			printf (" ");
		}
		printf ("Best hand: ");
		switch (max_rank) {
			case HIGHEST_CARD: printf ("highest-card"); break;
			case ONE_PAIR: printf ("one-pair"); break;
			case TWO_PAIRS: printf ("two-pairs"); break;
			case THREE_OF_A_KIND: printf ("three-of-a-kind"); break;
			case STRAIGHT: printf ("straight"); break;
			case FLUSH: printf ("flush"); break;
			case FULL_HOUSE: printf ("full-house"); break;
			case FOUR_OF_A_KIND: printf ("four-of-a-kind"); break;
			case STRAIGHT_FLUSH: printf ("straight-flush"); break;
			default: break;
		}
		printf ("\n");
	}
	
	
	return 0;
}

Card str_to_Card (char str[5]) {
	Card card;
	switch (str[0]) {
		case 'A': card.value = 1; break;
		case 'T': card.value = 10; break;
		case 'J': card.value = 11; break;
		case 'Q': card.value = 12; break;
		case 'K': card.value = 13; break;
		default : card.value = str[0]-'0'; break;
	}
	card.suit = str[1];
	
	return card;
}

void print_card (Card card) {
	switch (card.value) {
		case 1: printf ("A"); break;
		case 10: printf ("T"); break;
		case 11: printf ("J"); break;
		case 12: printf ("Q"); break;
		case 13: printf ("K"); break;
		default : printf ("%c", card.value+'0'); break;
	}
	
	printf ("%c", card.suit);
	
	return;
}

void judge_rank (vector<Card> &card_vector, int &max_rank) {
	int nums[15]={0};
	for (int i=0; i<card_vector.size(); i++) {
		nums[card_vector[i].value]++;
		if (card_vector[i].value == 1)
			nums[14]++;
	}
	
	if (max_rank < STRAIGHT_FLUSH) {
		bool OK_flag=true;
		char suit_type=card_vector[0].suit;
		for (int i=1; i<5; i++) {
			if (card_vector[i].suit != suit_type) {
				OK_flag = false;
				break;
			}
		}
		int start_i;
		for (int i=2; i<=13; i++) {
			if (nums[i] > 0) {
				start_i = i;
				break;
			}
		}
		if (start_i <= 10) {
			if (start_i == 2 && nums[1] == 1) {
				start_i = 1;
			}
			for (int i=1; i<5; i++) {
				if (nums[start_i+i] == 0) {
					OK_flag = false;
					break;
				}
			}
		}
		else
			OK_flag = false;
		
		if (OK_flag) {
			max_rank = STRAIGHT_FLUSH;
			return;
		}
	}
	
	if (max_rank < FOUR_OF_A_KIND) {
		bool OK_flag=false;
		for (int i=1; i<=13; i++) {
			if (nums[i] == 4) {
				OK_flag = true;
				break;
			}
		}
		if (OK_flag) {
			max_rank = FOUR_OF_A_KIND;
			return;
		}
	}
	
	if (max_rank < FULL_HOUSE) {
		bool two_flag=false, three_flag=false;
		for (int i=1; i<=13; i++) {
			if (nums[i] == 2)
				two_flag = true;
			else if (nums[i] == 3)
				three_flag = true;
		}
		if (two_flag && three_flag) {
			max_rank = FULL_HOUSE;
			return;
		}
	}
	
	if (max_rank < FLUSH) {
		bool OK_flag=true;
		char suit_type=card_vector[0].suit;
		for (int i=1; i<5; i++) {
			if (card_vector[i].suit != suit_type) {
				OK_flag = false;
				break;
			}
		}
		if (OK_flag) {
			max_rank = FLUSH;
			return;
		}
	}
	
	if (max_rank < STRAIGHT) {
		bool OK_flag=true;
		int start_i;
		for (int i=2; i<=13; i++) {
			if (nums[i] > 0) {
				start_i = i;
				break;
			}
		}
		if (start_i <= 10) {
			if (start_i == 2 && nums[1] == 1) {
				start_i = 1;
			}
			for (int i=1; i<5; i++) {
				if (nums[start_i+i] == 0) {
					OK_flag = false;
					break;
				}
			}
		}
		else
			OK_flag = false;
		
		if (OK_flag) {
			max_rank = STRAIGHT;
			return;
		}
	}
	
	if (max_rank < THREE_OF_A_KIND) {
		bool OK_flag=false;
		for (int i=1; i<=13; i++) {
			if (nums[i] == 3) {
				OK_flag = true;
				break;
			}
		}
		if (OK_flag) {
			max_rank = THREE_OF_A_KIND;
			return;
		}
	}
	
	if (max_rank < TWO_PAIRS) {
		int pair_num=0;
		for (int i=1; i<=13; i++) {
			if (nums[i] == 2)
				pair_num++;
		}
		if (pair_num == 2) {
			max_rank = TWO_PAIRS;
			return;
		}
		else if (pair_num == 1) {
			max_rank = ONE_PAIR;
			return;
		}
	}
	
	return;
}

/* 窮舉所有組合 */
void find_best_hand (vector<Card> &hand_vector, vector<Card> &card_vector, int &max_rank) {
	if (max_rank == STRAIGHT_FLUSH)
		return;
	
	if (card_vector.size() == 5) {
		judge_rank(card_vector, max_rank);
		return;
	}
	
	for (int i=0; i<hand_vector.size(); i++) {
		Card temp_card = hand_vector[i];
		hand_vector.erase(hand_vector.begin()+i);
		card_vector.push_back(temp_card);
		
		find_best_hand (hand_vector, card_vector, max_rank);
		
		hand_vector.insert(hand_vector.begin()+i, temp_card);
		card_vector.pop_back();
	}
	return;
}
