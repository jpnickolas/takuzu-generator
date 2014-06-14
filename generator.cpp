#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>

#define SIZE 4
#define BLANK '/'
#define ZERO '0'
#define ONE '1'

using namespace std;

//Prints out the board separated by spaces
void print_board(vector<vector<char> > board) {
  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++)
      cout<<board[i][j]<<' ';
    cout<<endl;
  }
}

//Returns true if the board is a valid board, and false otherwise 
bool valid_board(vector<vector<char> > board) {

  int zero=0, one=0, size=board.size();

  //checks the rows for too many 1's or 0's
  for(int i=0; i<size; i++) {
    for(int j=0; j<size; j++) {
      if(board[i][j] == ONE)
        one++;
      else if(board[i][j] == ZERO)
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
      else if(board[j][i] == ZERO)
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
      if(board[i][j]==board[i][j-1] && board[i][j]!=BLANK) {
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
      if(board[j][i]==board[j-1][i] && board[j][i]!=BLANK) {
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
        if(board[i][k] != board[j][k] || board[j][k]==BLANK) {
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
        if(board[k][i] != board[k][j] || board[k][j]==BLANK) {
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

int count_blanks(vector<vector<char> > board) {
  int blanks = 0;
  
  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++) {
      if(board[i][j] == BLANK) {
        blanks++;
      }
    }
  }
}

void get_random_blank(vector<vector<char> > board, int &x, int &y) {
  int blanks = count_blanks(board);

  int blank = rand()%blanks;

  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++) {
      if(board[i][j]==BLANK) {
        if(blank>0)
          blank--;
        else {
          x=i;
          y=j;
          return;
        }
      }
    }
  }
}

vector<vector<char> > generate_puzzle(vector<vector<char> > board) {
  vector<vector<char> > test_board = vector<vector<char> >(board);

  int solutions = solve_puzzle(test_board);

  if(solutions == 1) {
    return board;
  }
  else if(solutions > 1) {
    int x, y;
    
    get_random_blank(board, x, y);
    
    board[x][y] = rand()%2+48;
    
    vector<vector<char> > generated_puzzle = generate_puzzle(board);
    if(generated_puzzle.size() == 0) {
      if(board[x][y]=='0')
        board[x][y]='1';
      else
        board[x][y]='0';
      
      return generate_puzzle(board);
    }
  }

  return vector<vector<char> >(0);
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
  print_board(board);

  //validates the board
  if(valid_board(board)) {
    cout<<"Valid"<<endl;
  }
  else {
    cout<<"Invalid"<<endl;
  }
}
