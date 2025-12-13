#include <iostream>
#include "MisereTTT_Classes.h"
#include "MisereTTT_Board.h"
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "DiamondTTT_Classes.h"
#include "DiamondTTT_Board.h"
#include "DiamondTTT_UI.h"
#include "NumTTT_Classes.h"
#include "TTC5_Board.h"
#include "TTC5_UI.h"
#include "FourByFourBoard.h"
#include "FourByFourUI.h"
#include "PyramidBoard.h"
#include "PyramidUI.h" 
#include "WordTTT_Board.h"
#include "WordTTT_SmartAI.h"
#include "WordTTT_UI.h"
#include "ObstaclesBoard.h"
#include "ObstaclesUI.h"
#include "SUS_Classes.h"
#include "XO4R_Classes.h"
#include "InfinityTTT_Classes.h"
#include "UltimateTTT_Classes.h"
#include "MemoryTTT_Board.h"
#include "MemoryTTT_UI.h"


using namespace std;

int main() {
    while (true) {
        int choice;
        cout << "\n=============================\n";
        cout << " FCAI Game Hub Menu \n";
        cout << "=============================\n";
        cout << "0. Classic Tic-Tac-Toe (X-O)\n";
        cout << "1. SUS Game\n";
        cout << "2. Four-in-a-Row \n";
        cout << "3. 5 x 5 Tic-Tac-Toe \n";
        cout << "4. Word Tic-Tac-Toe\n";
        cout << "5. Misere Tic-Tac-Toe\n";
        cout << "6. Diamond Tic-Tac-Toe\n";
        cout << "7. 4 x 4 Tic-Tac-Toe\n";
        cout << "8. Pyramid Tic-Tac-Toe\n";
        cout << "9. Numerical Tic-Tac-Toe (Sum = 15)\n";
        cout << "10. Obstacles Tic-Tac-Toe \n";
        cout << "11. Infinity Tic-Tac-Toe \n";
        cout << "12. Ultimate Tic-Tac-Toe \n";
        cout << "13. Memory Tic-Tac-Toe \n";
        cout << "14. Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            XO_UI ui;
            Player<char>** players = ui.setup_players();
            X_O_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
            delete[] players;
        }

        else if (choice == 1) {
            SUS_UI ui;
            Player<char>** players = ui.setup_players();

            SUS_Board* board = new SUS_Board();
            for (int i = 0; i < 2; ++i)
                players[i]->set_board_ptr(board);

            GameManager<char> game(board, players, &ui);
            game.run();

            delete board;
            for (int i = 0; i < 2; ++i) delete players[i];
            delete[] players;
        }

        else if (choice == 2) {
            XO4R_UI ui;
            Player<char>** players = ui.setup_players();

            XO4R_Board* board = new XO4R_Board();
            for (int i = 0; i < 2; ++i)
                players[i]->set_board_ptr(board);

            GameManager<char> game(board, players, &ui);
            game.run();
        }

        else if (choice == 3) {
            cout << "=== 5x5 Tic Tac Toe ===" << endl;

            TTC5_Board* board = new TTC5_Board();
            TTC5_UI* ui = new TTC5_UI();
            Player<char>** players = ui->setup_players();
            GameManager<char> gameManager(board, players, ui);
            gameManager.run();

            delete board;
            delete ui;
            delete players[0];
            delete players[1];
            delete[] players;
        }

        else if (choice == 4) {
            cout << "=== Word Tic-Tac-Toe ===" << endl;

            WordTTT_Board* board = new WordTTT_Board();
            WordTTT_UI* ui = new WordTTT_UI();

            // FIXED: Use setup_players() to allow AI selection
            Player<char>** players = ui->setup_players();

            GameManager<char> gameManager(board, players, ui);
            gameManager.run();

            delete board;
            delete ui;
            delete players[0];
            delete players[1];
            delete[] players;
        }

        else if (choice == 5) {
            MisereTTT_UI ui;
            Player<char>** players = ui.setup_players();
            MisereTTT_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
            delete[] players;
        }

        else if (choice == 6) {
            DiamondTTT_UI ui;
            Player<char>** players = ui.setup_players();
            DiamondTTT_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
            delete[] players;
        }

        else if (choice == 7) {
            cout << "=== 4x4 Moving Tic Tac Toe ===" << endl;

            FourByFourBoard* board = new FourByFourBoard();
            FourByFourUI* ui = new FourByFourUI();

            Player<char>** players = ui->setup_players();

            GameManager<char> gameManager(board, players, ui);
            gameManager.run();

            delete board;
            delete ui;
            delete players[0];
            delete players[1];
            delete[] players;
        }

        else if (choice == 8) {
            cout << "=== Pyramid Tic Tac Toe ===" << endl;

            PyramidBoard* board = new PyramidBoard();
            PyramidUI* ui = new PyramidUI();

            Player<char>** players = ui->setup_players();

            GameManager<char> gameManager(board, players, ui);
            gameManager.run();

            delete board;
            delete ui;
            delete players[0];
            delete players[1];
            delete[] players;

        }

        else if (choice == 9) {
            NumTTT_UI ui;
            Player<int>** players = ui.setup_players();
            NumTTT_Board board;
            GameManager<int> game(&board, players, &ui);
            game.run();
            delete[] players;
        }

        else if (choice == 10) {
            cout << "=== Obstacles Tic Tac Toe ===\n";

            ObstaclesBoard* board = new ObstaclesBoard();
            ObstaclesUI* ui = new ObstaclesUI();

            Player<char>** players = ui->setup_players();

            GameManager<char> game(board, players, ui);
            game.run();

            delete board;
            delete ui;
            delete players[0];
            delete players[1];
            delete[] players;

        }

        else if (choice == 11) {
            InfinityTTT_UI ui;
            Player<char>** players = ui.setup_players();
            InfinityTTT_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
            delete[] players;
        }

        else if (choice == 12) {
            cout << "=== Ultimate Tic-Tac-Toe ===\n";
            UltimateTTT_UI ui;
            Player<char>** players = ui.setup_players();
            UltimateTTT_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
            delete[] players;
        }


        else if (choice == 13) {
            MemoryTTT_UI ui;
            Player<char>** players = ui.setup_players();
            MemoryTTT_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
        }

        else if (choice == 14) {
            cout << "Goodbye!\n";
            break;
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
