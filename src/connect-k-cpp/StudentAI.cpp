#include "StudentAI.h"
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <climits>
#include <utility>
using namespace std;
#define MAXDEPTH 10000
#define WINNER 9999
#define MYAI 2
#define OPPONENT 1
int moveCnt = 0;
clock_t TIMER;

// Board myBoard;
//The following part should be completed by students.
//The students can modify anything except the class name and exisiting functions and varibles.
StudentAI::StudentAI(int col,int row,int k,int g):AI(col, row, k, g) {
	Board _board(col,row,k,g);
  myBoard = _board;
}

Move StudentAI::GetMove(Move move) {
  moveCnt++;
  myBoard = myBoard.MakeMove(move, OPPONENT);
  if(moveCnt == 1) {
    if(myBoard.board[col/2][row/2] == 0){
      myBoard = myBoard.MakeMove(Move(col/2, row/2), MYAI);
      return Move(col/2, row/2);
    } else if(myBoard.board[col/2-1][row/2-1] == 0){
      myBoard = myBoard.MakeMove(Move(col/2-1, row/2-1), MYAI);
      return Move(col/2-1, row/2-1);
    } else if(myBoard.board[col/2][row/2-1] == 0) {
      myBoard = myBoard.MakeMove(Move(col/2, row/2-1), MYAI);
      return Move(col/2, row/2-1);
    } else {
      myBoard = myBoard.MakeMove(Move(col/2-1, row/2), MYAI);
      return Move(col/2-1, row/2);
    }
  } else {
    TIMER = clock();
    // Run IterativeDeepeningSearch
    for(int depth=1; depth<MAXDEPTH; depth++) {
      // Move nxt = IDS(depth, myBoard.board, MYAI, INT_MIN, INT_MAX);
      pair<Move, int> action = IDS(depth, myBoard.board, MYAI, INT_MIN, INT_MAX);
      // printf("nxt.col = %d, nxt.row = %d, nxt.score = %d\n", nxt.col, nxt.row, nxt.score);
      
      // if(nxt.score != 0) {
      if(action.second != 0) {
        myBoard = myBoard.MakeMove(action.first, MYAI);
        return action.first;
      }
    }
  }
}

// Move StudentAI::IDS(int depth, vector<vector<int> >& board, int cPlayer, int ALPHA, int BETA) {
pair<Move,int> StudentAI::IDS(int depth, vector<vector<int> >& board, int cPlayer, int ALPHA, int BETA) {

  // Move m = miniMax(depth, board, cPlayer, ALPHA, BETA);
  pair<Move,int> action = miniMax(depth, board, cPlayer, ALPHA, BETA);
  // if(m.score >= WINNER || m.score == -1 || timeout()) return m;
  if(action.second >= WINNER || action.second == -1 || timeout()) return m;
  if(depth>0) {
    // Move m2 = IDS(depth-1, board, cPlayer, ALPHA, BETA);
    pair<Move,int> action2 = IDS(depth-1, board, cPlayer, ALPHA, BETA);
    // if(m2.score) return m2;
    if(action2.second) return action2;
  }
  // m.score = 0;
  action.second = 0;
  return action;
}

// Move StudentAI::miniMax(int depth, vector<vector<int> >& board, int cPlayer, int ALPHA, int BETA) {
pair<Move,int> StudentAI::miniMax(int depth, vector<vector<int> >& board, int cPlayer, int ALPHA, int BETA) {
  // vector<Move> mv = availableMoves(board);
  vector<pair<Move,int> > mv = availableMoves(board);
  pair<Move,int> bestMv;
  // Come to the limit of the IDS or No available move can be made
  if(depth == 0 || mv.size() == 0) {
    // Move sc(heuristic(board, cPlayer));
    // return sc;
    pair<Move,int> sc(make_pair(Move(),heuristic(board, cPlayer)));
    return sc;
  } else if(cPlayer == MYAI) {
    // MyAI, pick a maximum value
    int bestVal = INT_MIN;
    for(int i=0; i<(int)mv.size(); i++) {
      // board[mv[i].row][mv[i].col] = MYAI;
      board[mv[i].first.row][mv[i].first.col] = MYAI;
      // Move m = miniMax(depth-1, board, OPPONENT, bestVal, BETA);
      pair<Move,int> act = miniMax(depth-1, board, OPPONENT, bestVal, BETA);
      // mv[i].score = m.score;
      mv[i].second = act.second;
      // board[mv[i].row][mv[i].col] = 0;
      board[mv[i].first.row][mv[i].first.col] = 0;
      // if(m.score == -WINNER) {
      //   m.score = WINNER;
      //   return m;
      // }
      if(act.second == -WINNER) {
        act.second = WINNER;
        return act;
      }
      // if(mv[i].score > bestVal) {
      //   bestVal = mv[i].score;
      //   bestMv = mv[i];
      // }
      if(mv[i].second > bestVal) {
        bestVal = mv[i].second;
        bestMv = mv[i];
      }
      if(bestVal > ALPHA) ALPHA = bestVal;
      if(bestVal >= BETA) break;
      if(timeout()) return bestMv;
    }
    return bestMv;
  } else {
    // Opponent, pick a minimum value
    int bestVal = INT_MAX;
		vector<Move> mv = availableMoves(board);
		for(int i=0; i<mv.size(); i++){
			board[mv[i].row][mv[i].col] = OPPONENT;
			mv[i].score = miniMax(depth - 1, board, MYAI, ALPHA, bestVal).score;
			board[mv[i].row][mv[i].col] = 0;
      //If player two receives a winning score, player one uses this move to block
			if(mv[i].score == -WINNER){
				bestMv = mv[i];
				return bestMv;
			}
			if(mv[i].score < bestVal) {
				bestMv = mv[i];
				bestVal = mv[i].score;
			}
			if(bestVal < BETA) BETA = bestVal;
			if(bestVal <= ALPHA) break;
			if(timeout()) return bestMv;
		}
		return bestMv;
  }
}

vector<Move> StudentAI::availableMoves(vector<vector<int> >& board) {
  vector<Move> moveVector;
  //Push the middle of the board into available moves vector first
  for(int c=(col/2)-1; c<(col/2)+(col/3); c++) {
    for(int r=row-1; r>=0; r--) {
      if(board[r][c] == 0) {
        moveVector.push_back(Move(c, r));
        if(g==1) break;
      }
    }
  }
  //Push the right side of gameboard into vector
  for(int c=(col/2)+(col/3); c<col; c++) {
    for(int r=row-1; r>=0; r--) {
      if(board[r][c] == 0) {
        moveVector.push_back(Move(c, r));
        if(g==1) break;
      }
    }
  }
  //Push the left of the gameboard into available moves vector
  for(int c=(col/2)-2; c>=0; c--){
    for(int r=row-1; r>=0; r--){
      if(board[r][c] == 0) {
        moveVector.push_back(Move(c, r));
        if(g==1) break;        
      }
    }  
  }
  return moveVector;
}

pair<int,int> StudentAI::verticalScore(vector<vector<int> >& board, int c, int r) {
  int aiCount = 0; int otherCount = 0;
	int aiScore = 0; int otherScore = 0;

	scanVertical(board, c, r, MYAI, aiCount, aiScore);
	scanVertical(board, c, r, OPPONENT, otherCount, otherScore);
	return make_pair(aiScore, otherScore);
}

void StudentAI::scanVertical(vector<vector<int> >& board, int c, int r, int cPlayer, int& count, int& score) {
  bool bottomBlocked = false, topBlocked = false;

	if(board[r][c] == cPlayer){
		count++;
		if(r==0)
			bottomBlocked = true;
		else if(board[r-1][c] == (cPlayer%2)+1)
			bottomBlocked = true;

		while((++r<row) && board[r][c] == cPlayer)
			++count;
		
		if(r >= row)
			topBlocked = true;
		else if(board[r][c] == (cPlayer%2)+1)
			topBlocked = true;

		if(count >= k){
			score = WINNER;
			return;
		}
		if(bottomBlocked && topBlocked){
			score = 0;
			return;
		}
		evaluate(count, score);
	}
}

pair<int,int> StudentAI::horizontalScore(vector<vector<int> >& board, int c, int r) {
  int aiCount = 0; int otherCount = 0;
	int aiScore = 0; int otherScore = 0;

	scanHorizontal(board, c, r, MYAI, aiCount, aiScore);
	scanHorizontal(board, c, r, OPPONENT, otherCount, otherScore);
	return make_pair(aiScore, otherScore);
}

void StudentAI::scanHorizontal(vector<vector<int> >& board, int c, int r, int cPlayer, int& count, int& score) {
  bool leftBlocked = false; 
  bool rightBlocked = false;
  int tmpC = c;
	if(board[r][c] == cPlayer){
		count++;
    while((--tmpC>=0) && board[r][tmpC] == cPlayer)
			++count;
		if(tmpC < 0)
			leftBlocked = true;
		else if(board[r][tmpC] == (cPlayer%2)+1)
			leftBlocked = true;
    
    tmpC = c;
    while(++tmpC<col && board[r][tmpC] == cPlayer)
			++count;
    if(tmpC == col)
			rightBlocked = true;
		else if(board[r][tmpC] == (cPlayer%2)+1)
			rightBlocked = true;

		if(count >= k) {
      score = WINNER;
      return;
    }
    if(leftBlocked && rightBlocked){
      score = 0;
      return;
    }
    evaluate(count, score);
	}
}

int StudentAI::heuristic(vector<vector<int> >& board, int cPlayer){
  int aiScore = 0, aiHScore = 0, otherScore = 0, otherHScore = 0;
	for(int c=0; c<col; c++)
		for(int r=0; r<row; r++){
			//vertical Win count
      pair<int,int> piiv = verticalScore(board,c,r);
			int vertScore = piiv.first;
			int otherScore = piiv.second;
			if(otherScore>=WINNER) return -WINNER;
			if(vertScore>=WINNER) return WINNER;
			aiScore += vertScore;
			
			//horizontal wins count
      pair<int,int> piih = horizontalScore(board,c,r);
			int horizScore = piih.first;
			otherScore = piih.second;
			if(otherScore>=WINNER) return -WINNER;
			if(horizScore>=WINNER) return WINNER;
			aiScore += horizScore;
		}	 	
		return aiScore;
}

bool StudentAI::timeout() {
  return (float)(clock() - TIMER)/CLOCKS_PER_SEC > 10;
}

void StudentAI::evaluate(int cnt, int& score) {
  if(cnt==2) score=1;
  if(cnt==k-3) score=10;
  if(cnt==k-2) score=100;
  if(cnt==k-1) score=1000;
}