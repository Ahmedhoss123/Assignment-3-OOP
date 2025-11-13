#include <iostream>
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include "NumTTT_Classes.h"

using namespace std;
int main() {
    while (true) {
        int choice;
        cout << "\n=============================\n";
        cout << " FCAI Game Hub Menu \n";
        cout << "=============================\n";
        cout << "1. Classic Tic-Tac-Toe (X-O)\n";
        cout << "2. Numerical Tic-Tac-Toe (Sum = 15)\n";
        cout << "3. Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            XO_UI ui;
            Player<char>** players = ui.setup_players();
            X_O_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
        }
        else if (choice == 2) {
            NumTTT_UI ui;
            Player<int>** players = ui.setup_players();
            NumTTT_Board board;
            GameManager<int> game(&board, players, &ui);
            game.run();
        }
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
