#include<iostream>
#include<stdlib.h>
#include<time.h>

#define SIZE 4

using namespace std;

void printBoard(char board[][SIZE]) {
  for(int i=0; i<SIZE; i++) {
    for(int j=0; j<SIZE; j++)
      cout<<board[i][j]<<' ';
    cout<<endl;
  }
}

bool validBoard(char board[][SIZE]) {

  int zero=0, one=0;

  for(int i=0; i<SIZE; i++) {
    for(int j=0; j<SIZE; j++) {
      if(board[i][j] == '1')
        one++;
      else
        zero++;
    }
    if(one != zero)
      return false;
    
    one = 0;
    zero = 0;
  }

  for(int i=0; i<SIZE; i++) {
    for(int j=0; j<SIZE; j++) {
      if(board[j][i] == '1')
        one++;
      else
        zero++;
    }
    if(one != zero)
      return false;
    
    one = 0;
    zero = 0;
  }
  
  for(int i=0; i<SIZE; i++) {
    for(int j=i+1; j<SIZE; j++) {
      bool same = true;;
      for(int k=0; k<SIZE; k++) {
        if(board[i][k] != board[j][k]) {
          same = false;
          break;
        }
      }
      if(same)
        return false;
    }
  }

  for(int i=0; i<SIZE; i++) {
    for(int j=i+1; j<SIZE; j++) {
      bool same = true;;
      for(int k=0; k<SIZE; k++) {
        if(board[k][i] != board[k][j]) {
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
  char board[SIZE][SIZE];

  srand(time(NULL));
  
  for(int i=0; i<SIZE; i++)
    for(int j=0; j<SIZE; j++)
      board[i][j] = rand()%2+48;
  
  printBoard(board);

  if(validBoard(board)) {
    cout<<"Valid"<<endl;
  }
  else {
    cout<<"Invalid"<<endl;
  }
}
