#include <iostream>
#include <string> // For strings

void clearcin();
void Init();
void DrawBoard();
void PlayGame();
bool CheckForWin();

const int rows{ 3 };
const int cols{ 3 };
char Board[rows][cols]{}; // Storage for the different squares
int TurnNumber{ 1 }; // We start on Turn 1
int PlayerNumber{ 1 }; // Player 1 starts

int main() {

    char RepeatAns{};
    bool RepeatGame{};
    bool RepeatQuestion{};
    

    do {
        system("cls"); // Clear the screen of any potential previous game
        std::cout << "Hello, and welcome to tic-tac-toe!\n";
        Init(); // Initialize the game
        DrawBoard(); // Draw the game board
        std::cout << "You will each choose a number between 1 and 9 to select the square you want to pick. \n"
            << "The goal is to get three pieces in a row.\n";
        PlayGame(); // Play the game
        // If nobody won the game after it's over, declare a draw
        if (CheckForWin() == false) {
            std::cout << "It's a draw! Well played, both of you!\n\n";
        }
        do {
            // Ask if the game should be repeated, and set RepeatGame accordingly
            std::cout << "Would you like to play again?\n"; // No need to tell them to use Y/N format, since we store the answer in a char variable, it will only take the first letter anyway
            std::cin >> RepeatAns;
            clearcin();
            RepeatAns = toupper(RepeatAns); // We set the character to its uppercase equivalent, so we only get 2 condition checks instead of 4
            switch (RepeatAns) {
            case 'Y':
                RepeatQuestion = false;
                RepeatGame = true;
                break;
            case 'N':
                RepeatQuestion = false;
                RepeatGame = false;
                std::cout << "Very well, goodbye for now!";
                break;
            default:
                std::cout << "That's not a valid answer! Please answer yes or no.\n";
                RepeatQuestion = true;
                break;
            }
        } while (RepeatQuestion == true);


    } while (RepeatGame == true);

	return 0;
}

// Function to clear out the buffer of cin, ensuring we don't take in more than one word and get weird inputs (or worse, infinite loops)
void clearcin() {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
}

// Function to initialize the gamestate, setting the characters back to 1-9 and resetting player and turn number
void Init() {
    //Initializing the board to 1-9, since char is just an integer we can simply add the value of '1' to it to start counting from there
    for (int i{ 0 }; i < rows; i++) {
        for (int j{ 0 }; j < cols; j++) {
            Board[i][j] = '1' + (i * 3) + j;
        }
    }
    PlayerNumber = 1; // Player 1 starts
    TurnNumber = 1; // We start on turn 1
}

// Function to draw the board, using nested for loops
void DrawBoard() {

    std::cout << "+---+---+---+\n";
    for (int i{ 0 }; i < rows; i++) {
        for (int j{ 0 }; j < cols; j++) {
            std::cout << "| " << Board[i][j] << " ";
        }
        std::cout << "|\n+---+---+---+\n";
    }

}

// Function to play the game
void PlayGame() {

    int PlayerChoice{};

    do {
        std::cout << "Player " << PlayerNumber << ", please select a square to place your piece in (1-9):\n";
        std::cin >> PlayerChoice;
        clearcin();
        // Check if the space is not taken by another piece
        do {
            if (Board[PlayerChoice / 3][(PlayerChoice % 3) - 1] == 'X' || Board[PlayerChoice / 3][(PlayerChoice % 3) - 1] == 'O') {
                std::cout << "That space is already taken! Choose another square:\n";
                std::cin >> PlayerChoice;
                clearcin();
            }
            // While also checking if they entered a number between 1 and 9
            while ((PlayerChoice < 1 || PlayerChoice > 9) == true) {
                std::cout << "That's not a number between 1 and 9, please try again!\n";
                std::cin >> PlayerChoice;
                clearcin();
            }
        } while (Board[PlayerChoice / 3][(PlayerChoice % 3) - 1] == 'X' || Board[PlayerChoice / 3][(PlayerChoice % 3) - 1] == 'O');

        // Check which player played, and change the respective square to their piece
        if (PlayerNumber == 1) {
            Board[PlayerChoice / 3][(PlayerChoice % 3) - 1] = 'X';
        }
        else if (PlayerNumber == 2) {
            Board[PlayerChoice / 3][(PlayerChoice % 3) - 1] = 'O';
        }
        // Check if someone has won, if they have, there's no need to check who's won, it's clearly the current player
        if (CheckForWin() == true) {
            system("cls");
            DrawBoard(); // Clear the screen and draw the final game board before breaking the loop and going back to main
            std::cout << "Player " << PlayerNumber << " has won the game! Congratulations!\n";
            break;
        }
        PlayerNumber = 1 - PlayerNumber + 2; // Switch between player 1 and 2 every iteration of the loop (assuming PlayerNumber is set to either of the values already, which it is in Init)
        system("cls"); // Clear the screen
        DrawBoard(); // Draw the new game board
        TurnNumber += 1; // Increment the turn counter, so the game ends after 9 turns
    } while (TurnNumber != 10);
}

// Function to check for a winner of the game, it does this by checking if 3 grids in a row (diagonally, vertically, or horizontally) are the same
bool CheckForWin() {

    // Check the 2 diagonals
    if (Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2]) {
        return true;
    }
    else if (Board[2][0] == Board[1][1] && Board[1][1] == Board[0][2]) {
        return true;
    }
    // Check the 3 horizontals
    else if (Board[0][0] == Board[0][1] && Board[0][1] == Board[0][2]) {
        return true;
    }
    else if (Board[1][0] == Board[1][1] && Board[1][1] == Board[1][2]) {
        return true;
    }
    else if (Board[2][0] == Board[2][1] && Board[2][1] == Board[2][2]) {
        return true;
    }
    // Check the 3 verticals
    else if (Board[0][0] == Board[1][0] && Board[1][0] == Board[2][0]) {
        return true;
    }
    else if (Board[0][1] == Board[1][1] && Board[1][1] == Board[2][1]) {
        return true;
    }
    else if (Board[0][2] == Board[1][2] && Board[1][2] == Board[2][2]) {
        return true;
    }
    // If none of them are the same, return false as there is no winner yet
    else return false;
}