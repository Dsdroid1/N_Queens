#include<stdio.h>
#include<string.h>

#define MAX_BOARD_SIZE 15


//--Some Structure Definitions-----------------------------------------
typedef struct Board
{
    int size;
    int ChessBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
}Board;

void InitBoard(Board *Bptr,int n)
{
    Bptr->size=n;
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            Bptr->ChessBoard[i][j]=0;// 0 denotes nothing placed here,not kills here.
        }
    }
}

typedef enum {FALSE,TRUE} Bool;
//End of Structure Definitions-----------------------------------------

Bool Place(Board *B,int row,int col)
{
    int i,j;
    Bool CanPlace=TRUE;
    if(row >= 0 && col >= 0)
    {
        if(row < B->size && col < B->size)
        {
            if(B->ChessBoard[row][col] == 1)
            {
                    //Not possible to place here
                    //Call error
            }
            else
            {
                //Scratch off the entire row and column simultaneously
                for(j = 0; j < B->size && CanPlace==TRUE; j++)
                {
                    /*
                    B.ChessBoard[row][j] = 'x';
                    B.ChessBoard[j][col] = 'x';
                    */
                    if(B->ChessBoard[row][j]==1)
                    {
                        CanPlace=FALSE;
                    }
                    if(B->ChessBoard[j][col]==1)
                    {
                        CanPlace=FALSE;
                    }
                }
                //Scratch off the diagonals.
                /*
                    No.of rows above the given row = row
                    No.of rows below the given row = B.size-row
                    No.of cols before the given col = col
                    No.of cols after the given col = B.size-col
                */
                int valid=1;
                i=0;
                if(CanPlace==TRUE)
                {
                    while(valid)//From piece to upper left corner
                    {
                        i++;
                        if(row - i >= 0 && col - i >= 0)
                        {
                            //B.ChessBoard[row-i][col-i] = 'x';
                            if(B->ChessBoard[row-i][col-i]==1)
                            {
                                CanPlace=FALSE;
                                valid=0;
                            }
                        }
                        else
                        {
                            valid=0;
                        }
                    }   
                }
                if(CanPlace==TRUE)
                {
                    valid=1;
                    i=0;
                    while(valid)//From piece to lower right corner
                    {
                        i++;
                        if(row + i < B->size && col + i < B->size)
                        {
                            //B.ChessBoard[row+i][col+i] = 'x';
                            if(B->ChessBoard[row+i][col+i] == 1)
                            {
                                CanPlace=FALSE;
                                valid=0;
                            }
                        }
                        else
                        {
                            valid=0;
                        }
                    }
                }
                if(CanPlace==TRUE)
                {
                    valid=1;
                    i=0;
                    while(valid)//From piece to upper right corner
                    {
                        i++;
                        if(row - i >= 0 && col + i < B->size)
                        {
                            //B.ChessBoard[row-i][col+i] = 'x';
                            if(B->ChessBoard[row-i][col+i] == 1)
                            {
                                CanPlace=FALSE;
                                valid=0;
                            }
                        }
                        else
                        {
                            valid=0;
                        }
                    }
                }
                if(CanPlace==TRUE)
                {
                    valid=1;
                    i=0;
                    while(valid)//From piece to lower left corner
                    {
                        i++;
                        if(row + i < B->size && col - i >= 0)
                        {
                            //B.ChessBoard[row+i][col-i] = 'x';
                            if(B->ChessBoard[row+i][col-i] == 1)
                            {
                                CanPlace=FALSE;
                                valid=0;
                            }
                        } 
                        else
                        {
                            valid=0;
                        }
                    }
                }
                if(CanPlace==TRUE)
                {
                    //Finally,place the queen at (row,col)
                    B->ChessBoard[row][col]=1;//1 denotes queen is present
                }
            }
        
        }
            
    }  
    return CanPlace;  
}

void Withdraw(Board *B,int row,int col)
{
    if(row >= 0 && col >= 0)
    {
        if(row < B->size && col < B->size)
        {
            if(B->ChessBoard[row][col]==1)
            {
                B->ChessBoard[row][col]=0;
            }
        }
    }
}

Bool Play_N_Queens(Board *B,int curr_row)
//Initial call (B,0)
{
    int i,j,done=0;
    Bool retval=TRUE;
    if(B->size-curr_row != 0)
    {
        for(i = 0 ; i < B->size && done==0 ;i++)
        {
            retval=Place(B,curr_row,i);
            if(retval==TRUE)
            {
                //Placing successful,move to next row
                retval=Play_N_Queens(B,curr_row+1);
                //if backtracking,i.e not successful
                if(retval==FALSE)
                {
                    Withdraw(B,curr_row,i);
                }
                else
                {
                    done=1;
                }   
            }
        }
        if(done == 0 && i == B->size)
        {
            //We were not able not place any queen in this row,thus not possible
            retval=FALSE;
        }
    }
    else
    {
        //All queens were placed,the job is done
        retval=TRUE;
        for(i=0;i<B->size;i++)
        {
            printf("\n");
            for(j=0;j<B->size;j++)
            {
                printf("%d ",B->ChessBoard[i][j]);
            }
        }
    } 
    return retval;
}

void main()
{
    int n;
    Board B;
    printf("\nEnter the board size(<%d):",MAX_BOARD_SIZE);
    scanf("%d",&n);
    InitBoard(&B,n);
    printf("\nThe solution possible is:");
    Bool possible=Play_N_Queens(&B,0);
    if(possible==FALSE)
    {
        printf("\nNo possible solution");
    }
}
