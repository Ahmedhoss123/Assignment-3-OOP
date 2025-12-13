#include "FourByFourUI.h"
#include "AIPlayer.h" // Include the AI header
#include <iostream>
#include <limits>
#include <ctime>
#include <cstdlib>

using namespace std;

FourByFourUI::FourByFourUI()
    : UI<char>("4x4 Moving Tic Tac Toe", 3) {
    srand(static_cast<unsigned>(time(nullptr)));
}

Player<char>* FourByFourUI::create_player(string& name, char symbol, PlayerType type) {
    // Fix: Check for AI/Computer type and return the specific AI class
    if (type == PlayerType::COMPUTER || type == PlayerType::AI) {
        return new FourByFour_AI_Player(name, symbol);
    }
    return new Player<char>(name, symbol, type);
}

Move<char>* FourByFourUI::get_move(Player<char>* player) {
    if (!player) return nullptr;

    // Check if it is the Smart AI player
    FourByFour_AI_Player* aiPtr = dynamic_cast<FourByFour_AI_Player*>(player);
    if (aiPtr) {
        // Delegate to the AI class logic
        return aiPtr->get_move(player->get_board_ptr());
    }

    // Human Logic
    if (player->get_type() == PlayerType::HUMAN) {
        int sx, sy, dx, dy;
        while (true) {
            cout << player->get_name()
                << " (" << player->get_symbol()
                << ") enter src(x y) then dst(x y): ";

            if ((cin >> sx >> sy >> dx >> dy) && !cin.fail()) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return new FourByFourMove<char>(sx, sy, dx, dy, player->get_symbol());
            }
            else {
                cout << "Invalid input. Enter four integers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    // Fallback internal computer logic (if dynamic cast fails for some reason)
    return get_computer_move(player);
}

Move<char>* FourByFourUI::get_computer_move(Player<char>* player) {
    Board<char>* bptr = player->get_board_ptr();
    if (!bptr) {
        return new FourByFourMove<char>(0, 0, 0, 0, player->get_symbol());
    }

    FourByFourBoard* realBoard = dynamic_cast<FourByFourBoard*>(bptr);
    if (!realBoard) {
        // ... (Fallback code remains same as before)
        return new FourByFourMove<char>(0, 0, 0, 0, player->get_symbol());
    }

    char aiSym = player->get_symbol();
    char oppSym = (aiSym == 'X' ? 'O' : 'X');

    vector<Move4> moves = generate_moves(*realBoard, aiSym);
    if (moves.empty()) {
        return new FourByFourMove<char>(-1, -1, -1, -1, aiSym);
    }

    int bestScore = numeric_limits<int>::min();
    Move4 bestMove = moves[0];
    int maxDepth = 4;

    for (const auto& m : moves) {
        FourByFourBoard simBoard = *realBoard;
        FourByFourMove<char> mv(m.sx, m.sy, m.dx, m.dy, aiSym);
        if (!simBoard.update_board(&mv))
            continue;

        int score = minimax(simBoard, aiSym, oppSym, false, 1, maxDepth);

        if (score > bestScore) {
            bestScore = score;
            bestMove = m;
        }
    }

    cout << player->get_name() << " (" << aiSym << ") chooses move: "
        << bestMove.sx << " " << bestMove.sy
        << " -> " << bestMove.dx << " " << bestMove.dy << "\n";

    return new FourByFourMove<char>(bestMove.sx, bestMove.sy,
        bestMove.dx, bestMove.dy, aiSym);
}

std::vector<FourByFourUI::Move4>
FourByFourUI::generate_moves(const FourByFourBoard& boardState, char sym) {
    vector<Move4> result;
    auto mat = boardState.get_board_matrix();
    int rows = boardState.get_rows();
    int cols = boardState.get_columns();
    const int dr[4] = { 1, -1, 0, 0 };
    const int dc[4] = { 0, 0, 1, -1 };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (mat[r][c] != sym) continue;
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                if (mat[nr][nc] == '.') {
                    Move4 m;
                    m.sx = r;  m.sy = c;
                    m.dx = nr; m.dy = nc;
                    result.push_back(m);
                }
            }
        }
    }
    return result;
}

int FourByFourUI::minimax(FourByFourBoard boardState,
    char aiSym, char oppSym,
    bool isAiTurn,
    int depth,
    int maxDepth) {
    
    Player<char> ai("AI", aiSym, PlayerType::HUMAN);
    Player<char> op("OPP", oppSym, PlayerType::HUMAN);

    if (boardState.is_win(&ai)) return 10 - depth;
    if (boardState.is_win(&op)) return -10 + depth;
    if (depth >= maxDepth) return 0;

    char currentSym = isAiTurn ? aiSym : oppSym;
    vector<Move4> moves = generate_moves(boardState, currentSym);
    if (moves.empty()) return 0;

    if (isAiTurn) {
        int best = numeric_limits<int>::min();
        for (const auto& m : moves) {
            FourByFourBoard nextBoard = boardState;
            FourByFourMove<char> mv(m.sx, m.sy, m.dx, m.dy, currentSym);
            if (!nextBoard.update_board(&mv)) continue;
            int score = minimax(nextBoard, aiSym, oppSym, false, depth + 1, maxDepth);
            if (score > best) best = score;
        }
        return best;
    }
    else {
        int best = numeric_limits<int>::max();
        for (const auto& m : moves) {
            FourByFourBoard nextBoard = boardState;
            FourByFourMove<char> mv(m.sx, m.sy, m.dx, m.dy, currentSym);
            if (!nextBoard.update_board(&mv)) continue;
            int score = minimax(nextBoard, aiSym, oppSym, true, depth + 1, maxDepth);
            if (score < best) best = score;
        }
        return best;
    }
}
