#include "Menu.h"
#include <iostream>
#include "TicTacToe.h"
using namespace std;

// struct Action contains information about actions (e.g. name of action)
struct Action
{
	int number;
	string name;
};

// game board 
char board[3][3] =
{
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

// number of actions
const int ACTIONS_SIZE = 5;

// array of actions (use for printing)
const Action* ACTIONS = new Action[ACTIONS_SIZE]{ {1, "play"},{2,"play with bot" }, {3, "rules"}, {55, "menu"}, {99, "quit"}};

void start()
{
	// clear the console, print the menu and allow user to use it
	system("CLS");
	print_menu();
	handle_action();
}

int get_action_number()
{
	int action_number = 0;

	// read input 
	// check if input is int if not - ignore
	cin >> action_number;
	cin.clear();
    cin.ignore(INT32_MAX, '\n');

	return action_number;
}	

void handle_action()
{
	// read input
	int action_number = get_action_number();

	// validate
	while (!validate_action_number(action_number))
	{
		cout << "Wrong action, try again" << endl;
		action_number = get_action_number();
	}

	// execute
	execute_action(action_number);
}

bool validate_action_number(int action_number)
{
	// search for action_number in ACTIONS
	for (size_t i = 0; i < ACTIONS_SIZE; i++)
	{
		if (ACTIONS[i].number == action_number)
		{
			return true;
		}
	}
	return false;
}

void execute_action(int action_number)
{
	// hard-coded swtich case that executes actions with specified number
	// if there is no action defined with given number print warning and quit app. Please use validation (validate_action_number)
	switch (action_number)
	{
	case 1:
		go_to_play();
		break;
	case 2:
		go_to_play_with_bot();
		break;
	case 3:
		go_to_rules();
		break;
	case 55:
		start();
		break;
	case 99:
		quit();
		break;
	default:
		cout << "No action defined with number " <<  action_number;
		exit(0);
		break;
	}
}

void print_menu()
{
	// print instructions 
	cout << "Choose what to do: " << endl;
	cout << "(enter a number that represents action)" << endl;

	// print actions from ACTIONS
	for (size_t i = 0; i < ACTIONS_SIZE; i++)
	{
		cout << "(" << ACTIONS[i].number << ") " << ACTIONS[i].name << endl;
	}
}

void go_to_play()
{
	// call play() from TicTacToe.h
	play(board);
	// go back to the menu
	start();
}

void go_to_play_with_bot()
{
	// call play_with_bot() from TicTacToe.h
	play_with_bot(board);
	// go back to the menu
	start();
}

void go_to_rules()
{
	// print rules
	print_rules();
	// print menu and handle actions
	print_menu();
	handle_action();
}

void print_rules()	
{
	// rules
	system("CLS");
	cout << "Rules:" << endl;
	cout << "*Players take turns putting their marks in empty squares. " << 
		"\n*The first player to get 3 of his/her marks in a row(up, down, across, or diagonally) is the winner. " << 
		"\n*When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie." << endl;
	cout << "Source: exploratorium.edu" << endl << endl;
	
	cout << "How to play:" << endl;
	cout << "X starts. First player inputs coordinates of a move to place giving row and column as a number. \nExample: to place move like shown: " << endl;

	// example board 
	char board_example[3][3] = { {' ', ' ', ' '}, {' ', ' ', 'X'}, {' ', ' ', ' '} };
	print_board(board_example);
	
	cout << "You need to input 12. \n1 - first row, \n2 - second column. \nWe number from zero to two." << endl;
	cout << "It may be tricky but we believe you can get used to it. :)" << endl;
	
	cout << "After X's move, O can make its move. And so on. \nYou can't overwrite already marked spot or undo your move." << endl;
	cout << endl;
}

void quit()
{
	// quit the app
	system("CLS");
	cout << "Have a nice day! :) " << endl;
	exit(0);
}