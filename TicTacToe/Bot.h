#pragma once

extern struct Result
{
	Move best_move;
	int board_value;
};

void copy_array_2D(char array1[3][3], char array2[3][3]);

Result minimax(char board[3][3], int depth, bool is_maximizing_player, int move_number, Move lastmove);

int calculate_board_value(char board[3][3]);



