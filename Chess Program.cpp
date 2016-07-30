#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

const int NUM_ROWS = 8;
const int NUM_COLS = 8;

string player1 = "";
string player2 = "";


// **************** CLASS: CELL *******************
class Cell {
	char piece;
	char color;
public:
	Cell();
	void place(char color, char piece);
	string getPiece();

};

Cell::Cell() {
	piece = ' ';
	color = ' ';
}

void Cell::place(char newColor, char newPiece) {
	assert((newColor == 'W') || (newColor == 'B') || (newColor == ' '));
	color = newColor;
	assert((newPiece == 'R') || (newPiece == 'K') ||
		(newPiece == 'B') || (newPiece == 'Q') ||
		(newPiece == 'K') || (newPiece == 'N') ||
		(newPiece == 'P') || (newPiece == ' '));
	piece = newPiece;

}

string Cell::getPiece() {
	string result = "";
	result = result.append(1, color);
	result = result.append(1, piece);
	return result;
}

// **************** CLASS: BOARD *******************

class Board {
	Cell board[NUM_ROWS][NUM_COLS]; // <-- Not a good idea in the long run
	char boardRowHeader[1][9];
	void displayLine();
	string take(int row, int col);
	void place(int row, int col, char color, char piece);
	bool movePieceOneStep(string piece, string direction, int &row, int &col);
	bool cellEmpty(int toRow, int toCol, string piece);
	bool moveRook(int &row, int &col, string direction, int steps);
	bool movePawn(int &row, int &col, string direction, int steps);
	bool moveBishop(int &row, int &col, string direction, int steps);
	bool moveQueen(int &row, int &col, string direction, int steps);
	bool moveKing(int &row, int &col, string direction, int steps);
	bool moveKnight(int &row, int &col, string direction, int steps);
	bool kingOnBoard(char color);
	bool canTake(int row, int col, char color, string enemyPiece);
	int captureCounter = 0;
public:
	Board();
	Board(string command, int row, int col, char color, char piece);
	Board(string);
	void displayBoard();
	bool turn(int row, int col, string direction, int steps);
	string look(int toRow, int toCol);
	void buffer(string);
	bool checkForCheck(char);
	bool makeMove(char color);
};

Board::Board() {
		boardRowHeader[0][0] = ' ';
		boardRowHeader[0][1] = '0';
		boardRowHeader[0][2] = '1';
		boardRowHeader[0][3] = '2';
		boardRowHeader[0][4] = '3';
		boardRowHeader[0][5] = '4';
		boardRowHeader[0][6] = '5';
		boardRowHeader[0][7] = '6';
		boardRowHeader[0][8] = '7';

		board[0][0].place('B', 'R');
		board[0][1].place('B', 'N');
		board[0][2].place('B', 'B');
		board[0][3].place('B', 'Q');
		board[0][4].place('B', 'K');
		board[0][5].place('B', 'B');
		board[0][6].place('B', 'N');
		board[0][7].place('B', 'R');
		for (int c = 0; c < NUM_COLS; c++) {
			board[1][c].place('B', 'P');
		}

		board[NUM_ROWS - 1][0].place('W', 'R');
		board[NUM_ROWS - 1][1].place('W', 'N');
		board[NUM_ROWS - 1][2].place('W', 'B');
		board[NUM_ROWS - 1][4].place('W', 'K');
		board[NUM_ROWS - 1][3].place('W', 'Q');
		board[NUM_ROWS - 1][5].place('W', 'B');
		board[NUM_ROWS - 1][6].place('W', 'N');
		board[NUM_ROWS - 1][7].place('W', 'R');
		for (int c = 0; c < NUM_COLS; c++) {
			board[NUM_ROWS - 2][c].place('W', 'P');
		}
}

Board::Board(string command, int row, int col, char color, char piece) {
	if (command == "ONEPIECE") {
		board[row][col].place(color, piece);
		return;
	}
	else if (command == "NOPAWNS") {
		boardRowHeader[0][0] = ' ';
		boardRowHeader[0][1] = '0';
		boardRowHeader[0][2] = '1';
		boardRowHeader[0][3] = '2';
		boardRowHeader[0][4] = '3';
		boardRowHeader[0][5] = '4';
		boardRowHeader[0][6] = '5';
		boardRowHeader[0][7] = '6';
		boardRowHeader[0][8] = '7';

		board[0][0].place('B', 'R');
		board[0][1].place('B', 'N');
		board[0][2].place('B', 'B');
		board[0][3].place('B', 'Q');
		board[0][4].place('B', 'K');
		board[0][5].place('B', 'B');
		board[0][6].place('B', 'N');
		board[0][7].place('B', 'R');

	board[NUM_ROWS - 1][0].place('W', 'R');
	board[NUM_ROWS - 1][1].place('W', 'N');
	board[NUM_ROWS - 1][2].place('W', 'B');
	board[NUM_ROWS - 1][4].place('W', 'K');
	board[NUM_ROWS - 1][3].place('W', 'Q');
	board[NUM_ROWS - 1][5].place('W', 'B');
	board[NUM_ROWS - 1][6].place('W', 'N');
	board[NUM_ROWS - 1][7].place('W', 'R');
	}
	else {
		cout << "Invalid Command.";
		assert(false);
	}
}

Board::Board(string command) {
	if (command == "NOPAWNS") {
		boardRowHeader[0][0] = ' ';
		boardRowHeader[0][1] = '0';
		boardRowHeader[0][2] = '1';
		boardRowHeader[0][3] = '2';
		boardRowHeader[0][4] = '3';
		boardRowHeader[0][5] = '4';
		boardRowHeader[0][6] = '5';
		boardRowHeader[0][7] = '6';
		boardRowHeader[0][8] = '7';

		board[0][0].place('B', 'R');
		board[0][1].place('B', 'N');
		board[0][2].place('B', 'B');
		board[0][3].place('B', 'Q');
		board[0][4].place('B', 'K');
		board[0][5].place('B', 'B');
		board[0][6].place('B', 'N');
		board[0][7].place('B', 'R');

		board[NUM_ROWS - 1][0].place('W', 'R');
		board[NUM_ROWS - 1][1].place('W', 'N');
		board[NUM_ROWS - 1][2].place('W', 'B');
		board[NUM_ROWS - 1][4].place('W', 'K');
		board[NUM_ROWS - 1][3].place('W', 'Q');
		board[NUM_ROWS - 1][5].place('W', 'B');
		board[NUM_ROWS - 1][6].place('W', 'N');
		board[NUM_ROWS - 1][7].place('W', 'R');
	}
}

void Board::buffer(string command) {

	static Cell boardCopy[NUM_ROWS][NUM_COLS];
	static Cell boardCopy2[NUM_ROWS][NUM_COLS];
	if (command == "copy") {
		// make a copy of the board
		for (int rx = 0; rx < NUM_ROWS; rx++) {
			for (int cx = 0; cx < NUM_COLS; cx++) {
				boardCopy[rx][cx] = board[rx][cx];
			}
		}
	}
	else if (command == "paste") {
		// put the copy back into the board
		for (int rx = 0; rx < NUM_ROWS; rx++) {
			for (int cx = 0; cx < NUM_COLS; cx++) {
				board[rx][cx] = boardCopy[rx][cx];
			}
		}
	}
	else if (command == "copy2") {
		// put the copy back into the board
		for (int rx = 0; rx < NUM_ROWS; rx++) {
			for (int cx = 0; cx < NUM_COLS; cx++) {
				boardCopy2[rx][cx] = board[rx][cx];
			}
		}
	}
	else if (command == "paste2") {
		// put the copy back into the board
		for (int rx = 0; rx < NUM_ROWS; rx++) {
			for (int cx = 0; cx < NUM_COLS; cx++) {
				board[rx][cx] = boardCopy2[rx][cx];
			}
		}
	}
	else
		assert(false); // only copy and paste are valid here 

}

bool Board::kingOnBoard(char color) {
	string foundKing;
	if (color == 'W') {
		for (int r = 0; r < NUM_ROWS; r++) {
			for (int c = 0; c < NUM_COLS; c++) {
				foundKing = look(r, c);
				if (foundKing == "WK") { //
					//cout << "found king at: " << r << " " << c << endl; //
					return true;
				} //
			}
		}
	}
	else if (color == 'B') {
		for (int r = 0; r < NUM_ROWS; r++) {
			for (int c = 0; c < NUM_COLS; c++) {
				foundKing = look(r, c);
				if (foundKing == "BK")
					return true;
			}
		}
	}
	return false;
}

bool Board::canTake(int row, int col, char color, string enemyPiece) {
	buffer("copy");
		//cout << "Piece: " << enemyPiece << " (" << row << ", " << col << ")\n"; //TRACE
		if (enemyPiece.at(1) == 'R') {
			for (int steps = 1; steps < 8; steps++) { 
				if (turn(row, col, "N", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}

				 if (turn(row, col, "S", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "E", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "W", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
			} 
		}
		else if (enemyPiece.at(1) == 'Q') {
			for (int steps = 1; steps < 8; steps++) { 
				if (turn(row, col, "N", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					//displayBoard(); //QUEENTRACE
					buffer("paste");
				}
				 if (turn(row, col, "S", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "E", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "W", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "NE", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					//displayBoard(); //QUEENTRACE
					buffer("paste");
				}
				 if (turn(row, col, "NW", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "SE", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					//displayBoard(); //QUEENTRACE
					buffer("paste");
				}
				 if (turn(row, col, "SW", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
			} 
		}
		else if (enemyPiece == "BP") {
				if (turn(row, col, "SE", 1)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "SW", 1)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
		}
		else if (enemyPiece == "WP") {
				if (turn(row, col, "NE", 1)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "NW", 1)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
		}
		else if (enemyPiece.at(1) == 'B') {
			for (int steps = 1; steps < 8; steps++) { 
				if (turn(row, col, "NE", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "NW", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "SE", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
				 if (turn(row, col, "SW", steps)) {
					if (!(kingOnBoard(color))) {
						buffer("paste");
						return true;
					}
					buffer("paste");
				}
			} 
		}
		else if (enemyPiece.at(1) == 'N') {
			if (turn(row, col, "NNE", 1)) {
				if (!(kingOnBoard(color))) {
					buffer("paste");
					return true;
				}
				buffer("paste");
			}
			 if (turn(row, col, "NNW", 1)) {
				if (!(kingOnBoard(color))) {
					buffer("paste");
					return true;
				}
				buffer("paste");
			}
			 if (turn(row, col, "SSE", 1)) {
				if (!(kingOnBoard(color))) {
					buffer("paste");
					return true;
				}
				buffer("paste");
			}
			 if (turn(row, col, "SSW", 1)) {
				if (!(kingOnBoard(color))) {
					buffer("paste");
					return true;
				}
			}
		}
	buffer("paste");
	return false;
}

bool Board::checkForCheck(char color) {
	string enemyPiece;
	if (color == 'W') {
		for (int r = 0; r < NUM_ROWS; r++) {
			for (int c = 0; c < NUM_COLS; c++) {
				enemyPiece = look(r, c);
				if (enemyPiece.at(0) == 'B') {
					if ((canTake(r, c, color, enemyPiece))) {
						cout << "White is in check! You can not move into or stay in check!" << endl;
						return true;
					}
				}
			}
		}
	}
	if (color == 'B') {
		for (int r = 0; r < NUM_ROWS; r++) {
			for (int c = 0; c < NUM_COLS; c++) {
				enemyPiece = look(r, c);
				if (enemyPiece.at(0) == 'W') {
					if ((canTake(r, c, color, enemyPiece))) {
						cout << "Black is in check! You can not move into or stay in check!" << endl;
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Board::displayLine() {
	cout << endl;
	for (int x = 0; x <= NUM_COLS; x++) {
		cout << "    | ";
	}
	cout << endl;
	for (int x = 0; x <= NUM_COLS; x++) {
		cout << "----| ";
	}
	cout << endl;

}

void Board::displayBoard() {
	cout << endl << "CURRENT BOARD:" << endl << endl;

	//row header
	for (int r = 0; r < 1; r++) {
		for (int c = 0; c <= NUM_COLS; c++) {
			cout << "  " << boardRowHeader[r][c] << " | ";
		}
		displayLine();
	}


	for (int r = 0; r < NUM_ROWS; r++) {
		if (r == 0) {
			cout << 'A' << "   |"; //column header
		}
		else if (r == 1) {
			cout << 'B' << "   |";
		}
		else if (r == 2) {
			cout << 'C' << "   |";
		}
		else if (r == 3) {
			cout << 'D' << "   |";
		}
		else if (r == 4) {
			cout << 'E' << "   |";
		}
		else if (r == 5) {
			cout << 'F' << "   |";
		}
		else if (r == 6) {
			cout << 'G' << "   |";
		}
		else if (r == 7) {
			cout << 'H' << "   |";
		}
		for (int c = 0; c < NUM_COLS; c++) {
			cout << " " << board[r][c].getPiece() << "  |";
		}
		displayLine();
	}
	cout << endl << endl;
}

string Board::take(int row, int col) {
	if (row <= NUM_ROWS - 1 && col <= NUM_COLS) {
		string pieceToTake;
		pieceToTake = board[row][col].getPiece();
		board[row][col].place(' ', ' ');
		return pieceToTake;
	}
}

void Board::place(int row, int col, char color, char piece) {
	if (row <= 7 && col <= 7) {
		board[row][col].place(color, piece);
	}
	else {
		cout << "Out of bounds!";
	}
}

string Board::look(int row, int col) {
	//assert((row >= 0) && (row < NUM_ROWS));
	if ((row <= 0) && (row > NUM_ROWS))
		return false;
	//assert((col >= 0) && (col < NUM_COLS));
	if ((col <= 0) && (col > NUM_COLS))
		return false;
	return board[row][col].getPiece();
}

bool Board::cellEmpty(int toRow, int toCol, string piece) {
	//assert((toRow >= 0) && (toRow < NUM_ROWS));
	if ((toRow < 0) || (toRow >= NUM_ROWS))
		return false;
	//assert((toCol >= 0) && (toCol < NUM_COLS));
	if ((toCol < 0) || (toCol >= NUM_ROWS))
		return false;
	char pieceMovingColor = piece.at(0);
	string pieceAtSpot = look(toRow, toCol);

	if (look(toRow, toCol) == "  ") {
		return true;
	}
	else if ((pieceMovingColor != pieceAtSpot.at(0))) { 
		captureCounter++;
		return true;
	}
	return false;
}


bool Board::moveRook(int &row, int &col, string direction, int steps) {

	string piece = look(row, col);
	//assert(piece.at(1) == 'R');
	if (piece.at(1) != 'R') {
		return false;
	}

	if (!((direction == "N") || (direction == "S") || (direction == "W") || (direction == "E"))) {
		cout << "Rooks can not move " << direction << "!" << endl;
		return false;
	}
	for (int x = 0; x < steps; x++) {
		if (!movePieceOneStep(piece, direction, row, col))
			return false;
	}
	return true;
}

bool Board::moveBishop(int &row, int &col, string direction, int steps) {
	string piece = look(row, col);
	//assert(piece.at(1) == 'B');
	if (piece.at(1) != 'B') {
		return false;
	}

	if (!((direction == "NW") || (direction == "SW") || (direction == "NE") || (direction == "SE"))) {
		cout << "Bishops can not move " << direction << "!" << endl;
		return false;
	}
	for (int x = 0; x < steps; x++) {
		if (!movePieceOneStep(piece, direction, row, col))
			return false;
	}
	return true;
}

bool Board::moveQueen(int &row, int &col, string direction, int steps) {
	string piece = look(row, col);
	//assert(piece.at(1) == 'Q');
	if (piece.at(1) != 'Q') {
		return false;
	}

	if (!((direction == "NW") || (direction == "SW") || (direction == "NE") || (direction == "SE") ||
		(direction == "N") || (direction == "S") || (direction == "W") || (direction == "E"))) {
		cout << "Queens can not move " << direction << "!" << endl;
		return false;
	}
	for (int x = 0; x < steps; x++) {
		if (!movePieceOneStep(piece, direction, row, col))
			return false;
	}
	return true;
}

bool Board::moveKing(int &row, int &col, string direction, int steps) {
	string piece = look(row, col);
	//assert(piece.at(1) == 'K');
	if (piece.at(1) != 'K') {
		return false;
	}

	if (!((direction == "NW") || (direction == "SW") || (direction == "NE") || (direction == "SE") ||
		(direction == "N") || (direction == "S") || (direction == "W") || (direction == "E"))) {
		cout << "Kings can not move " << direction << "!" << endl;
		return false;
	}
	else if (steps == 1) {
		if (!movePieceOneStep(piece, direction, row, col)) {
			return false;
		}
	}
	else {
		cout << "Kings can not move more than one space at a time!" << endl;
		return false;
	}
	return true;
}

bool Board::moveKnight(int &row, int &col, string direction, int steps) {
	string piece = look(row, col);
	//assert(piece.at(1) == 'N');
	if (piece.at(1) != 'N') {
		return false;
	}

	if (!((direction == "NNW") || (direction == "NWW") || (direction == "NNE") || (direction == "SEE") ||
		(direction == "NEE") || (direction == "SSE") || (direction == "SWW") || (direction == "SSW"))) {
		cout << "Knights can not move " << direction << "!" << endl;
		return false;
	}
	else if (steps == 1) {
		if (!movePieceOneStep(piece, direction, row, col)) {
			return false;
		}
	}
	else {
		cout << "Knights can only move one space at a time (In the shape of an L)!" << endl;
		return false;
	}
	return true;
}

bool Board::movePawn(int &row, int &col, string direction, int steps) {
	string piece = look(row, col);
	//assert(piece.at(1) == 'P');
	if (piece.at(1) != 'P') {
		return false;
	}
	string attackCheckString;
	char attackCheckChar;
	if (steps > 2) {
		cout << "Pawns cannot move " << steps << " steps at a time!" << endl;
		return false;
	}
	if (piece.at(0) == 'B') {
		if (!((direction == "S") || (direction == "SW") || (direction == "SE"))) {
			cout << "Black Pawns can not move " << direction << "!" << endl;
			return false;
		}
		else if ((row == 1) && (steps <= 2)) {
			if (direction == "SW") {
				attackCheckString = look(row + 1, col - 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'W') {
					//cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "SE") {
				attackCheckString = look(row + 1, col + 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'W') {
					//cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "S") {
				attackCheckString = look(row + 1, col);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != ' ') {
					cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
		}

		else if ((row != 1) && (steps == 1)) {
			if (direction == "SW") {
				attackCheckString = look(row + 1, col - 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'W') {
					//cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "SE") {
				attackCheckString = look(row + 1, col + 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'W') {
					//cout << "Pawns can only attack on a diagonal!" << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "S") {
				attackCheckString = look(row + 1, col);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != ' ') {
					cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
		}
		else {
			cout << "Pawns can only move 2 steps on their first move!" << endl << endl;
			return false;
		}
	}


	else if (piece.at(0) == 'W') {
		if (!((direction == "N") || (direction == "NW") || (direction == "NE"))) {
			cout << "White Pawns can not move " << direction << "!" << endl;
			return false;
		}
		else if ((row == 6) && (steps <= 2)) {
			if (direction == "NW") {
				attackCheckString = look(row - 1, col - 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'B') {
					//cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "NE") {
				attackCheckString = look(row - 1, col + 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'B') {
					//cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "N") {
				attackCheckString = look(row - 1, col);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != ' ') {
					cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
		}

		else if ((row != 6) && (steps == 1)) {
			if (direction == "NW") {
				attackCheckString = look(row - 1, col - 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'B') {
					//cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "NE") {
				attackCheckString = look(row - 1, col + 1);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != 'B') {
					//cout << "Pawns can only attack on a diagonal!" << endl << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
			else if (direction == "N") {
				attackCheckString = look(row - 1, col);
				attackCheckChar = attackCheckString.at(0);
				if (attackCheckChar != ' ') {
					cout << "Pawns can only attack on a diagonal!" << endl;
					return false;
				}
				for (int x = 0; x < steps; x++) {
					if (!movePieceOneStep(piece, direction, row, col)) {
						return false;
					}
				}
			}
		}
		else {
			cout << "Pawns can only move 2 steps on their first move!" << endl << endl;
			return false;
		}
	}
}

bool Board::movePieceOneStep(string piece, string direction,
	int &row, int &col) {
	//assert((row >= 0) && (row < NUM_ROWS));
	if ((row < 0) || (row >= NUM_ROWS)) {
		return false;
	}
	//assert((col >= 0) && (col < NUM_COLS));
	if ((col < 0) || (col >= NUM_COLS)) {
		return false;
	}
	int toRow = row;
	int toCol = col;
	if (direction == "S")
		toRow = row + 1;
	else if (direction == "N")
		toRow = row - 1;
	else if (direction == "E")
		toCol = col + 1;
	else if (direction == "W")
		toCol = col - 1;
	else if (direction == "NW") {
		toRow = row - 1;
		toCol = col - 1;
	}
	else if (direction == "NE") {
		toRow = row - 1;
		toCol = col + 1;
	}
	else if (direction == "SW") {
		toRow = row + 1;
		toCol = col - 1;
	}
	else if (direction == "SE") {
		toRow = row + 1;
		toCol = col + 1;
	}
	else if (direction == "NNW") {
		toRow = row - 2;
		toCol = col - 1;
	}
	else if (direction == "NWW") {
		toRow = row - 1;
		toCol = col - 2;
	}
	else if (direction == "NNE") {
		toRow = row - 2;
		toCol = col + 1;
	}
	else if (direction == "NEE") {
		toRow = row - 1;
		toCol = col + 2;
	}
	else if (direction == "SWW") {
		toRow = row + 1;
		toCol = col - 2;
	}
	else if (direction == "SSW") {
		toRow = row + 2;
		toCol = col - 1;
	}
	else if (direction == "SSE") {
		toRow = row + 2;
		toCol = col + 1;
	}
	else if (direction == "SEE") {
		toRow = row + 1;
		toCol = col + 2;
	}
	else {
		cout << "INVALID DIRECTION!" << endl;
		assert(false); // force a failure
	}

	//assert((toRow >= 0) && (toRow < NUM_ROWS));
	if ((toRow < 0) || (toRow >= NUM_ROWS)) {
		return false;
	}
	//assert((toCol >= 0) && (toCol < NUM_COLS));
	if ((toCol < 0) || (toCol >= NUM_COLS)) {
		return false;
	}

	if (!cellEmpty(toRow, toCol, piece)) { 
		/*cout << "Space [" << toRow << ", " << toCol <<
			"] Contains [" << look(toRow, toCol) << "]" << endl;*/
		return false;
	}
	else if (captureCounter >= 2) {
		captureCounter = 0;
		//cout << "many captures";
		return false;
	}
	else {
		piece = take(row, col);
		place(toRow, toCol, piece.at(0), piece.at(1));
		row = toRow;
		col = toCol;
		return true;
	}
}

bool Board::turn(int row, int col, string direction, int steps) {
	captureCounter = 0;
	//assert((row >= 0) && (row < NUM_ROWS));
	if ((row < 0) || (row >= NUM_ROWS)) {
		return false;
	}
	//assert((col >= 0) && (col < NUM_COLS));
	if ((col < 0) || (col >= NUM_COLS)) {
		return false;
	}
	int holdRow = row;
	int holdCol = col;
	bool result = false;
	string piece = look(row, col);
	//cout << "*** MOVING " << piece << " FROM [" << row << ", " << col   //TRACE STATEMENTS
	//<< "] Direction:" << direction << " #steps: " << steps << endl;
	if (piece.at(1) == 'R') {
		result = moveRook(row, col, direction, steps);
	}
	else if (piece.at(1) == 'P') {
		result = movePawn(row, col, direction, steps);
	}
	else if (piece.at(1) == 'B') {
		result = moveBishop(row, col, direction, steps);
	}
	else if (piece.at(1) == 'Q') {
		result = moveQueen(row, col, direction, steps);
	}
	else if (piece.at(1) == 'K') {
		result = moveKing(row, col, direction, steps);
	}
	else if (piece.at(1) == 'N') {
		result = moveKnight(row, col, direction, steps);
	}
	else {
		cout << "Invalid piece " << piece << " at position [" << row << ", " << col << "]" << endl;
		assert(false);
	}
	if (result) { 
		return true;
	}
	else {
		piece = take(row, col);
		place(holdRow, holdCol, piece.at(0), piece.at(1));
		return false;
	}
}

bool Board::makeMove(char color) {
	char charRow;
	char charCol;
	int numRow;
	int col;
	string direction;
	int steps;
	string move;
	string colorCheck;

	if (color == 'W') {
		cout << player1 << "'s " << "turn!" << endl;
		cout << "Enter cell (row/col) to move: ";
		cin >> move;
		charRow = move.at(0);
		if (charRow == 'A') {
			numRow = 0;
		}
		else if (charRow == 'B') {
			numRow = 1;
		}
		else if (charRow == 'C') {
			numRow = 2;
		}
		else if (charRow == 'D') {
			numRow = 3;
		}
		else if (charRow == 'E') {
			numRow = 4;
		}
		else if (charRow == 'F') {
			numRow = 5;
		}
		else if (charRow == 'G') {
			numRow = 6;
		}
		else if (charRow == 'H') {
			numRow = 7;
		}
		else {
			cout << "Invalid Row!" << endl;
			makeMove(color);
		}

		charCol = move.at(1);
		col = charCol - '0';
		colorCheck = look(numRow, col);
		if (colorCheck.at(0) != color) {
			cout << "Wrong color!" << endl;
			makeMove(color);
		}
		else {
			cout << "Enter direction: ";
			cin >> direction;
			cout << "Enter number of steps: ";
			cin >> steps;
			buffer("copy2"); //
			if (!(turn(numRow, col, direction, steps))) {
				//makeMove(color); // 
				return false;
			}
			else if (checkForCheck(color)) { //
				//cout << "is true";
				buffer("paste2");
				displayBoard();
				return false; //
			}
		}
	}

	else if (color == 'B') {
		cout << player2 << "'s " << "turn!" << endl;
		cout << "Enter cell (row/col) to move: ";
		cin >> move;
		charRow = move.at(0);
		if (charRow == 'A') {
			numRow = 0;
		}
		else if (charRow == 'B') {
			numRow = 1;
		}
		else if (charRow == 'C') {
			numRow = 2;
		}
		else if (charRow == 'D') {
			numRow = 3;
		}
		else if (charRow == 'E') {
			numRow = 4;
		}
		else if (charRow == 'F') {
			numRow = 5;
		}
		else if (charRow == 'G') {
			numRow = 6;
		}
		else if (charRow == 'H') {
			numRow = 7;
		}
		else {
			cout << "Invalid Row!" << endl;
			makeMove(color);
		}
		charCol = move.at(1);
		col = charCol - '0';
		colorCheck = look(numRow, col);
		if (colorCheck.at(0) != color) {
			cout << "Wrong color!" << endl;
			makeMove(color);
		}
		else {
			cout << "Enter direction: ";
			cin >> direction;
			cout << "Enter number of steps: ";
			cin >> steps;
			buffer("copy2"); //
			if (!(turn(numRow, col, direction, steps))) {
				return false;
			}
			else if (checkForCheck(color)) { //
				buffer("paste2"); //
				displayBoard();
				return false; //
			}
		}
	}
	displayBoard();
	return true;
}

int main() {
	int counter;
	Board board;
	string goOn = "";

	cout << "************WELCOME TO DP CHESS**************" << endl << "Enter player names: " << endl;
	cout << "Player 1: ";
	cin >> player1;
	cout << "Player 2: ";
	cin >> player2;

	cout << "BEGINNING BOARD:" << endl;
	board.displayBoard();
	while ((goOn != "N") && (goOn != "n")) {
		int step = 0;
		board.checkForCheck('W');
		counter = 0;
		while (!board.makeMove('W')) {
			if (counter++ > 3) {
				cout << "Out of tries! White loses!\n";
				goOn = "N";
				break;
			}
		}
		if (goOn != "N") {
			board.checkForCheck('B');
			counter = 0;
			while (!board.makeMove('B')) {
				if (counter++ > 3) {
					cout << "Out of tries! Black loses!\n";
					goOn = "N";
					break;
				}
			}
		}
		if (goOn != "N") {
			cout << "Continue? (Y/N) ";
			cin >> goOn;
		}
	}

	cout << "ENDING BOARD:" << endl;
	board.displayBoard();
	return 0;
}



