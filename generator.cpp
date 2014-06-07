#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>

#define SIZE 4

using namespace std;

void printBoard(vector<vector<char> > board) {
  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++)
      cout<<board[i][j]<<' ';
    cout<<endl;
  }
}

bool validBoard(vector<vector<char> > board) {

  int zero=0, one=0, size=board.size();

  for(int i=0; i<size; i++) {
    for(int j=0; j<size; j++) {
      if(board[i][j] == '1')
        one++;
      else if(board[i][j] == '0')
        zero++;
    }
    if(one > size/2 ||  zero > size/2)
      return false;
    
    one = 0;
    zero = 0;
  }

  for(int i=0; i<size; i++) {
    for(int j=0; j<size; j++) {
      if(board[j][i] == '1')
        one++;
      else if(board[j][i] == '0')
        zero++;
    }
    if(one > size/2 ||  zero > size/2)
      return false;
    
    one = 0;
    zero = 0;
  }
  
  for(int i=0; i<size; i++) {
    for(int j=i+1; j<size; j++) {
      bool same = true;
      for(int k=0; k<size; k++) {
        if(board[i][k] != board[j][k] || board[j][k]=='/') {
          same = false;
          break;
        }
      }
      if(same)
        return false;
    }
  }

  for(int i=0; i<size; i++) {
    for(int j=i+1; j<size; j++) {
      bool same = true;
      for(int k=0; k<size; k++) {
        if(board[k][i] != board[k][j] || board[k][j]=='/') {
          same = false;
          break;
        }
      }
      if(same)
        return false;
    }
  }

  return true;
}

int main(void) {
  vector<vector<char> > board;
  
  board.resize(SIZE, vector<char>(SIZE, '/'));

  srand(time(NULL));
  
  for(int i=0; i<board.size(); i++)
    for(int j=0; j<board[i].size(); j++)
      board[i][j] = rand()%3+47;
  
  printBoard(board);

  if(validBoard(board)) {
    cout<<"Valid"<<endl;
  }
  else {
    cout<<"Invalid"<<endl;
  }
}
