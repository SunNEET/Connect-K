#include "Move.h"


Move::Move()
{
	row = 0;
	col = 0;
	score = 0;
}
Move::Move(int _col, int _row):row(_row),col(_col){}

Move::Move(int _score):score(_score){}


