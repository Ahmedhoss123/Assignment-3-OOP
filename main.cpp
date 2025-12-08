#include "MisereTTT_Classes.h"
#include <iostream>
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
#include "WordTTT_UI.h"
#include "ObstaclesBoard.h"
#include "ObstaclesUI.h"
#include "SUS_Classes.h"
#include "XO4R_Classes.h"
#include "InfinityTTT_Classes.h"
#include "AIPlayer3.h"
#include "WordTTT_SmartAI.h"

using namespace std;

int main() {
    while (true) {
        int choice;
        cout << "\n=============================\n";
        cout << " FCAI Game Hub Menu \n";
        cout << "=============================\n";
        cout << "1.SUS\n";
        cout << "2.Four-in-a-Row \n";
        cout << "3.5 x 5 Tic-Tac-Toe \n";
        cout << "4.Word Tic-Tac-Toe\n";
        cout << "5.Misere Tic-Tac-Toe\n";
        cout << "6.Diamond Tic-Tac-Toe\n";
        cout << "7.4 x 4 Tic-Tac-Toe\n";
        cout << "8.Pyramid Tic-Tac-Toe\n";
        cout << "0.Classic Tic-Tac-Toe (X-O)\n";
        cout << "9.Numerical Tic-Tac-Toe (Sum = 15)\n";
        cout << "10.Obstacles Tic-Tac-Toe \n";
        cout << "11.Infinity Tic-Tac-Toe \n";
        cout << "12.Ultimate Tic-Tac-Toe \n";
        cout << "13.Memory Tic-Tac-Toe \n";
        cout << "14.Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            SUS_UI ui;
            Player<char>** players = ui.setup_players();
            SUS_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
        }
        else if (choice == 2) {
            XO4R_UI ui;
            Player<char>** players = ui.setup_players();
            XO4R_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
        }
        else if (choice == 3) {
            cout << "=== 5x5 Tic Tac Toe ===" << endl;

			 int mode;
 			 cout << "1. Human vs Human\n";
			 cout << "2. Human vs Random AI\n";
			 cout << "3. Human vs Smart AI\n";
			 cout << "Choice: ";
			 cin >> mode;

			 TTC5_Board* board = new TTC5_Board();
			 TTC5_UI* ui = new TTC5_UI();
			 Player<char>** players;
			
			 if (mode == 1) {
		     players = new Player<char>*[2];
		
		     string name1, name2;
		     cout << "Enter Player 1 name: ";
		     cin >> name1;
		     cout << "Enter Player 2 name: ";
		     cin >> name2;
		
		     players[0] = new Player<char>(name1, 'X', PlayerType::HUMAN);
			 new Player<char>("Random AI", 'O', PlayerType::RANDOM);
			 }
			 else if (mode == 3) {
			     players = new Player<char>*[2];
			     string name;
			     cout << "Enter your name: ";
			     cin >> name;
			
			     int difficulty;
			     cout << "AI Difficulty (1=Easy, 2=Medium, 3=Hard): ";
			     cin >> difficulty;
			
			     players[0] = new Player<char>(name, 'X', PlayerType::HUMAN);
			     players[1] = new AIPlayer("Smart AI", 'O', PlayerType::AI);
			
			     AIPlayer* ai = dynamic_cast<AIPlayer*>(players[1]);
			     if (ai) {
		         ai->set_difficulty(difficulty);
		         cout << "Playing against " << ai->get_difficulty_string() << " AI\n";
		     }
		 }
		 else {
		     cout << "Invalid! Defaulting to Human vs Human.\n";
		     players = new Player<char>*[2];
		     players[0] = new Player<char>("Player 1", 'X', PlayerType::HUMAN);
		     players[1] = new Player<char>("Player 2", 'O', PlayerType::HUMAN);
		 }
		
			 GameManager<char> gameManager(board, players, ui);
			 gameManager.run();
			
			 delete board;
			 delete ui;
			 delete[] players;
        }
        else if (choice == 4) {
            cout << "=== Word Tic -Tac -Toe ===" << endl;
			int gameMode;
			cout << "\nSelect Game Mode:\n";
			cout << "1. Human vs Human\n";
			cout << "2. Human vs Random AI\n";
			cout << "3. Human vs Smart AI\n";
			cout << "Enter your choice (1-3): ";
			cin >> gameMode;
			
			if (gameMode < 1 || gameMode > 3) {
			    cout << "Invalid choice! Defaulting to Human vs Human.\n";
			    gameMode = 1;
			}
			WordTTT_Board* board = new WordTTT_Board();
			WordTTT_UI* ui = new WordTTT_UI();
			
			Player<char>* players[2];
			string name1, name2;
			
			if (gameMode == 1) {
			    cout << "Enter Player 1 name: ";
			    cin >> name1;
			    cout << "Enter Player 2 name: ";
			    cin >> name2;
			
			    players[0] = new Player<char>(name1, 'A', PlayerType::HUMAN);
			    players[1] = new Player<char>(name2, 'B', PlayerType::HUMAN);
			}
			else if (gameMode == 2) {
			    cout << "Enter your name: ";
			    cin >> name1;
			
			    players[0] = new Player<char>(name1, 'A', PlayerType::HUMAN);
			    players[1] = new Player<char>("Random AI", 'B', PlayerType::COMPUTER);
			}
			else if (gameMode == 3) {
			    cout << "Enter your name: ";
			    cin >> name1;
			    int difficulty;
			    cout << "Select AI Difficulty:\n";
			    cout << "1. Easy (Depth 2)\n";
			    cout << "2. Medium (Depth 4)\n";
			    cout << "3. Hard (Depth 6)\n";
			    cout << "Enter difficulty (1-3): ";
			    cin >> difficulty;
			
			    int depth;
			    if (difficulty == 1) depth = 2;
			    else if (difficulty == 2) depth = 4;
			    else depth = 6;
			
			    players[0] = new Player<char>(name1, 'A', PlayerType::HUMAN);
			    players[1] = new WordTTT_SmartAI("Smart AI", 'B', depth);
			
			    cout << "\nPlaying against Smart AI (Depth: " << depth << ")\n";
				}
				players[0]->set_board_ptr(board);
				players[1]->set_board_ptr(board);
				GameManager<char> gameManager(board, players, ui);
				gameManager.run();
				delete board;
				delete ui;
				delete players[0];
				delete players[1];           
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
        else if (choice == 0) {
            XO_UI ui;
            Player<char>** players = ui.setup_players();
            X_O_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
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
        }
        else if (choice == 12) {
        
        }
        else if (choice == 13) {
        
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









