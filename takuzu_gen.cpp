#include<iostream>
#include<math.h>
#include<ctime>

#define SIZE 10
#define SEED_SIZE 8

using namespace std;

bool prune(bool** board, int row, int col, bool** used, bool* error)
{
    bool absolute_found = false;

    if (used[row][col])
    {
        absolute_found = true;
    }

    int total_ones = 0;
    int total_zeroes = 0;
    // count the 1's and 0's in each row, to make sure there are no more than SIZE/2 of each
    for (int i = 0; i < col; i++)
    {
        if (board[row][i])
        {
            total_ones++;
        }
        else
        {
            total_zeroes++;
        }
    }
    if (total_ones >= SIZE / 2)
    {
        if (absolute_found)
        {
            if (board[row][col] == true)
            {
                *error = true;
                return true;
            }
        }

        board[row][col] = false;
        absolute_found = true;
    }

    if (total_zeroes >= SIZE / 2)
    {
        if (absolute_found)
        {
            if (board[row][col] == false)
            {
                *error = true;
                return true;
            }
        }

        board[row][col] = true;
        absolute_found = true;
    }

    // count the 1's and 0's in each column, to make sure there are no more than SIZE/2 of each
    total_ones = 0;
    total_zeroes = 0;
    for (int i = 0; i < row; i++)
    {
        if (board[i][col])
        {
            total_ones++;
        }
        else
        {
            total_zeroes++;
        }
    }
    if (total_ones >= SIZE / 2)
    {
        if (absolute_found)
        {
            if (board[row][col] == true)
            {
                *error = true;
                return true;
            }
        }

        board[row][col] = false;
        absolute_found = true;
    }

    if (total_zeroes >= SIZE / 2)
    {
        if (absolute_found)
        {
            if (board[row][col] == false)
            {
                *error = true;
                return true;
            }
        }

        board[row][col] = true;
        absolute_found = true;
    }

    // check if there are 2 values in a row, so the third must be the opposite (00 -> 001)
    if (row > 1)
    {
        if (board[row - 1][col] == board[row - 2][col])
        {
            if (absolute_found)
            {
                if (board[row][col] == board[row - 1][col])
                {
                    *error = true;
                    return true;
                }
            }

            board[row][col] = !board[row - 1][col];
            absolute_found =  true;
        }
    }

    // check if there are 2 values in a column, so the third must be the opposite (00 -> 001)
    if (col > 1)
    {
        if (board[row][col - 1] == board[row][col - 2])
        {
            if (absolute_found)
            {
                if (board[row][col] == board[row][col - 1])
                {
                    *error = true;
                    return true;
                }
            }

            board[row][col] = !board[row][col - 1];
            absolute_found = true;
        }
    }

    // Look for rows that are duplicates, and make sure they are not
    if (col == SIZE - 1)
    {
        for (int i = 0; i < row; i++)
        {
            bool duplicate_found = true;
            for (int j = 0; j < col; j++)
            {
                if (board[row][j] != board[i][j])
                {
                    duplicate_found = false;
                    break;
                }
            }

            if (duplicate_found)
            {
                if (absolute_found)
                {
                    if (board[row][col] == board[i][col])
                    {
                        *error = true;
                        return true;
                    }
                }

                board[row][col] = !board[i][col];
                absolute_found = true;
            }
        }
    }

    // Look for rows that are duplicates, and make sure they are not
    if (row == SIZE - 1)
    {
        for (int i = 0; i < col; i++)
        {
            bool duplicate_found = true;
            for (int j = 0; j < row; j++)
            {
                if (board[j][col] != board[j][i])
                {
                    duplicate_found = false;
                    break;
                }
            }

            if (duplicate_found)
            {
                if (absolute_found)
                {
                    if (board[row][col] == board[row][i])
                    {
                        *error = true;
                        return true;
                    }
                }

                board[row][col] = !board[row][i];
                absolute_found = true;
            }
        }
    }

    *error = false;
    return absolute_found;
}

int get_possible_boards(bool ** board, int row, int col, bool ** used, int ** zeroes, int ** ones)
{
    // check board and exit when we leave the bounds of the grid
    if(row >= SIZE)
    {
        return 1;
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
    
    bool error = false;
    // proceed to the next set of boards if this has been pre-set
    if(prune(board, row, col, used, &error))
    {
        if (error)
        {
            return 0;
        }
        else
        {
            // Store the initial value of used in case it's one of the initial seeds and shouldn't be reset to false
            bool initial_used_val = used[row][col];
            used[row][col] = true;

            int total_boards = get_possible_boards(board, next_row, next_col, used, zeroes, ones);
            if (board[row][col])
            {
                ones[row][col] += total_boards;
            }
            else
            {
                zeroes[row][col] += total_boards;
            }

            used[row][col] = initial_used_val;
            return total_boards;
        }
    }
    
    // try generating boards with a 1 in this position
    board[row][col] = true;
    used[row][col] = true;
    int total_ones = get_possible_boards(board, next_row, next_col, used, zeroes, ones);
    ones[row][col] += total_ones;
    
    // now try again with a zero
    board[row][col] = false;
    int total_zeroes = get_possible_boards(board, next_row, next_col, used, zeroes, ones);
    zeroes[row][col] += total_zeroes;
    
    // reset the used section
    used[row][col] = false;
    
    // return the number of valid boards in this config
    return total_ones + total_zeroes;
}

int main()
{
    srand(time(0));

    // a grid of trues and falses representing the 1's and 0's respectively on a takuzu board
    bool** board = new bool *[SIZE];
    
    // which parts of the board have been used
    bool** used = new bool *[SIZE];
    
    // the total boards that exist with either a 1 or 0 in each respective position given an initial board
    int** zeroes = new int *[SIZE];
    int** ones = new int *[SIZE];
    
    // reset the boards
    for(int i=0; i < SIZE; i++)
    {
        board[i] = new bool[SIZE];
        used[i] = new bool[SIZE];
        zeroes[i] = new int[SIZE];
        ones[i] = new int[SIZE];

        for(int j=0; j < SIZE; j++)
        {
            board[i][j] = false;
            used[i][j] = false;
            
        }
    }
    
    // plant a seed of a few initial positions on the board
    for(int i = 0; i < SEED_SIZE; i++)
    {
        int row = rand()%SIZE;
        int col = rand()%SIZE;
        board[row][col] = rand()%2;
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
        

        // Draw board
        for (int i = 0; i<SIZE; i++)
        {
            cout << "----";
        }
        cout << "-\n";
        for (int i = 0; i<SIZE; i++)
        {
            cout << "|";
            for (int j = 0; j<SIZE; j++)
            {
                cout << ones[i][j] << "/" << zeroes[i][j] << " ";
            }
            cout << "\n";
            for (int j = 0; j<SIZE; j++)
            {
                cout << "----";
            }
            cout << "-\n";
        }

        getchar();

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
                if((zeroes[i][j] != 0) && ((lowest_zero == 0) || (zeroes[i][j] < lowest_zero)))
                {
                    lowest_zero = zeroes[i][j];
                    lowest_zero_row = i;
                    lowest_zero_col = j;
                }
                if((ones[i][j] != 0) && ((lowest_one == 0) || (ones[i][j] < lowest_one)))
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
            used[lowest_zero_row][lowest_zero_col] = true;
        }
        else
        {
            board[lowest_one_row][lowest_one_col] = 1;
            used[lowest_one_row][lowest_one_col] = true;
        }

        if ((lowest_zero == 1) || (lowest_one == 1))
        {
            break;
        }
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

    getchar();

    return 0;
}