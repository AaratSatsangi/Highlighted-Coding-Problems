#include <stdio.h>
#include <stdlib.h>


int p = 0,last_i =0, last_j =0, Q_placed =0,count=0;

void display(int *a,int N)
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if (*(a+i*N+j)==81)
                printf("%c ",*(a+i*N+j));
            else
                printf("%d ",*(a+N*i+j));
        }

        printf("\n");
    }
    printf("\n\n");
}

void conversion(int*a,int N)
{
    int i,j;
    int chess_board[N][N];
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if (*(a+i*N+j)<0)
                chess_board[i][j] = 81;
            else
                chess_board[i][j] = 1;
        }
    }
    display(chess_board,N);
}


void attack(int *a,int N,int queen_no)
{
    int i,j;

    *(a+N*last_i+last_j) = (-queen_no);
    for (i=last_i+1;i<N;i++)
        if(*(a+N*i+last_j)==0)
            *(a+N*i+last_j) = queen_no;

    for (i=last_i-1;i>=0;i--)
        if(*(a+N*i+last_j)==0)
            *(a+N*i+last_j) = queen_no;

    for (j=last_j+1;j<N;j++)
        if(*(a+N*last_i+j)==0)
            *(a+N*last_i+j) = queen_no;

    for (j=last_j-1;j>=0;j--)
        if (*(a+N*last_i+j)==0)
            *(a+N*last_i+j) = queen_no;

    for (i=last_i+1,j=last_j+1;i<N&&j<N;i++,j++)
        if(*(a+N*i+j)==0)
            *(a+N*i+j)=queen_no;

    for (i=last_i-1,j=last_j-1;i>=0&&j>=0;i--,j--)
        if(*(a+N*i+j)==0)
            *(a+N*i+j)=queen_no;

    for (i=last_i+1,j=last_j-1;i<N&&j>=0;i++,j--)
        if(*(a+N*i+j)==0)
            *(a+N*i+j)=queen_no;

    for (i=last_i-1,j=last_j+1;i>=0&&j<N;i--,j++)
        if(*(a+N*i+j)==0)
            *(a+N*i+j)=queen_no;
}

void anti_attack(int *a,int N,int queen_no)
{
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            if(abs(*(a+i*N+j))==queen_no)
                {*(a+i*N+j) = 0;
               // printf("anti :: \ni = %d , j = %d\n\n",i,j);
               }

}

void backtrack_move(int *a,int N)
{
    int i,prev_i = last_i;
    for(i=0;i<N;i++)
    {
        if(*(a+N*i+last_j)==0)
        {
            Q_placed++;
            last_i = i;
            attack(a,N,Q_placed);
            if(last_j<N-1)
            {
                last_j++;
                backtrack_move(a,N);
                p = 1;
            }
        }
        if(p&&Q_placed==N)
        {
            count++;
            printf("\nSOLUTION NUMBER :: %d \n",count);
            conversion(a,N);
            p = 0;
            anti_attack(a,N,Q_placed);
            Q_placed--;
        }
        if (i==N-1)
        {
            last_j--;
            last_i = prev_i;
            anti_attack(a,N,Q_placed);
            Q_placed--;
        }
    }
}

int main()
{
    int N,i,j;
    printf("N = ");
    scanf("%d", &N);
    int *a = (int*)calloc(N*N,sizeof(int));
    backtrack_move(a,N);
    free(a);
}
