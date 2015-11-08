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

struct board {
public:
	bool lookedAt;
	vector<int> me;
	board() {}
	board(vector<int> passed) : me(passed), lookedAt(false) {}
	~board(){}
};

class Puzzle {
	//week 1
	bool running;
	int n;
	int currentNum = 00;
	int posToSkip;
	int turns;
	board moveChoices;
	board moveRight, moveLeft, moveUp, moveDown;
	board puzzleBoard, previousBoard, wonBoard;
	vector<board> previousBoardList;
	int topLeftCorner, bottomLeftCorner, bottomRightCorner, topRightCorner;
	//week 2
	bool solved; 
	int totalBoardStates;
	int maxDepth, currentDepth;
	board currentBoard;
	vector<board> solutionPath, recursePath;
	board * choiceBoards[4];
	
public:
	board startBoard;
	Puzzle() : n(4) {}
	Puzzle(int n) : n(n), running(true), turns(0), solved(false), totalBoardStates(0), maxDepth(0), currentDepth(0) {
		srand(clock());
		createBoard();
		currentBoard = puzzleBoard;
		topLeftCorner = 0;
		topRightCorner = n - 1;
		bottomRightCorner = (n * n)-1;
		bottomLeftCorner = bottomRightCorner - topRightCorner; 
		choiceBoards[0] = &moveUp;
		choiceBoards[1] = &moveDown;
		choiceBoards[2] = &moveLeft;
		choiceBoards[3] = &moveRight;
	}
	~Puzzle(){}

	void shuffleBoard(int timesToShuffle);
	void drawBoard(board board);
	void drawTempBoard(int direction);
	void setNewBoard(int direction);
	void drawChoices();
	
	void draw();
	void input();
	vector<board> figureOutChoices(board);
	void createBoard();
	void randomizeBoard();
	//void changePosToSkip(int);
	void swapPositions(board &board, int pos1, int pos2);
	void swapBoardPositions(int pos1, int pos2);
	void checkWin();
	bool isRunning();
	board setChoiceBoard(int direction, board);

	// week 2
	void play();
	bool  IDFS(int depth, board currentBoard);
};