#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
	StudentAI(int col, int row, int k, int g);
	virtual Move GetMove(Move board);
  Board myBoard;

  // Move IDS(int, vector<vector<int> >&, int, int, int);
  // Move miniMax(int, vector<vector<int> >&, int, int, int);
  // vector<Move> availableMoves(vector<vector<int> >&);
  pair<Move, int> IDS(int depth, vector<vector<int> >& board, int, int, int);
  pair<Move, int> miniMax(int depth, vector<vector<int> >& board, int, int, int);
  vector<pair<Move, int> > availableMoves(vector<vector<int> >&);


  int heuristic(vector<vector<int> >&, int);
  pair<int,int> diagnalBRtoTLScore(vector<vector<int> >&, int col, int row);
  void scanDiagnalBRtoTL();
  pair<int,int> diagnalBLtoTRScore(vector<vector<int> >&, int col, int row);
  void scandDiagnalBLtoTR();
  pair<int,int> horizontalScore(vector<vector<int> >&, int col, int row);
  void scanHorizontal(vector<vector<int> >& board, int c, int r, int cPlayer, int& count, int& score);
  pair<int,int> verticalScore(vector<vector<int> >&, int col, int row);
  void scanVertical(vector<vector<int> >& state, int col, int row, int player, int& count, int& score);
  void evaluate(int, int&);
  bool timeout();
};

#endif //STUDENTAI_H
