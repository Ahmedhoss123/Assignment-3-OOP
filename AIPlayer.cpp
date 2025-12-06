#include "AIPlayer.h"
#include <algorithm>

AIPlayer::AIPlayer(char symbol) : Player<char>(symbol) {}

Move<char>* AIPlayer::get_move(Board<char>* b) {
    auto board = dynamic_cast<FourByFourBoard*>(b);

    int bestVal = -100000;
    Move<char>* bestMove = nullptr;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board->board[i][j] == symbol){

                int dx[4] = {1,-1,0,0};
                int dy[4] = {0,0,1,-1};

                for(int k=0;k<4;k++){
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    if(ni>=0 && ni<4 && nj>=0 && nj<4 && board->board[ni][nj]=='.'){
                        auto move = new FourByFourMove<char>(i,j,ni,nj,symbol);

                        if(board->update_board(move)){
                            int val = minimax(board, 0, false);
                            board->undo_move(move);

                            if(val > bestVal){
                                bestVal = val;
                                bestMove = move;
                            }
                        }
                    }
                }
            }
        }
    }
    return bestMove;
}
