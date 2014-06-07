#include<iostream>

#define SIZE 10

using namespace std;

void printBoard(bool board[][SIZE]) {
  for(int i=0; i<SIZE; i++) {
    for(int j=0; j<SIZE; j++)
      cout<<board[i][j]<<' ';
    cout<<endl;
  }
}

int main(void) {
  bool board[SIZE][SIZE];

  for(int i=0; i<SIZE; i++)
    for(int j=0; j<SIZE; j++)
      board[i][j] = 0;

  printBoard(board);
}
