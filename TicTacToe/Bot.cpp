#include "TicTacToe.h"
#include "Bot.h"

/*
copy_array_2D(char[3][3], char[3][3]) copies first array values to second array

@param array1 source array

@param array2 target array
*/
void copy_array_2D(char array1[3][3], char array2[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            array2[i][j] = array1[i][j];
        }
    }
}

// X is maximizing player, O is minimizing
Result minimax(char board[3][3], int depth, bool is_maximizing_player, int move_number, Move lastmove)
{
    // checking whether minimax algorithm is at the end of recursion 
	if (depth == 0 || move_number > 8 || check_win(board, !is_maximizing_player ? 'X' : 'O'))
	{
        // returning best move and value of the board
        return { {lastmove.row, lastmove.col}, calculate_board_value(board) };
	}

    if (is_maximizing_player)
    {
        // initialize best_result, and move variables to store information about current best result and placed move
        Result best_result = { {-1,-1}, -9999 };
        Move move = { -1,-1 };

        // setting player
        char current_player = 'X';

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // finding empty place on the board 
                if (board[i][j] != ' ') continue;

                // set move on found place
                move = { i, j };
                set_move(move, current_player, board);

                // copy current board to temp_board
                // we use only temp_board to calculate next positions
                char temp_board[3][3] = {};
                copy_array_2D(board, temp_board);

                // calculate for new instance of the board
                Result result = minimax(temp_board, depth - 1, !is_maximizing_player, move_number + 1, move);
                
                // undo last move from the board 
                undo_move(move, board);

                // check if new move is better than current
                if ((best_result.best_move.row == -1 && best_result.best_move.col == -1) ||
                    result.board_value > best_result.board_value)
                {
                    // set new move as the best
                    best_result.best_move = move;
                    best_result.board_value = result.board_value;
                }
            }
        }
        return best_result;
    }
    else
    {
        // actions in the 'else' statement are the same as above but for 'O''s

        Result best_result = { {-1,-1}, 9999 };
        Move move = { -1,-1 };
        char current_player = 'O';

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != ' ') continue;
                
                move = { i, j };
                set_move(move, current_player, board);

                char temp_board[3][3] = {};
                copy_array_2D(board, temp_board);

                Result result = minimax(temp_board, depth - 1, !is_maximizing_player, move_number + 1, move);
                
                undo_move(move, board);

                if ((best_result.best_move.row == -1 && best_result.best_move.col == -1) ||
                    result.board_value < best_result.board_value)
                {
                    best_result.best_move = move;
                    best_result.board_value = result.board_value;
                }
            }
        }
        return best_result;
    }
}

/*
calculate_board_value(char[3][3]) calculates board value for current position by checking for win

@param board - TicTacToe game board, 3x3 2D char array

@return inteager value of position, 1000 if 'X' won, -1000 if 'O' won, else 0
*/
int calculate_board_value(char board[3][3])
{
    if (check_win(board,'X'))
    {
        return 1000;
    }
    if (check_win(board, 'O'))
    {
        return -1000;
    }
    return 0;
}

