#pragma once
#include "stdafx.h"
#include "puzzleManager.h"

// shuffles board based on user input
void Puzzle::shuffleBoard(int timesToShuffle) {
	maxDepth = timesToShuffle + 100;
	for (int i = 0; i < timesToShuffle; ++i) {
		previousBoard = puzzleBoard;
		figureOutChoices(puzzleBoard);
		bool goodPos = false;
		int toSkip = rand()% moveChoices.me.size();
		setNewBoard(moveChoices.me[toSkip]);
		if (puzzleBoard.me == previousBoard.me)
			i--;
	}
	if (puzzleBoard.me == wonBoard.me)
		shuffleBoard(timesToShuffle);
	startBoard.me = puzzleBoard.me;
}

// displays the passed vector as a grid
void Puzzle::drawBoard(board board) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int currentPos = (x * n) + y;
			if (board.me[currentPos] != 00)
				printf("%02i ", board.me[currentPos]);
			else
				printf("   ");
		}
		cout << endl;
	}
}

// draws a temporary board without storing any of the changes
// to be used for potential moves.
void Puzzle::drawTempBoard(int direction) {
	board tempBoard(puzzleBoard.me);
	int tempPos = posToSkip;
	switch (direction) {
	case(UP) :
		posToSkip -= n;
		//moveUp = puzzleBoard;
		//swapPositions(moveUp, posToSkip, tempPos);
		break;
	case(DOWN) :
		posToSkip += n;
		//moveDown = puzzleBoard;
		//swapPositions(moveDown, posToSkip, tempPos);
		break;
	case(LEFT) :
		posToSkip -= 1;
		//moveLeft = puzzleBoard;
		//swapPositions(moveLeft, posToSkip, tempPos);
		break;
	case(RIGHT) :
		posToSkip += 1;
		//moveRight = puzzleBoard;
		//swapPositions(moveRight, posToSkip, tempPos);
		break;
	}
	swapPositions(tempBoard, posToSkip, tempPos);
	drawBoard(tempBoard);
	posToSkip = tempPos;
	cout << endl;
}

board Puzzle::setChoiceBoard(int direction, board currentB) {
	board tempBoard = currentB;
	int tempPos = posToSkip;
	switch (direction) {
	case(UP) :
		tempPos -= n;
		//moveUp.me.clear();
		//moveUp = currentBoard;
		//swapPositions(moveUp, posToSkip, tempPos);
		break;
	case(DOWN) :
		tempPos += n;
		//moveDown.me.clear();
		//moveDown = currentBoard;
		//swapPositions(moveDown, posToSkip, tempPos);
		break;
	case(LEFT) :
		tempPos -= 1;
		//moveLeft.me.clear();
		//moveLeft = currentBoard;
		//swapPositions(moveLeft, posToSkip, tempPos);
		break;
	case(RIGHT) :
		tempPos += 1;
		//moveRight.me.clear();
		//moveRight = currentBoard;
		//swapPositions(moveRight, posToSkip, tempPos);
		break;
	}
	swapPositions(tempBoard, posToSkip, tempPos);
	return tempBoard;
}

// sets the main board based on user input 
void Puzzle::setNewBoard(int direction) {
	int tempPos = posToSkip;
	switch (direction) {
	case(UP) :
		posToSkip -= n;
		moveUp = puzzleBoard;
		swapPositions(moveUp, posToSkip, tempPos);
		puzzleBoard = moveUp;
		break;
	case(DOWN) :
		posToSkip += n;
		moveDown = puzzleBoard;
		swapPositions(moveDown, posToSkip, tempPos);
		puzzleBoard = moveDown;
		break;
	case(LEFT) :
		posToSkip -= 1;
		moveLeft = puzzleBoard;
		swapPositions(moveLeft, posToSkip, tempPos);
		puzzleBoard = moveLeft;
		break;
	case(RIGHT) :
		posToSkip += 1;
		moveRight = puzzleBoard;
		swapPositions(moveRight, posToSkip, tempPos);
		puzzleBoard = moveRight;
		break;
	}
}

// figures out how many potential moves the user has
vector<board> Puzzle::figureOutChoices(board currentBoard) {
	vector<board> toReturn;
	for (int i = 0; i < currentBoard.me.size(); ++i) {
		if (currentBoard.me[i] == 00) {
			posToSkip = i;
			break;
		}
	}
	moveChoices.me.clear();
	if (posToSkip == topLeftCorner) {		// top left corner
		moveChoices.me.push_back(DOWN);
		moveChoices.me.push_back(RIGHT);
	}
	else if(posToSkip == topRightCorner) {		// top right corner
		moveChoices.me.push_back(DOWN);
		moveChoices.me.push_back(LEFT);
	}
	else if (posToSkip == bottomLeftCorner) {	// bottom left corner
		moveChoices.me.push_back(UP);
		moveChoices.me.push_back(RIGHT);
	}
	else if (posToSkip == bottomRightCorner) {	// bottom right corner
		moveChoices.me.push_back(UP);
		moveChoices.me.push_back(LEFT);
	}
	else if (posToSkip < n) {						// top edge
		moveChoices.me.push_back(DOWN);
		moveChoices.me.push_back(LEFT);
		moveChoices.me.push_back(RIGHT);
	}
	else if (posToSkip > bottomRightCorner - n) {	// bottom edge
		moveChoices.me.push_back(UP);
		moveChoices.me.push_back(LEFT);
		moveChoices.me.push_back(RIGHT);
	}
	else if (posToSkip % n == 0) {					// left edge
		moveChoices.me.push_back(UP);
		moveChoices.me.push_back(DOWN);
		moveChoices.me.push_back(RIGHT);
	}
	else if (posToSkip % n == n - 1) {				// right edge
		moveChoices.me.push_back(UP);
		moveChoices.me.push_back(DOWN);
		moveChoices.me.push_back(LEFT);
	}
	else {
		moveChoices.me.push_back(UP);
		moveChoices.me.push_back(DOWN);
		moveChoices.me.push_back(LEFT);
		moveChoices.me.push_back(RIGHT);
	}
	for (int i = 0; i < moveChoices.me.size(); ++i) {
		toReturn.push_back(setChoiceBoard(moveChoices.me[i], currentBoard));
	}

	return toReturn;
}

// draws the potential choices for the users next move
void Puzzle::drawChoices() {
	//figureOutChoices();
	cout << "Here are your choices for the next move:" << endl;
	for (int i = 0; i < moveChoices.me.size(); ++i) {
		cout << "(" << i + 1 << ")" << endl;
		drawTempBoard(moveChoices.me[i]);
	}
}

// main draw function to be called by main
void Puzzle::draw() {
	//cout << "\n\nHere's the current board" << endl;
	drawBoard(puzzleBoard.me);
	cout << endl;
	drawChoices();
}

// gets input and calls setNewBoard to handle it
void Puzzle::input() {
	bool validInput = true;
	int input;
	do {
		cout << "choose one of the boards above" << endl;
		cin >> input;
	} while (input > moveChoices.me.size());
	turns++;
	//previousBoardList.push_back(puzzleBoard);
	setNewBoard(moveChoices.me[input - 1]);

}

// initializes the puzzle board
void Puzzle::createBoard() {
	wonBoard.me.clear();
	puzzleBoard.me.clear();
	for (int i = 1; i <= (n * n) - 1; ++i) {
		puzzleBoard.me.push_back(i);
		wonBoard.me.push_back(i);
	}
	puzzleBoard.me.push_back(0);
	wonBoard.me.push_back(0);
	posToSkip = (n*n) - 1;
}

// randomizes board. Is replaced by shuffleBoard
void Puzzle::randomizeBoard() {
	createBoard();
	for (int i = 0; i < puzzleBoard.me.size(); ++i) {
		int randPos = rand() % puzzleBoard.me.size();
		swapBoardPositions(i, randPos);
	}
	puzzleBoard.me.push_back(0);
	posToSkip = (n*n) - 1;
}

// swaps the numbers of two positions in the main puzzleBoard
void Puzzle::swapBoardPositions(int pos1, int pos2) {
	int tempInt = puzzleBoard.me[pos1];
	puzzleBoard.me[pos1] = puzzleBoard.me[pos2];
	puzzleBoard.me[pos2] = tempInt;
}

// swaps two numbers in the passed board
void Puzzle::swapPositions(board &board, int pos1, int pos2) {
	int tempInt = board.me[pos1];
	board.me[pos1] = board.me[pos2];
	board.me[pos2] = tempInt;
}

// checks if win conditions have been met
void Puzzle::checkWin() {
	if (solved) {
		cout << "Here's a list of the steps that were took" << endl;
		for (int i = 0; i < solutionPath.size(); ++i) {
			cout << "Step " << i+1 << ":" << endl;
			drawBoard(solutionPath[i]);
			cout << endl;
		}
		cout << "Total nodes examined: " << totalBoardStates << endl;
		getchar();
		getchar();
		getchar();
		running = false;
	}
}

bool Puzzle::isRunning() {
	return running;
}

void Puzzle::play() {
	//draw();
	//input();
	//checkWin();
	//currentDepth = 0;
	//while (!solved && (maxdepth< ? ? ))
	while (!solved && currentDepth < maxDepth) {
		puzzleBoard = startBoard;
		//	resetboard();
		//  createBoard();
		//	solutionpath = DFS(maxdepth, shuffledboard);
		// previousBoard = puzzleBoard;
		bool solutionFound = IDFS(currentDepth, puzzleBoard);
		currentDepth++;
		if (solutionFound)
			solved = true;
	}
	checkWin();
}

bool Puzzle::IDFS(int depth, board currentBoard) {
	//nodes_examined++;
	totalBoardStates++;
	//pathtosolution.add(currentboard);
	solutionPath.push_back(currentBoard);
	//If(currentboard == solvedboard)
	if (currentBoard.me == wonBoard.me) {
		return true;
	}
	//if (depth == 0)
	if (depth == 0) {
		//	pathtosolution.remove(currentboard);
		solutionPath.pop_back();
		return false;
		//}
	}
	//cout << endl << "depth: " << depth << " out of " << currentDepth << endl;
	//drawBoard(currentBoard);

	//listofmoves = generatemoves();
	vector<board> listOfMoves = figureOutChoices(currentBoard);
	//for (board in listofmoves)
	for (int i = 0; i < listOfMoves.size(); ++i) {
		//	recursepath = DFS(depth - 1, board));
		bool recurseSolved = IDFS(depth - 1, listOfMoves[i]);
		//if (recursepath)
		if (recurseSolved)
			return true;
	}
	solutionPath.pop_back();
	return false;
}

