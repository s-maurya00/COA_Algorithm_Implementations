// Date : 29-09-2021        Status : Incomplete        Understood : NO

#include <stdio.h>

struct node
{
    int bits;
    int bits_pos;
    struct node *link;
};

struct node *M_LL = NULL;
struct node *Q_LL = NULL;

void NonRestoringDiv(int, int, int);

void main()
{
    int M, Q, count;

    printf("\nEnter the Multiplicand:\t");
    scanf("%d", M);
    
    printf("\nEnter the Multiplier:\t");
    scanf("%d", Q);

    NonRestoringDiv(M, Q, count);
}

void NonRestoringDiv(int M, int Q, int count)
{
    
}