// Date : 29-09-2021        Status : Incomplete


// A == n+1 biits, Q == n bits, M == n+1 bits
#include <stdio.h>

int A[100], M_Bin[101], Q_Bin[101], M_TwosComp[101];
int count = 0, Quotient = 0, Remainder = 0;

void NonRestoringDiv(int, int);
void DeciToBin(int, int[]);
void TwosComp(int, int[]);
void BinToDeci(int[], int);

void main()
{
    int M, Q;

    printf("\nEnter the Divident:\t");
    scanf("%d", Q);
    
    printf("\nEnter the Divisor:\t");
    scanf("%d", M);

    NonRestoringDiv(M, Q);
}




void NonRestoringDiv(int M, int Q)  // Not sure it works yet-29-09-2021
{
    int count_resDiv;

    DeciToBin(Q, Q_Bin);
    DeciToBin(M, M_Bin);
    TwosComp(M, M_TwosComp);
    
    count_resDiv = count;
    while(count_resDiv >= 0)
    {
        // This if-else Block checks if A<0 is true or not and perfroms leftshift & A = A+M or A = A-M resp. 
        if(A[0] == 0)
        {
            ShiftLeft();
            AddBin(A, M_TwosComp);
        }
        else
        {
            ShiftLeft();
            AddBin(A, M_Bin);
        }

        // This if-else Block checks if A<0 is true or not and sets last bit of Q as ZERO or ONE resp.         
        if(A[0] == 0)
        {
            Q_Bin[count-1] = 1;
        }
        else
        {
            Q_Bin[count-1] = 0;
        }

        count_resDiv--;    // Decreaments the counter.
    }

    if(A[0] == 1)
    {
        AddBin(A, M_Bin);
    }
    BinToDeci(Q_Bin, Quotient);
    BinToDeci(A, Remainder);
    
}