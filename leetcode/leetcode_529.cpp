class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        vector<vector<int>> queue;
        queue.push_back(click);
        while (!queue.empty()) {
            vector<int> now_click = queue.front();
            queue.erase(queue.begin());
            if (now_click[0] < 0 || now_click[0] >= board.size() || now_click[1] < 0 || now_click[1] >= board[0].size()) {
                continue;
            }
            else if (board[now_click[0]][now_click[1]] == 'M') {
                board[now_click[0]][now_click[1]] = 'X';
            }
            else if (board[now_click[0]][now_click[1]] == 'E') {
                int mine_num=0;
                for (int i=-1; i<=1; i++) {
                    for (int j=-1; j<=1; j++) {
                        if (now_click[0]+i < 0 || now_click[0]+i >= board.size() || now_click[1]+j < 0 || now_click[1]+j >= board[0].size()) {
                            continue;
                        }
                        else {
                            if (board[now_click[0]+i][now_click[1]+j] == 'M') {
                                mine_num++;
                            }
                        }
                    }
                }
                
                if (mine_num == 0) {
                    board[now_click[0]][now_click[1]] = 'B';
                    for (int i=-1; i<=1; i++) {
                        for (int j=-1; j<=1; j++) {
                            if (i == 0 && j == 0)
                                continue;
                            
                            if (now_click[0]+i < 0 || now_click[0]+i >= board.size() || now_click[1]+j < 0 || now_click[1]+j >=board[0].size()) {
                                continue;
                            }
                            if (board[now_click[0]+i][now_click[1]+j] == 'E') {
                                vector<int> temp_click;
                                temp_click.push_back(now_click[0]+i);
                                temp_click.push_back(now_click[1]+j);
                                queue.push_back(temp_click);
                            }
                        }
                    }
                }
                else {
                    board[now_click[0]][now_click[1]] = '0'+mine_num;
                }
            }
        }
        return board;
    }
};