// GSP 480 week 1 iLab
// written by Chris Randall

#include "stdafx.h"
#include "puzzleManager.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	bool running;
	int boardSize, shuffleTimes;
	string mainInput;
	do {
		cout << "Enter a single number to indicate how large youwant the puzzle \n to be (i.e. entering 3 will output a 3x3 board)" << endl;
		cout << "The number must be larger than 1" << endl;
		//getline(cin, mainInput);
		//boardSize = (int)mainInput[0];
		cin >> boardSize;
		if (boardSize < 2)
			cout << "Invalid input" << endl; 
	} while (boardSize < 2);
	Puzzle puzzleGame(boardSize);
	
	cout << "How many times would you like to shuffle the board?" << endl;
	cin >> shuffleTimes;
	puzzleGame.shuffleBoard(shuffleTimes);
	cout << "This was the starter board: " << endl;
	puzzleGame.drawBoard(puzzleGame.startBoard);

	do{
		puzzleGame.play();
		running = puzzleGame.isRunning();
	} while (running);
	return 0;
}

