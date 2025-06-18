/**
 * @file ticTacToe.cpp
 * @brief Implementation of Tic Tac Toe
 *
 * This program allows two players to play a game of Tic-Tac-Toe in the terminal.
 * The game supports alternating turns, win conditions, and a draw message.
 *
 * @author Nishan Subba
 * @github https://github.com/nisSubba2024
 * @date 01/08/25
 */

#include <iostream>
#include <iomanip>

/**
 * @brief Initializes the game board with empty spaces.
 *
 * @param board A 2D array representing the game board.
 */
void gameBoard(char board[][3]);

/**
 * @brief Displays the current state of the game board.
 *
 * @param board A 2D array representing the game board.
 */
void displayBoard(char board[][3]);

/**
 * @brief Fill a position on the board with a player's symbol.
 *
 * @param board A 2D array representing the game board.
 * @param row The row index of the desired position.
 * @param col The column index of the desired position.
 * @param letter The symbol of the player ('X' or 'O').
 * @param legalMove Indicates whether the move was valid.
 */
void fillBoard(char board[][3], int row, int col, char letter, bool& legalMove);

/**
 * @brief Prompts the current player to enter the row and column for their move.
 *
 * @param row The row index provided by the player.
 * @param col The column index provided by the player.
 * @param curPosition The current player's identifier (0 for 'O', 1 for 'X').
 */
void getPosition(int& row, int& col, int& curPosition);

/**
 * @brief Checks if the game is over due to all positions being filled.
 *
 * @param board A 2D array representing the game board.
 * @return true If the board is completely filled.
 * @return false If there are still empty positions on the board.
 */
bool gameOver(char board[][3]);

/**
 * @brief Switches the turn to the other player.
 *
 * @param curPlayer The current player's identifier (0 for 'O', 1 for 'X').
 */
void changePlayer(int& curPlayer);

/**
 * @brief Checks if a player has won or if the game has ended in a draw.
 *
 * @param board A 2D array representing the game board.
 * @param isOver Indicates whether the game is over.
 * @param isDraw Indicates whether the game ended in a draw.
 */
void checkWin(char board[][3], bool& isOver, bool& isDraw);

/**
 * @brief Displays a message announcing the winner.
 *
 * @param curPlayer The identifier of the winning player (0 for 'O', 1 for 'X').
 */
void winnerMessage(int curPlayer);

/**
 * @brief Main function to run the Tic-Tac-Toe game.
 *
 * Initializes the game board and alternates turns between two players.
 * Checks for win conditions or a draw after each move.
 *
 * @return int Exit status of the program.
 */

int main()
{
    char board[3][3];
    gameBoard(board);
    int row,
        col;
    bool isOver;
    char playerX = 'X';
    char playerO = 'O';
    int currentPlayer = 0;
    bool legalMove;
    bool isDraw;
    std::cout << R"(
    '########:'####::'######:::::'########::::'###:::::'######:::::'########::'#######::'########:
    ... ##..::. ##::'##... ##::::... ##..::::'## ##:::'##... ##::::... ##..::'##.... ##: ##.....::
    ::: ##::::: ##:: ##:::..:::::::: ##:::::'##:. ##:: ##:::..:::::::: ##:::: ##:::: ##: ##:::::::
    ::: ##::::: ##:: ##::::::::::::: ##::::'##:::. ##: ##::::::::::::: ##:::: ##:::: ##: ######:::
    ::: ##::::: ##:: ##::::::::::::: ##:::: #########: ##::::::::::::: ##:::: ##:::: ##: ##...::::
    ::: ##::::: ##:: ##::: ##::::::: ##:::: ##.... ##: ##::: ##::::::: ##:::: ##:::: ##: ##:::::::
    ::: ##::::'####:. ######:::::::: ##:::: ##:::: ##:. ######:::::::: ##::::. #######:: ########:
    :::..:::::....:::......:::::::::..:::::..:::::..:::......:::::::::..::::::.......:::........::
    )" << std::endl;

    std::cout << "******************** Game Start ********************" << std::endl;

    while (!isOver)
    {
        displayBoard(board);
        checkWin(board, isOver, isDraw);

        if (isOver)
        {
            break;
        }
        do
        {
            getPosition(row, col, currentPlayer);
            if (currentPlayer == 0)
            {
                fillBoard(board, row, col, playerO, legalMove);
            }
            else if (currentPlayer == 1)
            {
                fillBoard(board, row, col, playerX, legalMove);
            }
        }
        while (!legalMove);

        changePlayer(currentPlayer);
    }
    if (!isDraw)
    {
        winnerMessage(currentPlayer);
    }

    return 0;
}

void gameBoard(char board[][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            board[row][col] = ' ';
        }
    }
}

void displayBoard(char board[][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            std::cout << board[row][col];
            if (col != 2)
            {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (row != 2)
        {
            std::cout << "---------" << std::endl;
        }
    }
}

void fillBoard(char board[][3], int row, int col, char letter, bool& legalMove)
{
    if (board[row][col] == ' ')
    {
        board[row][col] = letter;
        legalMove = true;
    }
    else
    {
        std::cout << "That box is already filled!!" << std::endl;
        legalMove = false;
    }
}

void getPosition(int& row, int& col, int& curPosition)
{
    char letter = curPosition == 0 ? 'O' : 'X';
    do
    {
        std::cout << "\nPlayer " << letter << ": Enter row and col: ";
        std::cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            std::cout << "\nPlease enter valid position, out of bound" << std::endl;
        }
    }
    while (row < 0 || row > 2 || col < 0 || col > 2);
}

bool gameOver(char board[][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

void changePlayer(int& curPlayer)
{
    if (curPlayer == 0)
    {
        curPlayer = 1;
    }
    else
    {
        curPlayer = 0;
    }
}

void checkWin(char board[][3], bool& isOver, bool& isDraw)
{
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            isOver = true;
            isDraw = false;
            return;
        }

        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            isOver = true;
            isDraw = false;
            return;
        }
    }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        isOver = true;
        isDraw = false;
        return;
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        isOver = true;
        isDraw = false;
        return;
    }

    if (gameOver(board))
    {
        isOver = true;
        isDraw = true;
        std::cout << "\n********************* GAME OVER ****************************" << std::endl;
        std::cout << "It's a tie! Well played both players!" << std::endl;
    }
}

void winnerMessage(int curPlayer)
{
    char player = curPlayer == 1 ? 'O' : 'X';
    std::cout << "\n********************* GAME OVER ****************************" << std::endl;
    std::cout << "Congratulations Player " << player << " !!! You Won!!!" << std::endl;
    std::cout << "Thank You for playing" << std::endl;
}
