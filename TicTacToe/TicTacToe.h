#pragma once

// struct Move was declared here because there are function using this structure as return type

// struct Move represents position (row and column) of a move that player can make
extern struct Move
{
    int row;
    int col;
};

void undo_move(Move move, char board[3][3]);

/*
set_move(Move, char, char[3][3]) set move on the board

@param Move - indicates position of the move
@param player - character to be placed (use 'X' and 'O')
@param board - TicTacToe game board, 3x3 2D char array
*/
void set_move(Move move, char player, char board[3][3]);

/*
parse_digit(char) changes type of a digit from char to int

@param digit - char type digit to be parsed

@return int type digit
*/
int parse_digit(char digit);

/*
read_move() reads input from console and returns it as Move

@return position as Move
*/
Move read_move();

/*
print_board(char[3][3]) prints TicTacToe board on the console

@param board - TicTacToe game board, 3x3 2D char array
*/
void print_board(char board[3][3]);

/*
check_win(char[3][3], char) checks whether there are 3 the same chars in a row, column or diagonal

@param board - TicTacToe game board, 3x3 2D char array

@param player - character to be checked on board in rows, columns or diagonals

@return true if someone won, otherwise - false
*/
bool check_win(char board[3][3], char player);

/*
play(char[3][3]) runs TicTacToe game

@param board - TicTacToe game board, 3x3 2D char array
*/
void play(char board[3][3]);

void play_with_bot(char board[3][3]);

/*
check_for_action(Move) checks if player's input is an action (except actions that can be interpret as a move)

@param move - move to check

@return If input is an action function returns a number that represents it. If not: -1.
*/
int check_for_action(Move move);

/*
clear_board(char[3][3]) sets all elements in 2D char array to ' ' (space)

@param board - TicTacToe game board, 3x3 2D char array
*/
void clear_board(char board[3][3]);