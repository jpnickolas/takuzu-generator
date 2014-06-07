#include<iostream>

#define SIZE 10

using namespace std;

void printBoard(char board[][SIZE]) {
  for(int i=0; i<SIZE; i++) {
    for(int j=0; j<SIZE; j++)
      cout<<board[i][j]<<' ';
    cout<<endl;
  }
}

int main(void) {
  char board[SIZE][SIZE];

  for(int i=0; i<SIZE; i++)
    for(int j=0; j<SIZE; j++)
      board[i][j] = '_';

  printBoard(board);
}
