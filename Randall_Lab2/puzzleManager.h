// PuzzleManger holds all details for the game board
// written by Chris Randall

#pragma once

#include "defines.h"
#include <vector>
#include <sstream>
#include <string>
#include <time.h>
#include <iostream>
using namespace std;

class Puzzle {
	//week 1
	bool running;
	int n;
	int currentNum = 00;
	int posToSkip;
	int turns;
	vector<int> moveChoices;
	vector<int> moveRight, moveLeft, moveUp, moveDown;
	vector<int> puzzleBoard, previousBoard, wonBoard;
	vector<vector<int>> previousBoardList;
	int topLeftCorner, bottomLeftCorner, bottomRightCorner, topRightCorner;
	//week 2
	bool solved; 
	int totalBoardStates;
	int maxDepth, currentDepth;
	vector<vector<int>> solutionPath;
	
public:
	Puzzle() : n(4) {}
	Puzzle(int n) : n(n), running(true), turns(0), solved(false), totalBoardStates(0), maxDepth(0), currentDepth(0) {
		srand(clock());
		createBoard();
		topLeftCorner = 0;
		topRightCorner = n - 1;
		bottomRightCorner = (n * n)-1;
		bottomLeftCorner = bottomRightCorner - topRightCorner; 
	}
	~Puzzle(){}

	void shuffleBoard(int timesToShuffle);
	void drawBoard(vector<int> board);
	void drawTempBoard(int direction);
	void setNewBoard(int direction);
	void drawChoices();
	
	void draw();
	void input();
	void figureOutChoices();
	void createBoard();
	void randomizeBoard();
	//void changePosToSkip(int);
	void swapPositions(vector<int> &board, int pos1, int pos2);
	void swapBoardPositions(int pos1, int pos2);
	void checkWin();
	bool isRunning();

	// week 2
	void play();
	vector<int> IDFS(int depth, vector<int> currentBoard);
};