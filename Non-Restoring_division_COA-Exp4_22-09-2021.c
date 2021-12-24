// Date : 29-09-2021        Status : Completed


// A == n+1 bits, Q == n bits(inclusive of sign bit), M == n+1 bits
#include <stdio.h>

int A[100], M_Bin[101], Q_Bin[101], M_TwosComp[101];
int count = 0, Quotient = 0, Remainder = 0, count_resDiv = 0;
int Quo_sign = 0, Rem_sign = 0; //0 indicates positive sign and 1 indicates negative sign

void NonRestoringDiv(int, int);
void DeciToBin(int, int[]);     //works
void TwosComp(int[], int[]);
void ShiftLeft(int);    //Flag to print (1)"Since A<0" or (0)"Since  A>=0"
void AddBin(int[]);
void BinToDeci(int[], int *);
void Display();                 //works



void main()
{
    int Q, M;

    printf("\nEnter the Divident:\t");
    scanf("%d", &Q);
    
    printf("\nEnter the Divisor:\t");
    scanf("%d", &M);

    // If else block to determine the sign of quotient and remainder
    if((M > 0) && (Q > 0))          //example +5/+3, Quotient: +1, Remainder: +2
    {
        if(Q < M) //If statement to check if Q<M
        {
            printf("\nThe Quotient is:\t0");
            printf("\nThe Remainder is:\t%d", Q);
            return;
        }
        NonRestoringDiv(Q, M);
    }    
    else if((M > 0) && (Q < 0))     //example -5/+3, Quotient: -1, Remainder: -2
    {
        if(-Q < M) //If statement to check if Q<M
        {
            printf("\nThe Quotient is:\t0");
            printf("\nThe Remainder is:\t%d", Q);
            return;
        }        
        Quo_sign = 1;
        Rem_sign = 1;        
        NonRestoringDiv(-Q, M);
    }    
    else if((M < 0) && (Q > 0))     //example +5/-3, Quotient: -1, Remainder: +2
    {
        if(Q < -M) //If statement to check if Q<M
        {
            printf("\nThe Quotient is:\t0");
            printf("\nThe Remainder is:\t%d", Q);
            return;
        }        
        Quo_sign = 1;
        NonRestoringDiv(Q, -M);
    }
    else                            //example -5/-3, Quotient: +1, Remainder: -2
    {
        if(-Q < -M) //If statement to check if Q<M
        {
            printf("\nThe Quotient is:\t0");
            printf("\nThe Remainder is:\t%d", Q);
            return;
        }
        Rem_sign = 1;
        NonRestoringDiv(-Q, -M);
    }
    getch();
}




void NonRestoringDiv(int Q, int M)  // Not sure it works yet-29-09-2021
{
    DeciToBin(Q, Q_Bin);
    DeciToBin(M, M_Bin);
    
    TwosComp(M_Bin, M_TwosComp);

    Display(0);

    count_resDiv = count;
    while(count_resDiv > 0)
    {
        // This if-else Block checks if A<0 is true or not and perfroms leftshift & A = A+M or A = A-M resp. 
        if(A[0] == 0)
        {
            ShiftLeft(0);
            Display(1);

            AddBin(M_TwosComp);
            Display(2);
        }
        else
        {
            ShiftLeft(1);
            Display(1);

            AddBin(M_Bin);
            Display(3);
        }

        // This if-else Block checks if A<0 is true or not and sets last bit of Q as ZERO or ONE resp.         
        if(A[0] == 0)
        {
            Q_Bin[count-1] = 1;
            Display(5);
        }
        else
        {
            Q_Bin[count-1] = 0;
            Display(4);
        }

        count_resDiv--;    // Decreaments the counter.
    }

    if(A[0] == 1)
    {
        AddBin(M_Bin);
    }
    BinToDeci(Q_Bin, &Quotient);
    BinToDeci(A, &Remainder);

    //Determines result's sign
    if((Quo_sign == 0) && (Rem_sign == 0))
    {
        printf("\nThe Quotient is:\t%d", Quotient);
        printf("\nThe Remainder is:\t%d", Remainder);
    }
    else if((Quo_sign == 1) && (Rem_sign == 0))
    {
        printf("\nThe Quotient is:\t%d", -Quotient);
        printf("\nThe Remainder is:\t%d", Remainder);
    }
    else if((Quo_sign == 0) && (Rem_sign == 1))
    {
        printf("\nThe Quotient is:\t%d", Quotient);
        printf("\nThe Remainder is:\t%d", -Remainder);
    }
    else
    {
        printf("\nThe Quotient is:\t%d", -Quotient);
        printf("\nThe Remainder is:\t%d", -Remainder);
    }
}




void DeciToBin(int Deci, int BinConv[]) //Works as intended
{
    int i = 0, rem;
    int BinRev[101];

    while(Deci > 0)
    {
        rem = Deci & 1;
        BinRev[i] = rem;
        Deci = Deci >> 1;
        i++;
    }

    if(count == 0)
    {
        count = i + 1;
    }

    for(int j = i; j <= count; j++)
    {
        BinRev[j] = 0;
    }

    for(int i = 0, j = (count-1); i < count; i++, j--)
    {
        BinConv[i] = BinRev[j];
    }
}




void TwosComp(int Bin[], int BinTwosComp[])
{
    int i = count-1;
    while(Bin[i] != 1)
    {
        BinTwosComp[i] = Bin[i];
        i--;
    }
    
    BinTwosComp[i] = 1;
    i--;

    while(i >= 0)
    {
        if(Bin[i] == 0)
        {
            BinTwosComp[i] = 1;
        }
        else
        {
            BinTwosComp[i] = 0;
        }
        i--;
    }
}




void ShiftLeft(int Flag)    //Flag to print (1)"Since A<0" or (0)"Since  A>=0"
{
    if(Flag == 0)
    {
        printf("Since A >= 0, ");
    }
    else if(Flag == 1)
    {
        printf("Since A < 0, ");
    }

    int i = 0;
    while (i < count-1)
    {
        A[i] = A[i+1];
        i++;
    }
    A[i] = Q_Bin[0];
    
    i = 0;
    while(i < count-1)
    {
        Q_Bin[i] = Q_Bin[i+1];
        i++;
    }
    Q_Bin[count-1] = '_';
}




void AddBin(int AddM[])         //Works as intended
{
    int i = count-1, carry = 0;
    while(i >= 0)
    {
        if(carry == 0)
        {
            if((A[i] == 0) && (AddM[i] == 0))
            {
                A[i] = 0;
                carry = 0;
            }
            else if(((A[i] == 1) && (AddM[i] == 0)) || ((A[i] == 0) && (AddM[i] == 1)))
            {
                A[i] = 1;
                carry = 0;
            }
            else
            {
                A[i] = 0;
                carry = 1;
            }
        }
        else
        {
            if((A[i] == 0) && (AddM[i] == 0))
            {
                A[i] = 1;
                carry = 0;
            }
            else if(((A[i] == 1) && (AddM[i] == 0)) || ((A[i] == 0) && (AddM[i] == 1)))
            {
                A[i] = 0;
                carry = 1;
            }
            else
            {
                A[i] = 1;
                carry = 1;
            }
        }
        i--;
    }
}




void BinToDeci(int BinToDeci[], int *num)   //Works as intended
{
    int base = 1;
    for(int i = (count-1); i >= 0; i--)
    {
        *num = *num + (BinToDeci[i] * base);
        base = base * 2;
    }
}




void Display(int Flag)      //Works as intended
{
    //OG: Flag = 0(intial disp); 1(ShiftLeft disp); 2(A = A-M); 3(Since A < 0, Q0 = 0); 4(Since A >= 0, Q0 = 1)
    //New: Flag = 0(intial disp); 1(ShiftLeft disp); 2(A = A-M); 3(A = A+M); 4(Since A < 0, Q0 = 0); 5(Since A >= 0, Q0 = 1)
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
        printf("\nThe Divident is:\t\t==>");
        for(int i = 0; i < count; i++)
        {
            printf("%d", Q_Bin[i]);
        }

        printf("\nThe Divisor is:\t\t\t==>");
        for(int i = 0; i < count; i++)
        {
            printf("%d", M_Bin[i]);
        }

        printf("\nTwo's Complement of Divisor is:\t==>");
        for(int i = 0; i < count; i++)
        {
            printf("%d", M_TwosComp[i]);
        }

        // printf("\t\t\t\t|\tA\t|\tQ\t|\tCount\n");
        printf("\n\n\t\t\t\t|\tA");
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
        printf("Left Shift AQ:\t|\t");
    }
    else if(Flag == 2)
    {
        printf("A = A - M:\t\t\t|\t");
    }
    else if(Flag == 3)
    {
        printf("A = A + M:\t\t\t|\t");
    }
    else if(Flag == 4)
    {
        printf("Since A < 0, Q0 = 0:\t\t|\t");
    }
    else if(Flag == 5)
    {
        printf("Since A >= 0, Q0 = 1:\t\t|\t");
    }
    
    for(int i = 0; i < count; i++)
    {
        printf("%d", A[i]);
    }
    printf("\t|\t");

    if(Flag == 1 || Flag == 2 || Flag == 3)
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
        printf("%d", count);
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
    if(Flag == 2 || Flag == 3 || Flag == 4 || Flag == 5)
    {
        if(Flag == 4 || Flag == 5)  //prints count only if 'Q0' bit is set to '0' or '1'
        {
            printf("%d", (count_resDiv-1));
        }
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