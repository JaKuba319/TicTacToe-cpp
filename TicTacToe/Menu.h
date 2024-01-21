#pragma once

/*
start() starts the application, initializes the menu and allows user to use it
*/
void start();

/*
handle_action() reads, validates and executes actions from input
*/
void handle_action();

/*
print_menu() prints a menu (list of actions) with navigation instructions
*/
void print_menu();

/*
get_action_number() reads and returns action from input, checks if input is a integer.
This functions trims non numeric characters after numeric input

@return user's input if it is int, otherwise 0
*/
int get_action_number();

/*
validate_action_number(int) checks if there is an action with number like parameter

@param action_number potential action's numer to validate

@return true if there is an action with specified action_number, otherwise false
*/
bool validate_action_number(int action_number);

/*
execute_action(int) executes action with number specified in parameter

@param action_number action's numer to be executed
*/
void execute_action(int action_number);

/*
go_to_play() is used to navigate to the game
*/
void go_to_play();

/*
go_to_play() is used to navigate to the game with the bot
*/
void go_to_play_with_bot();

/*
go_to_rules() is used to print rules and allow user to use menu
*/
void go_to_rules();

/*
print_rules() prints rules
*/
void print_rules();

/*
quit() quits from the app
*/
void quit();