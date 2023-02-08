#include <stdio.h>
#include <stdlib.h>
#define n 8

int chessboard[n][n];

int check1(int a ,int b)
// CHECKS THE BOUNDARY CONDITIONS
{
    if (a<0||b<0)
        return 0;
    else if (a>7||b>7)
        return 0;
    else
        return 1;
}
int check2(int a ,int b)
{
    if(chessboard[a][b]==0)
        return 0;
    else
        return 1;
}

int check3(int a, int b, int max)
{
    if (chessboard[a][b]>max)
        return 1;
    else
        return 0;
}

int move(int *x, int *y,int i,int j)
{
    int max_i=i,max_j=j,max=chessboard[i][j],a,b;

        if (check1((a=i+1),(b=j-2))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }
        if (check1((a=i+1),(b=j+2))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }
        if (check1((a=i+2),(b=j-1))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }
        if (check1((a=i+2),(b=j+1))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }
        if (check1((a=i-1),(b=j-2))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }
        if (check1((a=i-1),(b=j+2))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }
        if (check1((a=i-2),(b=j-1))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }
        if (check1((a=i-2),(b=j+1))&&check2(a,b)&&check3(a,b,max))
        {
            max_i=a;
            max_j=b;
            max=chessboard[a][b];
        }


    if (max!=0)
    {
        *x = max_i;
        *y = max_j;
        chessboard[max_i][max_j]=-1;
        return 1;
    }
    else
        return 0;
}

void display(int A[8][8], int rows, int cols)
{
    int i,j;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

}


int main()
{
    int i,j,k,*x,*y,a;

    for (i=0;i<n;i++)
    {

        for (j=0;j<8;j++)
        {
            chessboard[i][j]=0;
            if ((i==0||i==7||j==0||j==7))
            {
                chessboard[i][j]=8;
                if ((i-j)==0||(i+j)==7)
                    chessboard[i][j]=9;
            }
            if ((i==1||i==6||j==1||j==6)&&chessboard[i][j]==0)
            {
                chessboard[i][j]=6;
                if ((i-j)==0||(i+j)==7)
                    chessboard[i][j]=7;
            }
            if ((i==2||i==5||j==2||j==5)&&chessboard[i][j]==0)
            {
                chessboard[i][j]=4;
                if ((i-j)==0||(i+j)==7)
                    chessboard[i][j]=5;
            }
            if ((i==3||i==4||j==3||j==4)&&chessboard[i][j]==0)
            {
                    chessboard[i][j]=3;
            }

        }
    }

    display(chessboard,n,n);

    printf("\n\n----- THE KNIGHT STARTS MOVING -----\n\n");
    printf("(-1) INDICATES WHERE THE KNIGHT IS PRESENT\n(0) INDICATES THE BLOCKS VISITED\n");
    printf("\n----------------------------------------------------\n\n\n\n");
    chessboard[0][0]=-1;
    display(chessboard,n,n);
    printf("\n----------------------------------------------------\n\n\n\n");
    for(k=0,i=0,j=0;k<n*n;k++)
    {
        chessboard[i][j]=0;
        x=&i;
        y=&j;
        a=move(x,y,i,j);
        display(chessboard,n,n);
        if (a==0)
            {
                printf("\n----------------------------------------------------\n");
                printf("\nTHE PROGRAM IS TERMINATED");
                printf("\nNUMBER OF STEPS TAKEN = %d\n",(k+1));
                printf("\n----------------------------------------------------\n");
                break;
            }
        else
        {
            printf("\nTHE KNIGHT HAS MOVED TO  --> i = %d , j = %d",i,j);
            printf("\n----------------------------------------------------\n\n\n");
        }

    }

}

