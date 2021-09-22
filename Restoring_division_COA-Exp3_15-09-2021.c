// Date : 17-09-2021   Status: Completed

//Program a code for restoring division

#include <stdio.h>

void DeciToBin(int, int[]);
void BinToDeci(int[], int*);
void TwosComp(int[], int[]);

void ShiftLeft();           //Left shifts the bits of 'A' and 'Q'
void AddBin(int[]);
void RestoringDivAlgo(int);    //Performs and calls respective functions to execuite the restoring division Algorithm
void Display(int);

int Accumulator[50], M_Bin[50], M_TwosComp[50], Q_Bin[50];
int count = 0, Quotient = 0, Remainder = 0, count_for_disp = 0;



void main()
{
    int M, Q, SignFlag;

    printf("\nEnter the Divident:\t");
    scanf("%d", &Q);

    printf("\nEnter the Divisor:\t");
    scanf("%d", &M);

    printf("\n");

    if(M == 0)    //Special cases
    {
        printf("\nCannot divide a number by zero!!!\nPlease Re-enter the divisor:\t");
        scanf("%d", &M);
        if(M == 0)
        {
            printf("Looks like you are persistant about dividing by zero.\nVery well, Your answer is:\n\nQuotient:\tINFINITY!!!\nRemainder:\t0\nThank You (^-^)\n\n");
            return;
        }
    }
    if(Q < M)   // Divident is less than Divisor
    {
        printf("Since the Divident is less than the Divisor, \nThe Quotient will be:\t\t0");
        printf("\nAnd the Remainder will be:\t%d\n\n", Q);
        return;
    }


    //This if-else block determines signs of quotient and the remainder
    if(M > 0 && Q > 0)
    {
        DeciToBin(Q, Q_Bin);
        DeciToBin(M, M_Bin);
        SignFlag = 1;
    }
    else if(M > 0 && Q < 0)
    {
        DeciToBin(-Q, Q_Bin);
        DeciToBin(M, M_Bin);        
        SignFlag = 2;
    }
    else if(M < 0 && Q > 0)
    {
        DeciToBin(Q, Q_Bin);
        DeciToBin(-M, M_Bin);        
        SignFlag = 3;
    }
    else
    {
        DeciToBin(-Q, Q_Bin);
        DeciToBin(-M, M_Bin);        
        SignFlag = 4;
    }

    TwosComp(M_Bin, M_TwosComp);
    
    Display(0);
    
    RestoringDivAlgo(SignFlag);
}



void RestoringDivAlgo(int SignFlag) //Works Fine;
{
    while(count_for_disp > 0)
    {
        ShiftLeft();
        Display(1);

        AddBin(M_TwosComp);
        Display(2);

        if(Accumulator[0] == 1)
        {
            Q_Bin[count-1] = 0;
            AddBin(M_Bin);
            Display(3);
        }
        else if(Accumulator[0] == 0)
        {
            Q_Bin[count-1] = 1;
            Display(4);
        }
        count_for_disp--;
    }

    BinToDeci(Accumulator, &Remainder);
    BinToDeci(Q_Bin, &Quotient);

    printf("\nThe Binary form of Quotient is:\t\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d", Q_Bin[i]);
    }

    printf("\nAnd the Binary form of Remainder is:\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d", Accumulator[i]);
    }

    if(SignFlag == 1)
    {
        printf("\n\nConsequently, the Decimal equivalent of Quotient will be:\t%d", Quotient);
        printf("\nAnd the Decimal equivalent of Remainder will be:\t\t%d\n\n", Remainder);
    }
    else if(SignFlag == 2)
    {
        printf("\n\nConsequently, the Decimal equivalent of Quotient will be:\t%d", -Quotient);
        printf("\nAnd the Decimal equivalent of Remainder will be:\t\t%d\n\n", -Remainder);
    }
    else if(SignFlag == 3)
    {
        printf("\n\nConsequently, the Decimal equivalent of Quotient will be:\t%d", -Quotient);
        printf("\nAnd the Decimal equivalent of Remainder will be:\t\t%d\n\n", Remainder);
    }
    else
    {
        printf("\n\nConsequently, the Decimal equivalent of Quotient will be:\t%d", Quotient);
        printf("\nAnd the Decimal equivalent of Remainder will be:\t\t%d\n\n", -Remainder);
    }
}



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
        count_for_disp = count;
    }

    for(j = i; j <= count; j++) //Append zeros to the reverse binary form to make the bits of 'Q' from n to n+1
    {
        BinConv_reversed[j] = 0;
    }

    for(i = 0, j = (count-1); i < count; i++, j--)
    {
        BinConv[i] = BinConv_reversed[j];
    }
}



void TwosComp(int Bin[], int BinsTwoComp[]) //Works as intended
{
    int i = count-1;
    
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



void Display(int Flag)      //Works as intended
{
    //Flag = 0(intial disp); 1(ShiftLeft disp); 2(A = A-M); 3(Since A<0, Q0 = 0 & A = A+M); 4(Since A>=0, Q0 = 1)
    int tabDisp = 0;

    if((count % 7) != 0)
    {
        tabDisp = (int)(count/7);
    }
    else if(count > 7)
    {
        tabDisp = (int)((count-1) / 7);
    }

    //This if else block is for displaying the correct description
    if(Flag == 0)
    {
        // printf("\t\t\t\t|\tA\t|\tQ\t|\tCount\n");
        printf("\t\t\t\t|\tA");
        for(int i = 0; i <= tabDisp; i++)
        {
            printf("\t");
        }
        // for(int i = 0; i <= tabDisp; i++)
        // {
        //     printf("\t");
        // }
        printf("|\tQ");
        for(int i = 0; i <= tabDisp; i++)
        {
            printf("\t");
        }
        printf("|\tCount\n");

        //Prints Design
        printf("--------------------------------|---------------");
        for(int i = 0; i < tabDisp; i++)
        {
            printf("--------");
        }
        printf("|---------------");
        for(int i = 0; i < tabDisp; i++)
        {
            printf("--------");
        }
        printf("|-----------------\n");

        printf("Initialization:\t\t\t|\t");
    }
    else if(Flag == 1)
    {
        printf("Left Shift AQ:\t\t\t|\t");
    }
    else if(Flag == 2)
    {
        printf("A = A - M:\t\t\t|\t");
    }
    else if(Flag == 3)
    {
        printf("Since A < 0, Q0 = 0 & A = A + M:|\t");
    }
    else if(Flag == 4){
        printf("Since A >= 0, Q0 = 1:\t\t|\t");
    }
    
    for(int i = 0; i < count; i++)
    {
        printf("%d", Accumulator[i]);
    }
    printf("\t|\t");

    if(Flag == 1 || Flag == 2)
    {
        for(int i = 0; i < (count-1); i++)
        {
            printf("%d", Q_Bin[i]);
        }
        printf("_\t|\n");
        return;
    }
    else
    {
        for(int i = 0; i < count; i++)
        {
            printf("%d", Q_Bin[i]);
        }
        printf("\t|\t");
    }


    if(Flag == 0)
    {
        printf("%d", count_for_disp);
        //Prints Design
        printf("\n--------------------------------|---------------");
        for(int i = 0; i < tabDisp; i++)
        {
            printf("--------");
        }
        printf("|---------------");
        for(int i = 0; i < tabDisp; i++)
        {
            printf("--------");
        }
        printf("|-----------------");
    }
    if(Flag == 3 || Flag == 4)
    {
        printf("%d", (count_for_disp-1));
        //Prints Design
        printf("\n--------------------------------|---------------");
        for(int i = 0; i < tabDisp; i++)
        {
            printf("--------");
        }
        printf("|---------------");
        for(int i = 0; i < tabDisp; i++)
        {
            printf("--------");
        }
        printf("|-----------------");
    }
    printf("\n");
}




void ShiftLeft()        //Works as intended
{
    for(int i = 0; i < (count - 1); i++)
    {
        Accumulator[i] = Accumulator[i+1];
    }
    Accumulator[count-1] = Q_Bin[0];
    for(int i = 0; i < (count-1); i++)
    {
        Q_Bin[i] = Q_Bin[i+1];
    }
}



void AddBin(int AddAM[])        //Works as intended
{
    int carry = 0;

    for(int i = (count-1); i >= 0; i--)
    {
        if(Accumulator[i] == 0 && AddAM[i] == 0)
        {
            if(carry == 0)
            {
                Accumulator[i] = 0;
                carry = 0;
            }
            else
            {
                Accumulator[i] = 1;
                carry = 0;
            }
        }
        else if(((Accumulator[i] == 0) && (AddAM[i] == 1)) || ((Accumulator[i] == 1) && (AddAM[i] == 0)))
        {
            if(carry == 0)
            {
                Accumulator[i] = 1;
                carry = 0;
            }
            else
            {
                Accumulator[i] = 0;
                carry = 1;
            }
        }
        else if(Accumulator[i] == 1 && AddAM[i] == 1)
        {
            if(carry == 0)
            {
                Accumulator[i] = 0;
                carry = 1;
            }
            else
            {
                Accumulator[i] = 1;
                carry = 1;
            }
        }
    }
}



void BinToDeci(int BinToDeci[], int *num)       //Works as intended
{
    int base = 1;
    for(int i = (count-1); i >= 0; i--)
    {
        *num = *num + (BinToDeci[i] * base);
        base = base * 2;
    }
}