#include<iostream>

#define SIZE 8
#define SEED_SIZE 4

int get_possible_boards(bool** board, int row, int col, bool** used, int** zeroes, int** ones)
{
    // exit when we leave the bounds of the grid
    if(row >= SIZE)
    {
        return 0;
    }
    
    // move to the next row if the column leaves the bounds of the grid
    int next_row = row;
    int next_col = col;
    next_col++;
    if(next_col >= SIZE)
    {
        next_col = 0;
        next_row++;
    }
    
    // proceed to the next set of boards if this has been pre-set
    if(used[row][col])
    {
        return get_possible_boards(board, next_row, next_col, used, zeroes, ones);
    }
    
    // try with a 1
    board[row][col] = true;
    used[row][col] = true;
    int total_ones = get_possible_boards(board, next_row, next_col, used, zeroes, ones);
    ones[row][col] += total_ones;
    
    // try with a 0
    board[row][col] = false;
    int total_zeroes += get_possible_boards(board, next_row, next_col, used, zeroes, ones);
    zeroes[row][col] += total_zeroes;
    
    // reset the used section
    used[row][col] = false;
    
    // return the number of valid boards in this config
    return total_ones + total_zeroes;
}

int main()
{
    // a grid of trues and falses representing the 1's and 0's respectively on a takuzu board
    bool board[SIZE][SIZE];
    
    // which parts of the board have been used
    bool used[SIZE][SIZE];
    
    // the total boards that exist with either a 1 or 0 in each respective position given an initial board
    int zeroes[SIZE][SIZE];
    int ones[SIZE][SIZE];
    
    // reset the boards
    for(int i=0; i < SIZE; i++)
    {
        for(int j=0; j < SIZE; j++)
        {
            board[i][j] = false;
            used[i][j] = false;
            
        }
    }
    
    // plant a seed of a few initial positions on the board
    for(int i = 0; i < SEED_SIZE; i++)
    {
        int row = Math.random()*SIZE;
        int col = Math.random()*SIZE;
        board[row][col] = Math.random()*2;
        used[row][col] = true;
    }
    
    // iterate until the provided board produces only one valid solution
    while(true)
    {
        for(int i=0; i < SIZE; i++)
        {
            for(int j=0; j < SIZE; j++)
            {
                zeroes[i][j] = 0;
                ones[i][j] = 0;
            }
        }
        
        // populate the total number of boards with each position
        get_possible_boards(board, 0, 0, used, zeroes, ones);
        
        // Find the spot that would generate the most unique board if a piece were added (lowest non-zero value in the zeroes or ones grids)
        int lowest_zero = 0;
        int lowest_zero_row = 0;
        int lowest_zero_col = 0;
        int lowest_one = 0;
        int lowest_one_row = 0;
        int lowest_one_col = 0;
        for(int i=0; i < SIZE; i++)
        {
            for(int j=0; j < SIZE; j++)
            {
                if((lowest_zero == 0) || (zeroes[i][j] < lowest_zero))
                {
                    lowest_zero = zeroes[i][j];
                    lowest_zero_row = i;
                    lowest_zero_col = j;
                }
                if((lowest_one == 0) || (ones[i][j] < lowest_one))
                {
                    lowest_one = ones[i][j];
                    lowest_one_row = i;
                    lowest_one_col = j;
                }
            }
        }
        
        // exit if no possible board could be generated (sanity check, this shouldn't ever happen)
        if((lowest_zero == 0) || (lowest_one == 0))
        {
            break;
        }
        
        if(lowest_zero < lowest_one)
        {
            board[lowest_zero_row][lowest_zero_col] = 0;
        }
        else
        {
            board[lowest_one_row][lowest_one_col] = 0;
        }
        break;
    }
    
    // Draw board
    for(int i=0; i<SIZE; i++)
    {
        cout<<"--";
    }
    cout<<"-\n";
    for(int i =0; i<SIZE; i++)
    {
        cout<<"|";
        for(int j=0; j<SIZE; j++)
        {
            char output = ' ';
            if(used[i][j])
            {
                output = board[i][j] ? '1' : '0';
            }
            cout<<output<<" ";
        }
        cout<<"\n";
        for(int j=0; j<SIZE; j++)
        {
            cout<<"--";
        }
        cout<<"-\n";
    }
    
    return 0;
}