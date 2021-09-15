#include <iostream>
#include <time.h> // For time

void clearcin();
void Init();
void DrawBoard();
void PlayGame();
bool CheckForWin();
void PlayGameAI();

const int rows{ 3 };
const int cols{ 3 };
char Board[rows][cols]{}; // Storage for the different squares
int TurnNumber{ 1 }; // We start on Turn 1
int PlayerNumber{ 1 }; // Player 1 starts
int PlayerNumberChoice{}; // Letting the player choose whether to play as X or O against an AI
char PlayerNumberChoiceCH{}; // It looks cleaner if we let the user answer 'x' or 'o' when we ask them who to play, so we store it in a char first

int main() {

    char RepeatAns{};
    bool RepeatGame{};
    bool RepeatQuestion{};
    int PlayerChoice{};
    
    srand(time(NULL)); // Set the random seed to current system time, for the "AI" to choose a random square
    do {
        system("cls"); // Clear the screen of any potential previous game
        std::cout << "Hello, and welcome to tic-tac-toe!\n";
        Init(); // Initialize the game
        DrawBoard(); // Draw the game board
        std::cout << "You will each choose a number between 1 and 9 to select the square you want to pick. \n"
            << "The goal is to get three pieces in a row.\n"
            << "How would you like to play?\n"
            << "1. Versus another player\n"
            << "2. Versus easy AI\n";
        std::cin >> PlayerChoice;
        clearcin();
        // Check if they input a valid number
        while (PlayerChoice < 1 || PlayerChoice > 2) {
            std::cout << "That's not a valid choice, please try again!\n";
            std::cin >> PlayerChoice;
            clearcin();
        }
        switch (PlayerChoice) {
        case 1:
            PlayGame(); // If they entered 1, play a regular game of 2 human players
            break;
        case 2:
            PlayGameAI(); // If they entered 2, play a game against an AI that chooses random squares
            break;
        case 3:
            // COMING SOON™
        default:
            std::cout << "Something went wrong, please notify the developers!\n";
            EXIT_FAILURE;
        }
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

    system("cls"); // Clean up all the initial text and stuff
    DrawBoard(); // Redraw the initial board
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
            return;
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

// Function to play the game against an AI
void PlayGameAI() {
    
    int PlayerChoice{};
    int AIChoice{};

    std::cout << "Would you like to play as X or O?\n";
    std::cin >> PlayerNumberChoiceCH;
    clearcin();
    PlayerNumberChoiceCH = toupper(PlayerNumberChoiceCH); // Change the letter to uppercase so we only get 2 conditions instead of 4
    // Check if they actually typed in either x or o
    while (PlayerNumberChoiceCH != 'X' && PlayerNumberChoiceCH != 'O') {
        std::cout << "That's not a valid answer! Please choose either 'X' or 'O'\n";
        std::cin >> PlayerNumberChoiceCH;
        clearcin();
        PlayerNumberChoiceCH = toupper(PlayerNumberChoiceCH);
    }
    // Set PlayerNumberChoice according to which player they chose
    if (PlayerNumberChoiceCH == 'X') {
        PlayerNumberChoice = 1;
    }
    else if (PlayerNumberChoiceCH == 'O') {
        PlayerNumberChoice = 2;
    }
    system("cls"); // Clean up all the initial text and stuff
    DrawBoard(); // Redraw the initial board
    do {
        // If current player is the human, do basically the same thing as in PlayGame (I am lazy so I've mostly copy-pasted it)
        if (PlayerNumber == PlayerNumberChoice) {
            std::cout << "Please select a square to place your piece in (1-9):\n";
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
            // Check if someone has won, if they have, there's no need to check who's won, it's clearly the human since it's their turn
            if (CheckForWin() == true) {
                system("cls");
                DrawBoard(); // Clear the screen and draw the final game board before breaking the loop and going back to main
                std::cout << "The human has won! Congratulations, you will not be replaced by a robot just yet...\n";
                return;
            }
            PlayerNumber = 1 - PlayerNumber + 2; // Switch between player 1 and 2 every iteration of the loop (assuming PlayerNumber is set to either of the values already, which it is in Init)
            system("cls"); // Clear the screen
            DrawBoard(); // Draw the new game board
            TurnNumber += 1; // Increment the turn counter, so the game ends after 9 turns
        }
        else {
            AIChoice = rand() % (rows * cols) + 1; // Make AI choose a random square between 1 and rows times columns (This makes the board scalable, although my win condition check is not scalable)
            // Now check if the AI chose a valid square, if not choose another, then check again
            while (Board[AIChoice / 3][(AIChoice % 3) - 1] == 'X' || Board[AIChoice / 3][(AIChoice % 3) - 1] == 'O') {
                AIChoice = rand() % (rows * cols) + 1;
            }
            // Now we check if the AI is X or O, and update the board accordingly
            if (PlayerNumber == 1) {
                Board[AIChoice / 3][(AIChoice % 3) - 1] = 'X';
            }
            else if (PlayerNumber == 2) {
                Board[AIChoice / 3][(AIChoice % 3) - 1] = 'O';
            }
            // Check if someone has won, if they have, there's no need to check who's won, it's clearly the AI since it's their current turn
            if (CheckForWin() == true) {
                system("cls");
                DrawBoard(); // Clear the screen and draw the final game board before breaking the loop and going back to main
                std::cout << "The AI has won! This may or may not be the beginning of the robot revolution...\n";
                return;
            }
            PlayerNumber = 1 - PlayerNumber + 2; // Switch between player 1 and 2 every iteration of the loop (assuming PlayerNumber is set to either of the values already, which it is in Init)
            system("cls"); // Clear the screen
            DrawBoard(); // Draw the new game board
            TurnNumber += 1; // Increment the turn counter, so the game ends after 9 turns
        }
    } while (TurnNumber != 10);

}
