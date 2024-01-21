#include <iostream>
#include <iomanip>
#include "TicTacToe.h"
#include "Menu.h"
#include "Bot.h"
using namespace std;


Move last_move = { -1, -1 };

void undo_move(Move move, char board[3][3])
{
    if (move.row < 0 || move.row > 3 || move.col < 0 || move.col > 3) return;

    board[move.row][move.col] = ' ';
}

void set_move(Move move, char player, char board[3][3])
{
    if (move.row < 0 || move.row >= 3 || move.col < 0 || move.col >= 3) return;

    board[move.row][move.col] = player;
    last_move = { move.row, move.col };
}

int parse_digit(char digit)
{
    return digit - '0';
}

Move read_move()
{
    // read first two digits and clear iostream
    int row{}, col{};
   
    row = parse_digit(cin.get());
    col = parse_digit(cin.get());
    cin.clear();
    cin.ignore(INT32_MAX, '\n');
    return { row,col };
}

void print_board(char board[3][3])
{
    for (size_t i = 0; i < 3; i++)
    {
        cout << setw(2) << setfill(' ') << board[i][0] << setw(2) << "|" << setw(2) << board[i][1] << setw(2) << "|" << setw(2) << board[i][2] << endl;
        if (i != 2)cout << setw(12) << setfill('-') << " " << endl;
    }
}

bool check_win(char board[3][3], char player)
{
    // checking vertically and horizontally
    for (size_t i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == player)
        {
            return true;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == player)
        {
            return true;
        }
    }
    // checking diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == player)
    {
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == player)
    {
        return true;
    }
    return false;
}

void play(char board[3][3])
{
    // declaring a variable to store information about palye's move
    Move move;
    int action_number = 0;
    bool error = false;
    for (size_t i = 0; i < 9; i++)
    {
        // printing info and the board
        system("CLS");
        cout << "You can still use \"(55) menu\" and \"(99) quit\" actions while in game.\nWarning! \"menu\" action will clear the board." << endl;

        cout << "Please enter numbers representing row and column (0,1,2) in order row+column. \nFor example 12 - first row, second column." << endl << endl;

        print_board(board);

        if (error)
        {
            error = false;
            cout << "Wrong input, try again" << endl;
        }

        // reading move
        move = read_move();

        // handling actions
        action_number = check_for_action(move);
        if (action_number == 99)
        {
            execute_action(action_number);
        }
        else if (action_number == 55)
        {
            clear_board(board);
            execute_action(action_number);
            //return;
        }


        // validating position (move)
        if (move.row < 0 || move.row >= 3 || move.col < 0 ||move.col >= 3 || board[move.row][move.col] != ' ')
        {
            error = true;
            i--;
            continue;
        }

        // validating and setting move 
        set_move(move, i % 2 == 0 ? 'X' : 'O', board);
        
        // checking for win
        if (check_win(board, i % 2 == 0 ? 'X' : 'O'))
        {
            // printing winner's info
            system("CLS");
            print_board(board);
            cout << (i % 2 == 0 ? 'X' : 'O');
            cout << " won the game!";
            clear_board(board);
            cout << endl;
            system("pause");
            return;
        }
    }

    // all nine moves have been placed and function did not return in 'checking for win' block
    // it is tie then

    // printing info about tie
    system("CLS");
    print_board(board);
    cout << "Tie!";
    clear_board(board);
    cout << endl;
    system("pause");
}

void play_with_bot(char board[3][3])
{
    // declaring a variable to store information about palye's move
    Move move;
    int action_number = 0;

    bool error = false;

    for (size_t i = 0; i < 9; i++)
    {
        if (i % 2 == 1)
        {
            Result result = minimax(board, 9-i, false, i, last_move);
            set_move(result.best_move, 'O', board);
        }
        else
        {
            // printing info and the board
            system("CLS");
            cout << "You can still use \"(55) menu\" and \"(99) quit\" actions while in game. \nWarning! \"menu\" action will clear the board." << endl;

            cout << "Please enter numbers representing row and column (0,1,2) in order row+column. \nFor example 12 - first row, second column." << endl << endl;

            print_board(board);

            if (error)
            {
                error = false;
                cout << "Wrong input, try again" << endl;
            }

            // reading move
            move = read_move();

            // handling actions
            action_number = check_for_action(move);
            if (action_number == 99)
            {
                execute_action(action_number);
            }
            else if (action_number == 55)
            {
                clear_board(board);
                execute_action(action_number);
                //return;
            }


            // validating position (move)
            if (board[move.row][move.col] != ' ' || move.row < 0 || move.row >= 3 || move.col < 0 || move.col >= 3)
            {
                error = true;
                i--;
                continue;
            }

            // validating and setting move 
            set_move(move, i % 2 == 0 ? 'X' : 'O', board);
        }
        // checking for win
        if (check_win(board, i % 2 == 0 ? 'X' : 'O'))
        {
            // printing winner's info
            system("CLS");
            print_board(board);
            cout << (i % 2 == 0 ? 'X' : 'O');
            cout << " won the game!";
            clear_board(board);
            cout << endl;
            system("pause");
            return;
        }
    }

    // all nine moves have been placed and function did not return in 'checking for win' block
    // it is tie then

    // printing info about tie
    system("CLS");
    print_board(board);
    cout << "Tie!";
    clear_board(board);
    cout << endl;
    system("pause");
}

int check_for_action(Move move)
{
    int action_number = move.row * 10 + move.col;
    if (action_number < 33) return -1;
    if (validate_action_number(action_number))
    {
        return action_number;
    }
    return -1;
}

void clear_board(char board[3][3])
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}
