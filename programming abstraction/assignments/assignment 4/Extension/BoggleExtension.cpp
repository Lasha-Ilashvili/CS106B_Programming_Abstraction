/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "hashmap.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void playGame();
Vector<string> boggleChoice();
string forceConfig(int size);
string shuffle(Vector<string>& v);
void addLetters(string letters, Grid<char>& board);
void allPossibleWords(Lexicon& lex, Grid<char>& board, int size, HashMap<string, Grid<bool>>& allWords);
void userInput(Lexicon& lex, Grid<char>& board, int size, HashMap<string, Grid<bool>>& allWords);
void pcInput(HashMap<string, Grid<bool>>& allWords);
void resetGame(string& letters, Grid<char>& board);

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
	playGame();
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]

/*
 * Function: getYesOrNo
 * Usage: getYesOrNo(string question);
 * -----------------
 * Prompts user for yes or no.
 */

bool getYesOrNo(string question = "") {
	while(true) {
		string ans = toLowerCase( getLine( question ) );
		if(ans[0] == 'y') {
			return true;
		} else if(ans[0] == 'n') { 
			break;
		}
		cout<<"Please answer yes or no."<<endl;
	}
	return false;
}

/*
 * Function: boggleQuestion
 * Usage: boggleQuestion();
 * -----------------
 * Lets user to choose Boggle size.
 */

bool boggleQuestion() {
	cout<<endl;
	cout<<"You can choose standard Boggle (4x4 grid)"<<endl;
	cout<<"Or Big Boggle (5x5)."<<endl;
	return getYesOrNo("Would you like Big Boggle? ");
}

/*
 * Function: configQuestion
 * Usage: configQuestion();
 * -----------------
 * Lets user set the board to their specification.
 */

bool configQuestion() {
	cout<<endl;
	cout<<"I'll give you a chance to set up the board to your specification,"<<endl; 
	cout<<"Which makes it easier to confirm your boggle program is working."<<endl;
	return getYesOrNo("Do you want to force the board configuration? ");
}

/*
 * Function: configMessage, userMessage
 * Usage: configMessage(int size), userMessage();
 * -----------------
 * These two functions below are needed for instructions given to the user.
 */

void configMessage(int size) {
	cout<<endl;
	cout<<"Enter a "<<size<<"-character string to identify which letters you want on the cubes."<<endl;
	cout<<"The first "<<sqrt(double(size))<<" letters are the cubes on the top row from left to right,"<<endl;
	cout<<"The next "<<sqrt(double(size))<<" letters are the second row, and so on."<<endl;
	cout<<"Enter the string: ";
}

void userMessage() {
	cout<<endl;
	cout<<"Ok, take all the time you want and find all the words you can!"<<endl;  
	cout<<"Signal that you're finished by entering an empty line."<<endl<<endl;	
}

/*
 * Function: playGame
 * Usage: playGame();
 * -----------------
 * Calls other functions. Manages all the operations in the game.
 */

void playGame() {

	/* Set up */
	Lexicon lex("EnglishWords.dat");
	HashMap<string, Grid<bool>> allWords;
	Vector<string> v = boggleChoice();
	int size = sqrt(double(v.size()));
	Grid<char> board(size, size);
	string letters = "";

	/* Gameplay */
	while(true) {
		drawBoard(size, size);

		if(configQuestion()) {
			letters = forceConfig(v.size());
		} else {
			letters = shuffle(v);
		}

		addLetters(letters, board);
		allPossibleWords(lex, board, letters.length(), allWords);

		userInput(lex, board, letters.length(), allWords);
		pcInput(allWords);

		if(!getYesOrNo("Would you like to play again? ")) {
			cout<<endl;
			break;
		}

		
		resetGame(letters, board);

	}

}

/*
 * Function: fillVec
 * Usage: fillVec(Vector<string>& v, const string boggle[], int size);
 * -----------------
 * Copies elements from array to Vector.
 */

void fillVec(Vector<string>& v, const string boggle[], int size) {
	for(int i = 0; i < size; i++) {
		v+=boggle[i];
	}
}

/*
 * Function: boggleChoice
 * Usage: boggleChoice();
 * -----------------
 * Sets up board either for 4x4 of 5x5 size.
 */

Vector<string> boggleChoice() {
	Vector<string> v;
	
	if(boggleQuestion()) {
		fillVec(v, BIG_BOGGLE_CUBES, sizeof(BIG_BOGGLE_CUBES)/sizeof(string));
	} else {
		fillVec(v, STANDARD_CUBES, sizeof(STANDARD_CUBES)/sizeof(string));
	}

	return v;
}

/*
 * Function: forceConfig
 * Usage: forceConfig(int size);
 * -----------------
 * Asks user for 16 character - sized string, which will later fill the board.
 */

string forceConfig(int size) {
	configMessage(size);
	string letters = "";

	while(true) {
		letters = toUpperCase(getLine());
		if(letters.length() >= size) {
			break;
		}
		cout<<"String must include "<<size<<" characters! Try again: ";
	}

	return letters.substr(0, size);
}

/*
 * Function: shuffle
 * Usage: shuffle(Vector<string>& v);
 * -----------------
 * If user refused manual insertion of characters, function shuffles elements in vector - 
 * Cubes themselves and which of their 6 sides are facing up.
 */

string shuffle(Vector<string>& v) {
	string letters = "";
	for(int i = 0; i < v.size(); i++) {
		int r = randomInteger(i, v.size() - 1);
		if(r != i) {
			/* Cube placement shuffle */
			string temp = v[i];
			v[i] = v[r];
			v[r] = temp;
		}
		/* Each cube's side shuffle */
		int index = randomInteger(0, v[i].length() - 1);
		letters += v[i].at(index);
	}
	return letters;
}

/*
 * Function: addLetters
 * Usage: addLetters(string letters, Grid<char>& board);
 * -----------------
 * Either way user manually entered characters or it was shuffled by program,
 * One string is passed as a parameter, which then is used to fill the board and grid.
 */

void addLetters(string letters, Grid<char>& board) {
	/* In this and other Grid iteration related functions, I used One for loop + variables */

	int size = letters.length(), row = -1; // row is initialized to -1
	int sqrtSize = sqrt(double(size)); // Size is 16 so sqrtSize is equal to 4 (representing 4x4 board)

	for(int i = 0; i < size; i++) {
		int col = i % sqrtSize; // i % sqrtSize iterates through 0 to 3 (inclusively)

		if(col == 0) { // every time (including first iteration) col variable is equal to 0, row value is appended by one
			row++;
		}

		labelCube(row, col, letters[i]);
		board[row][col] = letters[i];
	}
}

/*
 * Function: neighbors
 * Usage: neighbors(string s, int row, int col, Grid<char>& board, Grid<bool>& used, Lexicon& lex, HashMap<string, Grid<bool>>& allWords);
 * -----------------
 * Does an exhaustive recursive search to find all possible words on the board.
 * If formed prefix isn't valid search stops and other paths are explored.
 */

void neighbors(string s, int row, int col, Grid<char>& board, Grid<bool>& used, Lexicon& lex, HashMap<string, Grid<bool>>& allWords) {
	if(!lex.containsPrefix(s)) {
		return;
	}

	if(s.length()>=4 && lex.contains(s) && !allWords.containsKey(s)) {
		allWords[s] = used;
	}	

	for(int i = -1; i <= 1; i++) {
		for(int j = -1; j <= 1; j++) {
			int x = row + i;
			int y = col + j;
			if(board.inBounds(x, y) && !used[x][y]) {

				used[x][y] = 1;
				
				neighbors(s+board[x][y], x, y, board, used, lex, allWords);
				
				used[x][y] = 0;

			}
		}
	}

}

/*
 * Function: allPossibleWords
 * Usage: allPossibleWords(Lexicon& lex, Grid<char>& board, int size, HashMap<string, Grid<bool>>& allWords);
 * -----------------
 * Iterates through grid. For every letter explores all the possible paths.
 */

void allPossibleWords(Lexicon& lex, Grid<char>& board, int size, HashMap<string, Grid<bool>>& allWords) {
	Grid<bool> used (board.numRows(), board.numCols());
	int sqrtSize = sqrt(double(size)), row = -1;

	for(int i = 0; i < size; i++) {
		int col = i % sqrtSize;

		if(col == 0) {
			row++;
		}

		used[row][col] = 1;

		neighbors(string("")+board[row][col], row, col, board, used, lex, allWords);

		used[row][col] = 0;

	}
}

/*
 * Function: highLight
 * Usage: highLight(Grid<bool>& used);
 * -----------------
 * Highlights letters on the board
 */

void highLight(Grid<bool>& used) {

	/* Highlighting every used letter */
	for(int r=0; r<used.numRows(); r++) {
		for(int c=0; c<used.numCols(); c++) {
			if(used[r][c]) {
				highlightCube(r, c, true);
			}
		}
	}

	/* Pause in-between */
	pause(400);

	/* Removes highlights */
	for(int r=0; r<used.numRows(); r++) {
		for(int c=0; c<used.numCols(); c++) {
			if(used[r][c]) {
				highlightCube(r, c, false);
			}
		}
	}

}

/*
 * Function: userInput
 * Usage: userInput(Lexicon& lex, Grid<char>& board, int size, HashMap<string, Grid<bool>>& allWords);
 * -----------------
 * Manages user's inputed words, checks if they can be formed, their size is >= 4 and are valid English words.
 * Displays appropriate messages otherwise.
 */

void userInput(Lexicon& lex, Grid<char>& board, int size, HashMap<string, Grid<bool>>& allWords) {
	userMessage();
	Set<string> used;
	while(true) {
		string word = toUpperCase(getLine("Enter a word: "));

		if(word.empty()) {
			break;
		}

		if(word.length() < 4) {
			cout<<"I'm sorry, but we have our standards."<<endl;
			cout<<"That word doesn't meet the minimum word length."<<endl;
		} else if(used.contains(word)) {
			cout<<"You've already guessed that!"<<endl;
		} else if(!allWords.containsKey(word)) {				
			cout<<"You can't make that word!"<<endl;
		} else {
			used+=word;
			highLight(allWords[word]);
			allWords.remove(word);
			recordWordForPlayer(word, HUMAN);
		}

	}

	cout<<endl;
}

/*
 * Function: pcInput
 * Usage: pcInput(HashMap<string, Grid<bool>>& allWords);
 * -----------------
 * Iterates through HashMap. Displays all remained words.
 */

void pcInput(HashMap<string, Grid<bool>>& allWords) {
	foreach(string word in allWords) {
		recordWordForPlayer(word, COMPUTER);
		allWords.remove(word);
	}
}

/*
 * Function: resetGame
 * Usage: resetGame(string& letters, Grid<char>& board);
 * -----------------
 * Resets all stored data for the new game.
 */

void resetGame(string& letters, Grid<char>& board) {
	letters.clear();
	Grid<char> newBoard(board.numRows(), board.numCols());
	board = newBoard;
}