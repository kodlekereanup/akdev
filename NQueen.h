class NQueen {
public:
	int row;
	int col;

	NQueen();
	NQueen(int, int); //row, col
	void move();
	bool ifConflict(NQueen);
	int getRow();
	int getCol();
};

NQueen :: NQueen() { }

NQueen :: NQueen(int row, int col) {
	this->row = row;
	this->col  = col;
}

void NQueen :: move() { row++; }

bool NQueen :: ifConflict(NQueen q) {
	if(row == q.getRow() || col == q.getCol()) return true;
	else if(abs(col - q.getCol()) == abs(row - q.getRow())) return true;
	else return false;
}

int NQueen :: getRow() { return row; }
int NQueen :: getCol() { return col; }
