#include "AIPlayer.h"
#include <algorithm>

AIPlayer::AIPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::AI) {}

Move<char>* AIPlayer::get_move(Board<char>* b) {
    auto board = dynamic_cast<FourByFourBoard*>(b);

    int bestVal = -100000;
    Move<char>* bestMove = nullptr;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board->get_cell(i,j) == symbol){

                int dx[4] = {1,-1,0,0};
                int dy[4] = {0,0,1,-1};

                for(int k=0;k<4;k++){
                    int ni = i + dx[k];
                    int nj = j + dy[k];

                    if(ni>=0 && ni<4 && nj>=0 && nj<4 && board->get_cell(ni,nj)=='.'){
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

int AIPlayer::minimax(FourByFourBoard* board, int depth, bool isMax) {

    if(board->is_win(this)) return 10 - depth;
    if(board->is_draw(this)) return 0;

    char opp = (symbol=='X') ? 'O' : 'X';

    if(isMax){
        int best = -100000;

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board->get_cell(i,j) == symbol){
                    for(int d=0; d<4; d++){
                        int dx[4]={1,-1,0,0};
                        int dy[4]={0,0,1,-1};

                        int ni=i+dx[d], nj=j+dy[d];
                        if(ni>=0&&ni<4&&nj>=0&&nj<4 && board->get_cell(ni,nj)=='.'){
                            auto m=new FourByFourMove<char>(i,j,ni,nj,symbol);
                            if(board->update_board(m)){
                                best = max(best, minimax(board, depth+1, false));
                                board->undo_move(m);
                            }
                        }
                    }
                }
            }
        }
        return best;
    }
    else{
        int best = 100000;

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(board->get_cell(i,j) == opp){
                    for(int d=0; d<4; d++){
                        int dx[4]={1,-1,0,0};
                        int dy[4]={0,0,1,-1};

                        int ni=i+dx[d], nj=j+dy[d];
                        if(ni>=0&&ni<4&&nj>=0&&nj<4 && board->get_cell(ni,nj)=='.'){
                            auto m=new FourByFourMove<char>(i,j,ni,nj,opp);
                            if(board->update_board(m)){
                                best = min(best, minimax(board, depth+1, true));
                                board->undo_move(m);
                            }
                        }
                    }
                }
            }
        }
        return best;
    }
}
