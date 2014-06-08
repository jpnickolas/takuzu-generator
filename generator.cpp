#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>

#define SIZE 4

using namespace std;

//Prints out the board separated by spaces
void printBoard(vector<vector<char> > board) {
  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++)
      cout<<board[i][j]<<' ';
    cout<<endl;
  }
}

//Returns true if the board is a valid board, and false otherwise 
bool validBoard(vector<vector<char> > board) {

  int zero=0, one=0, size=board.size();

  //checks the rows for too many 1's or 0's
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

  //checks the columns for too many 1's or 0's
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
 
  //checks the rows for any values of more than 2 in succession
  bool consecutive = false;
  for(int i=0; i<size; i++) {
    for(int j=1; j<size; j++) {
      if(board[i][j]==board[i][j-1] && board[i][j]!='/') {
        if(consecutive)
          return false;
        else
          consecutive = true;
      }
      else
        consecutive = false;
    }
  }
  
  //checks the columns for any values of more than 2 in succession
  consecutive = false;
  for(int i=0; i<size; i++) {
    for(int j=1; j<size; j++) {
      if(board[j][i]==board[j-1][i] && board[j][i]!='/') {
        if(consecutive)
          return false;
        else
          consecutive = true;
      }
      else
        consecutive = false;
    }
  }

  //checks the rows for duplicates
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

  //checks the columns for duplicates
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

  //creates the board of the correct size
  vector<vector<char> > board;
  board.resize(SIZE, vector<char>(SIZE, '/'));

  //randomly fills the board
  srand(time(NULL));
  for(int i=0; i<board.size(); i++)
    for(int j=0; j<board[i].size(); j++)
      board[i][j] = rand()%3+47;
  
  //prints out the board
  printBoard(board);

  //validates the board
  if(validBoard(board)) {
    cout<<"Valid"<<endl;
  }
  else {
    cout<<"Invalid"<<endl;
  }
}
