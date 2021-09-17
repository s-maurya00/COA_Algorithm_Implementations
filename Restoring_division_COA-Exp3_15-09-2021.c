// Date : 17-09-2021   Status: Incomplete

//Program a code for restoring division

#include <stdio.h>

void DeciToBin(int, int[]);
int BinToDeci(int[]);
void TwosComp(int[], int[]);   

void ShiftLeft();       //Left shifts the bits of 'A' and 'Q'
void AddBin(int);       //Flag decides if we have to add 'M' or '-M' corresponding to '1' and '-1' respectively
void RestoringDivAlgo();    //Performs and calls respective functions to execuite the restoring division Algorithm
void Display(int);         //Displays the respective output in step of the Algorithm Flag '-1' suggests initial display and '0' suggests rest all

int Accumulator[50], M_Bin[50], M_TwosComp[50], Q_Bin[50];
int count = 0, Quotient = 0, Remainder = 0;



void main()
{
    int M, Q;

    printf("\nEnter the Divident:\t");
    scanf("%d", &Q);

    printf("\nEnter the Divisor:\t");
    scanf("%d", &M);

    DeciToBin(Q, Q_Bin);
    DeciToBin(M, M_Bin);

    TwosComp(M_Bin, M_TwosComp);
    
    // Display(-1);


    printf("\nThe binary of Q is:\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d", Q_Bin[i]);
    }

    printf("\nThe binary of M is:\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d", M_Bin[i]);
    }

    printf("\nThe Twos complement of M is:\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d", M_TwosComp[i]);
    }
    
    // RestoringDivAlgo();
}


/*
void RestoringDivAlgo() //Dont know if it works yet
{
    for(int i = 0; i < count; i++)
    {
        ShiftLeft();
        AddBin(-1);
        if(Accumulator[0] == 1)
        {
            Q_Bin[count-1] = 0;
            AddBin(1);
        }
        else if(Accumulator[0] == 0)
        {
            Q_Bin[count-1] = 1;
        }
    }

    BinToDeci(Accumulator);
    BinToDeci(Q_Bin);

    printf("\nThe Quotient is:\t%d", Quotient);
    printf("\nThe Remainder is:\t%d", Remainder);
}
*/


void DeciToBin(int Deci, int BinConv[]) //Works as intended
{
    int rem = 0, i = 0, j = 0;
    int BinConv_reversed[50];
    
    while(Deci > 0)    //Loop to convert decimal to reversed binary
    {
        rem = Deci % 2;
        BinConv_reversed[i] = rem;
        Deci = Deci / 2;
        i++;
    }

    if(count == 0)
    {
        count = i + 1;
    }

    for(j = i; j <= count; j++) //Append zeros to the reverse binary form to make the bits of 'Q'    as n+1
    {
        BinConv_reversed[j] = 0;
    }

    for(i = 0, j = (count-1); i < count; i++, j--)
    {
        BinConv[i] = BinConv_reversed[j];
    }
}



void TwosComp(int Bin[], int BinsTwoComp[]) //Dont know if it works yet
{
    int i = count-1;
    
    printf("The count is: %d", count);
    if(Bin[count-1] == 1)
    {
        BinsTwoComp[count-1] = 1;
        for(i = (count-2); i >= 0; i--)
        {
            if(Bin[i] == 0)
            {
                BinsTwoComp[i] = 1;
            }
            else
            {
                BinsTwoComp[i] = 0;
            }
        }
    }
    else
    {
        while(Bin[i] != 1)
        {
            BinsTwoComp[i] = 0;
            i--;
        }
        BinsTwoComp[i] = 1;
        i--;
        for(int j = i; j >= 0; j--)
        {
            if(Bin[j] == 0)
            {
                BinsTwoComp[j] = 1;
            }
            else
            {
                BinsTwoComp[j] = 0;
            }
        }
    }
}