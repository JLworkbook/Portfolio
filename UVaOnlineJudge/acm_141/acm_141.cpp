#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

bool checkGameEnd (int n, set<pair<int, int> > game_board, set<set<pair<int, int> > > history_board);
set<pair<int, int> > turnRight (int n, set<pair<int, int> > game_board);

int main () {
	int n;
	while (scanf ("%d", &n) != EOF) {
		if (n == 0)
			break;
		
		int x, y;
		char c, action;
		set<pair<int, int> > game_board;
		set<set<pair<int, int> > > history_board;
		int end_flag=0;
		for (int i=0; i<2*n; i++) {
			scanf ("%d%d%c%c", &x, &y, &c, &action);
			if (end_flag == 0) {
				if (action == '+')
					game_board.insert(make_pair(x, y));
				else
					game_board.erase(make_pair(x, y));
				
				if (checkGameEnd (n, game_board, history_board)) {
					end_flag = i;
				}	
				else {
					history_board.insert(game_board);
				}
			}
		}
		
		if (end_flag == 0)
			printf ("Draw\n");
		else {
			printf ("Player %d wins on move %d\n", (end_flag+1)%2+1, end_flag+1);
		}
	}
	
	return 0;
}

bool checkGameEnd (int n, set<pair<int, int> > game_board, set<set<pair<int, int> > > history_board) {
	if (history_board.find(game_board) != history_board.end())
		return true;

	game_board = turnRight (n, game_board);
	if (history_board.find(game_board) != history_board.end())
		return true;

	game_board = turnRight (n, game_board);
	if (history_board.find(game_board) != history_board.end())
		return true;

	game_board = turnRight (n, game_board);
	if (history_board.find(game_board) != history_board.end())
		return true;

	return false;
}

set<pair<int, int> > turnRight (int n, set<pair<int, int> > game_board) {
	int first, second;
	set<pair<int, int> > new_game_board;
	for (set<pair<int, int> >::iterator it=game_board.begin(); it!=game_board.end(); it++) {
		first = n + 1 - (it->second);
		second = it->first;
		new_game_board.insert(make_pair(first, second));
	}
	
	return new_game_board;
}