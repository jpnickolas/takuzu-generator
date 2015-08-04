#define SIZE 8
#define SEED_SIZE 4

int main()
{
    bool board[SIZE][SIZE];
    bool used[SIZE][SIZE];
    
    for(int i=0; i < SIZE; i++)
    {
        for(int j=0; j < SIZE; j++)
        {
            board[i][j] = false;
            used[i][j] = false;
        }
    }
    
    return 0;
}