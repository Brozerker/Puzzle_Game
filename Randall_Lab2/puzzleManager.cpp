#pragma once
#include "stdafx.h"
#include "puzzleManager.h"

// shuffles board based on user input
void Puzzle::shuffleBoard(int timesToShuffle) {
	maxDepth = timesToShuffle;
	for (int i = 0; i < timesToShuffle; ++i) {
		previousBoard = puzzleBoard;
		figureOutChoices(puzzleBoard);
		bool goodPos = false;
		int toSkip = rand()% moveChoices.size();
		setNewBoard(moveChoices[toSkip]);
		if (puzzleBoard == previousBoard)
			i--;
	}
	if (puzzleBoard == wonBoard)
		shuffleBoard(timesToShuffle);
}

// displays the passed vector as a grid
void Puzzle::drawBoard(vector<int> board) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			int currentPos = (x * n) + y;
			if (board[currentPos] != 00)
				printf("%02i ", board[currentPos]);
			else
				printf("   ");
		}
		cout << endl;
	}
}

// draws a temporary board without storing any of the changes
// to be used for potential moves.
void Puzzle::drawTempBoard(int direction) {
	vector<int> tempBoard(puzzleBoard);
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

void Puzzle::setChoiceBoard(int direction) {
	int tempPos = posToSkip;
	switch (direction) {
	case(UP) :
		tempPos -= n;
		moveUp.clear();
		moveUp = currentBoard;
		swapPositions(moveUp, posToSkip, tempPos);
		break;
	case(DOWN) :
		tempPos += n;
		moveDown.clear();
		moveDown = currentBoard;
		swapPositions(moveDown, posToSkip, tempPos);
		break;
	case(LEFT) :
		tempPos -= 1;
		moveLeft.clear();
		moveLeft = currentBoard;
		swapPositions(moveLeft, posToSkip, tempPos);
		break;
	case(RIGHT) :
		tempPos += 1;
		moveRight.clear();
		moveRight = currentBoard;
		swapPositions(moveRight, posToSkip, tempPos);
		break;
	}

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
void Puzzle::figureOutChoices(vector<int> currentBoard) {
	for (int i = 0; i < currentBoard.size(); ++i) {
		if (currentBoard[i] == 00) {
			posToSkip = i;
			break;
		}
	}
	moveChoices.clear();
	if (posToSkip == topLeftCorner) {		// top left corner
		moveChoices.push_back(DOWN);
		moveChoices.push_back(RIGHT);
	}
	else if(posToSkip == topRightCorner) {		// top right corner
		moveChoices.push_back(DOWN);
		moveChoices.push_back(LEFT);
	}
	else if (posToSkip == bottomLeftCorner) {	// bottom left corner
		moveChoices.push_back(UP);
		moveChoices.push_back(RIGHT);
	}
	else if (posToSkip == bottomRightCorner) {	// bottom right corner
		moveChoices.push_back(UP);
		moveChoices.push_back(LEFT);
	}
	else if (posToSkip < n) {						// top edge
		moveChoices.push_back(DOWN);
		moveChoices.push_back(LEFT);
		moveChoices.push_back(RIGHT);
	}
	else if (posToSkip > bottomRightCorner - n) {	// bottom edge
		moveChoices.push_back(UP);
		moveChoices.push_back(LEFT);
		moveChoices.push_back(RIGHT);
	}
	else if (posToSkip % n == 0) {					// left edge
		moveChoices.push_back(UP);
		moveChoices.push_back(DOWN);
		moveChoices.push_back(RIGHT);
	}
	else if (posToSkip % n == n - 1) {				// right edge
		moveChoices.push_back(UP);
		moveChoices.push_back(DOWN);
		moveChoices.push_back(LEFT);
	}
	else {
		moveChoices.push_back(UP);
		moveChoices.push_back(DOWN);
		moveChoices.push_back(LEFT);
		moveChoices.push_back(RIGHT);
	}
	for (int i = 0; i < moveChoices.size(); ++i) {
		setChoiceBoard(moveChoices[i]);
	}
}

// draws the potential choices for the users next move
void Puzzle::drawChoices() {
	//figureOutChoices();
	cout << "Here are your choices for the next move:" << endl;
	for (int i = 0; i < moveChoices.size(); ++i) {
		cout << "(" << i + 1 << ")" << endl;
		drawTempBoard(moveChoices[i]);
	}
}

// main draw function to be called by main
void Puzzle::draw() {
	//cout << "\n\nHere's the current board" << endl;
	drawBoard(puzzleBoard);
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
	} while (input > moveChoices.size());
	turns++;
	previousBoardList.push_back(puzzleBoard);
	setNewBoard(moveChoices[input - 1]);

}

// initializes the puzzle board
void Puzzle::createBoard() {
	wonBoard.clear();
	puzzleBoard.clear();
	for (int i = 1; i <= (n * n) - 1; ++i) {
		puzzleBoard.push_back(i);
		wonBoard.push_back(i);
	}
	puzzleBoard.push_back(0);
	wonBoard.push_back(0);
	posToSkip = (n*n) - 1;
}

// randomizes board. Is replaced by shuffleBoard
void Puzzle::randomizeBoard() {
	createBoard();
	for (int i = 0; i < puzzleBoard.size(); ++i) {
		int randPos = rand() % puzzleBoard.size();
		swapBoardPositions(i, randPos);
	}
	puzzleBoard.push_back(0);
	posToSkip = (n*n) - 1;
}

// swaps the numbers of two positions in the main puzzleBoard
void Puzzle::swapBoardPositions(int pos1, int pos2) {
	int tempInt = puzzleBoard[pos1];
	puzzleBoard[pos1] = puzzleBoard[pos2];
	puzzleBoard[pos2] = tempInt;
}

// swaps two numbers in the passed board
void Puzzle::swapPositions(vector<int> &board, int pos1, int pos2) {
	int tempInt = board[pos1];
	board[pos1] = board[pos2];
	board[pos2] = tempInt;
}

// checks if win conditions have been met
void Puzzle::checkWin() {
	//bool won = true;
	//vector<int> win(puzzleBoard.size() - 1);
	//for (int i = 0; i < win.size(); ++i){
	//	if (wonBoard[i] != puzzleBoard[i]) {
	//		won = false;
	//		break;
	//	}
	//}
	if (solved) {
		cout << "YOU WIN!" << endl;
		cout << "It took " << turns << " turns to finish" << endl;
		getchar();
		cout << "Here's a list of the steps you took" << endl;
		for (int i = 0; i < solutionPath.size(); ++i) {
			cout << "Step " << i + 1 << ":" << endl;
			drawBoard(solutionPath[i]);
			cout << endl;
		}
		getchar();
	}
}

bool Puzzle::isRunning() {
	return running;
}

void Puzzle::play() {
	//draw();
	//input();
	//checkWin();
	//while (!solved && (maxdepth< ? ? ))
	while (!solved && currentDepth < maxDepth) {
		//	resetboard();
		//createBoard();
		//	solutionpath = DFS(maxdepth, shuffledboard);
		bool solutionFound = IDFS(currentDepth, puzzleBoard);
			//	maxdepth++;
		currentDepth++;
		if (solutionFound)
			solved = true;
	}
	checkWin();
}

bool Puzzle::IDFS(int depth, vector<int> currentBoard) {
	this->currentBoard = currentBoard;
	//nodes_examined++;
	totalBoardStates++;
	//pathtosolution.add(currentboard);
	solutionPath.push_back(currentBoard);
	//If(currentboard == solvedboard)
	if (currentBoard == wonBoard) {
		return true;
	}
	//if (depth == 0)
	if (depth == maxDepth) {
		//	pathtosolution.remove(currentboard);
		solutionPath.pop_back();
		return false;
		//}
	}

	//listofmoves = generatemoves();
	figureOutChoices(currentBoard);
	//for (board in listofmoves)
	for (int i = 0; i < moveChoices.size(); ++i) {
		//	recursepath = DFS(depth - 1, board));
		bool recurseSolved = IDFS(depth + 1, *choiceBoards[moveChoices[i]]);
		//if (recursepath)
		if (recurseSolved)
			return true;
	}
	for (int i = 0; i < solutionPath.size() - 1; ++i) {
		if (solutionPath[i] == currentBoard) {
			vector<int> temp = solutionPath[i];
			solutionPath[i] = solutionPath[i + 1];
			solutionPath[i + 1] = temp;
		}
	}
	solutionPath.pop_back();
	return false;
}

