#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>

#define DEFAULT_SIZE 8
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

//counts the blank spaces in a board
int count_blanks(vector<vector<char> > board) {
  int blanks = 0;
  
  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++) {
      if(board[i][j] == BLANK) {
        blanks++;
      }
    }
  }

  return blanks;
}

/*
  chooses a random blank space from the board, and sends back the (x, y) 
  coordinates using the reference of the x and y sent initially
*/
void get_random_blank(vector<vector<char> > board, int &x, int &y) {

  //counts the blanks and chooses a random one
  int blanks = count_blanks(board);
  int blank = rand()%blanks;

  //finds that random blank spot, and sends it back
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

/*
  Recursively counts the number of solutions of the board. 
  This caps at 2 for the sake of efficiency, but can be altered easily to get
  the total number of solutions. 
*/
int count_solutions(vector<vector<char> > &board) {
  //checks if the board is even valid
  if(!valid_board(board))
    return 0;
  
  //finds a blank spot
  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++) {
      if(board[i][j]==BLANK) {
        
        //tests zero in that blank spot
        board[i][j]=ZERO;
        int solutions = count_solutions(board);
        
        //if there are too many solutions, don't even bother getting the rest
        if(solutions>1) {
          board[i][j]=BLANK;
          return solutions;
        }
        else {
          //tests one in that blank spot
          board[i][j]=ONE;
          solutions += count_solutions(board);
          
          //resets the board before returning the number of solutions
          board[i][j]=BLANK;
          return solutions;
        }
      }
    }
  }
  
  //if there are no more blank spots, then this must be a solution
  return 1;
}

//recursively finds the first solution to a puzzle, and returns it
vector<vector<char> > get_solution(vector<vector<char> > &board) {
  if(!valid_board(board))
    return vector<vector<char> >(0);
  
  //finds the first blank in the board
  for(int i=0; i<board.size(); i++) {
    for(int j=0; j<board[i].size(); j++) {
      if(board[i][j]==BLANK) {
        
        //tries filling the blank with a zero
        board[i][j]=ZERO;
        
        //gets the first solution with a zero
        vector<vector<char> > solution = get_solution(board);
        
        //if the solution is empty, tries again with a one
        if(solution.size() == 0) {
          board[i][j]=ONE;
          solution = get_solution(board);
          
          if(solution.size()==0)
            board[i][j]=BLANK;
        }
        
        //resets the board before returning the solution
        board[i][j] = BLANK;
        return solution;
      }
    }
  }

  return vector<vector<char> >(board);
}

//makes the game a bit easier by giving the user some free spaces
vector<vector<char> > ease_board(vector<vector<char> > board, int extra_spots) {
  
  //gets the solution to the puzzle
  vector<vector<char> > solution = get_solution(board);

  //gets random blank spots, and fills them in
  for(int i=0; i<extra_spots; i++) {
    int x,y;
    get_random_blank(board, x, y);
    
    board[x][y] = solution[x][y];
  }
  
  return board;
}

/*
  recursively generates the takuzu puzzle based on the size of the initial 
  board sent. If the board is filled, it will attempt to create a puzzle from
  it.
*/
vector<vector<char> > generate_puzzle(vector<vector<char> > board) {

  //counts the possible solutions in the board
  int solutions = count_solutions(board);

  //if there is only one solution, return that board with a few spaces filled
  if(solutions == 1) {
    return ease_board(board, count_blanks(board)/8);
  }
  else if(solutions > 1) {
    
    //will try up to 10 times to create a working puzzle 
    for(int i=0; i<10; i++) {
      
      //gets a random blank spot, and fills it with a random zero or one
      int x, y;
      get_random_blank(board, x, y);
      board[x][y] = rand()%2+48;
      
      //generates a new puzzle with that configuration
      vector<vector<char> > generated_puzzle = generate_puzzle(board);
      
      //if the new puzzle is successful, it is returned. Otherwise, reattempt
      if(generated_puzzle.size() == 0) {
        board[x][y]=BLANK;
      }
      else
        return generated_puzzle;
      
    }
  }

  //will eventually give up, although this is highly unlikely.
  return vector<vector<char> >(0);
}

int main(int argc, char * args[]) {
  
  int size = DEFAULT_SIZE;
  
  //checks if a command line argument was sent
  if(argc > 1) {
    //gets the size from the argument
    size = atoi(args[1]);
    
    //makes sure the argument is valid.
    if(size<2)
      size = DEFAULT_SIZE;
    
    //makes sure the argument is even
    if(size%2 == 1)
      size--;
  }

  //randomizes the timer
  srand(time(NULL));

  vector<vector<char> > board;
  
  //keeps trying to generate puzzles until it creates a successful one.
  //this normally doesn't need to loop, but it's still an edge case to test for
  do {
    //creates the board of the correct size
    board.resize(size, vector<char>(size, '/'));
    board = generate_puzzle(board);
  } while(board.size()==0);

  //prints out the board
  print_board(board);

}
