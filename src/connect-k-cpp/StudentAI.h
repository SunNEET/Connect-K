#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#pragma once
#include <utility>
#include <vector>
//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
	StudentAI(int col, int row, int k, int g);
	virtual Move GetMove(Move board);
  Board myBoard;

  pair<Move, int> IDS(int depth, vector<vector<int> >& board, int currentPlayer, int Alpha, int Beta);
  pair<Move, int> miniMax(int depth, vector<vector<int> >& board, int currentPlayer, int Alpha, int Beta);
  vector<pair<Move, int> > availableMoves(vector<vector<int> >& board);


  int heuristic(vector<vector<int> >& board, int);
  pair<int,int> diagnalBRtoTLScore(vector<vector<int> >& board, int col, int row);
  void scanDiagnalBRtoTL(vector<vector<int> >& board , int col, int row, int cPlayer, int& count, int& score);
  pair<int,int> diagnalBLtoTRScore(vector<vector<int> >& board, int col, int row);
  void scanDiagnalBLtoTR(vector<vector<int> >& board , int col, int row, int cPlayer, int& count, int& score);
  pair<int,int> horizontalScore(vector<vector<int> >& board, int col, int row);
  void scanHorizontal(vector<vector<int> >& board , int col, int row, int cPlayer, int& count, int& score);
  pair<int,int> verticalScore(vector<vector<int> >& board, int col, int row);
  void scanVertical(vector<vector<int> >& board, int col, int row, int cPlayer, int& count, int& score);
  void evaluate(int, int&);
  bool timeout();
};

#endif //STUDENTAI_H
