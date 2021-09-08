// Date : 25-08-2021    Status : Incomplete     Understood : ----
// Try own variation for multiplication of various signed numbers(maybe try storing numbers in a list)
// Objective: Booth's Algorithm

#include <stdio.h>
#include <math.h>


void DeciToBin(int M, int Q, int Flag);  // (Arg1: decimal M to convert into bin; Arg2: decimal Q to convert into Bin; Arg2: Flag indicating signs of M & Q) Complete
void TwosComp(int BinForm[], int TwosCompForm[]);  //(Arg1: bin array to be worked upon; Arg2:bin array where the result is to be stored) Complete
void AddBina(int Add_M[]);    //(Arg1: M_Bin or M_twoscomp)
void Display(int Flag);
void ARightShift(); //Does arithimetic shift right operation on A, Q and Q(-1)
void BinToDeci();    //prints the converted value of AQ as result


int Q_Bin[50], M_Bin[50], M_TwosComp[50], Q_TwosComp[50], Result_Bin[100], Result_TwosComp[100];
int count = 0, Qminus1 = 0, result = 0; //Globally stores the size of signed bit that is larger of the inputed two numbers
int Accumulator[50];




void main()     //Working and is correct
{
    int M, Q;   // Multiplicand == M and Multiplier == Q

    printf("Enter the multiplicand: \n");
    scanf("%d", &M);

    printf("Enter the multiplier: \n");
    scanf("%d", &Q);

    //if else for getting correct values of twoscomp and binary forms of M and Q
    if((M > 0) && (Q > 0)) //If M & Q both are +ve
    {
        DeciToBin(M, Q, 1);
    }
    else if((M > 0) && (Q < 0)) //If M is +ve & Q is -ve
    {
        DeciToBin(M, -Q, 2);
    }
    else if((M < 0) && (Q > 0)) //If M is -ve & Q is +ve
    {
        DeciToBin(-M, Q, 3);
    }
    else // both -ve
    {
        DeciToBin(-M, -Q, 4);
    }


    printf("M ==> \t");
    for(int i = 0; i < count; i++) //printing the binary value of Multiplicand
    {
        printf("%d", M_Bin[i]);
    }
    printf("\n-M ==> \t");
    for(int i = 0; i < count; i++) //printing the binary value of Two's Compliment of Multiplicand
    {
        printf("%d", M_TwosComp[i]);
    }
    printf("\nQ ==> \t");
    for(int i = 0; i < count; i++) //printing the binary value of Multiplier
    {
        printf("%d", Q_Bin[i]);
    }


    //Printing the initial values of A, Q and Q(-1) for the user
    printf("\n\t\t\tA\t\t|\tQ\t\t|\tQ(-1)\n");
    printf("\t\t\t----------------|-----------------------|----------------");
    printf("\nInitialization:");
    printf("\t\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d ", Accumulator[i]);
    }
    printf("\t|\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d ", Q_Bin[i]);
    }
    printf("\t|\t%d\n", Qminus1);


    //Booths Algo
    for(int i = count; i > 0; i--)
    {
        //If else to check the Q_bin[0]Q_minus1 bits and perform accordingly
        if(Q_Bin[count-1] > Qminus1)
        {
            AddBina(M_TwosComp);
            Display(2);

            ARightShift();
            Display(3);
        }
        else if(Q_Bin[count-1] < Qminus1)
        {
            AddBina(M_Bin);
            Display(1);

            ARightShift();
            Display(3);
        }
        else
        {
            ARightShift();
            Display(3);
        }
    }
    BinToDeci();
    printf("");
}



void DeciToBin(int M, int Q, int Flag) //Working and is correct
// This function converts decimal to binary and makes the number of bits to 'NumberOfBitsOfMaxNumber + 1'
{
    int count_M = 0, count_Q = 0, rem = 0, i = 0, j = 0, bin_rev_M[50], bin_rev_Q[50];

    while(M > 0) //Loop for converting 'M' in reversed binary
    {
        rem = M % 2;
        bin_rev_M[count_M] = rem;
        M = M / 2;
        count_M++;
    }

    while(Q > 0) //Loop for converting 'Q' in reversed binary
    {
        rem = Q % 2;
        bin_rev_Q[count_Q] = rem;
        Q = Q / 2;
        count_Q++;
    }

    if(count_M > count_Q)
    {
        count = count_M + 1; //The number of digits in total signed array

        bin_rev_M[count_M] = 0; // for adding one '0' bit to array 'M'

        for(i = count_Q; i <= count_M; i++) // for adding ((count_M + 1) - count_Q) number of bits to array 'Q'
        {
            bin_rev_Q[i] = 0;
        }
    }
    else
    {
        count = count_Q + 1; //The number of digits in total signed array
        
        bin_rev_Q[count_Q] = 0; // for adding one '0' bit to array 'Q'

        for(i = count_M; i <= count_Q; i++) // for adding ((count_Q + 1(this +1 is for an extra signed bit)) - count_M) number of bits to array 'M'
        {
            bin_rev_M[i] = 0;
        }        
    }

    switch(Flag)    // Used for knowing whether m&q are +ve or -ve and storing the binary in 'twoscomp array' or 'binary array' of that variable
    {
        case 1: // Both +ve
        {
            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
            {
                M_Bin[i] = bin_rev_M[j];
            }

            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
            {
                Q_Bin[i] = bin_rev_Q[j];
            }            
            TwosComp(M_Bin, M_TwosComp);
            break;
        }
        case 2: // M +ve & Q -ve
        {
            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
            {
                M_Bin[i] = bin_rev_M[j];
            }

            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
            {
                Q_TwosComp[i] = bin_rev_Q[j];
            }
            TwosComp(Q_TwosComp, Q_Bin);
            TwosComp(M_Bin, M_TwosComp);
            break;
        }
        case 3: // M -ve & Q +ve
        {
            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
            {
                M_TwosComp[i] = bin_rev_M[j];
            }

            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
            {
                Q_Bin[i] = bin_rev_Q[j];
            }
            TwosComp(M_TwosComp, M_Bin);
            break;
        }
        case 4: // Both -ve
        {
            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
            {
                M_TwosComp[i] = bin_rev_M[j];
            }

            for(i = 0, j = (count-1); i < count; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
            {
                Q_TwosComp[i] = bin_rev_Q[j];
            }
            TwosComp(Q_TwosComp, Q_Bin);
            TwosComp(M_TwosComp, M_Bin);
            break;
        }
    }

}



void TwosComp(int BinForm[], int TwosCompForm[])    //Working and is correct
// This function calculates the twos complement of entered number and saves it in the second argument pass to this function
{
    if(BinForm[count] == 1)
    {
        TwosCompForm[count] = 1;

        for(int i = (count - 1); i >= 0; i--)
        {
            if(BinForm[i] == 0)
            {
                TwosCompForm[i] = 1;
            }
            else
            {
                TwosCompForm[i] = 0;
            }
        }
    }
    else
    {
        TwosCompForm[count] = 0;
        int i = count - 1;

        while(BinForm[i] != 1)
        {
            TwosCompForm[i] = 0;
            i--;
        }

        TwosCompForm[i] = 1;
        i = i - 1;

        while(i >= 0)
        {
            if(BinForm[i] == 0)
            {
                TwosCompForm[i] = 1;
            }
            else
            {
                TwosCompForm[i] = 0;
            }
            i--;
        }
    }
}



void AddBina(int Add_M[])   //Cannot check unless i create ARightShift function
{
    int carry[count-1];
    carry[count-1] = 0;

    for(int i = (count-1); i >= 0; i--)
    {
        if(carry[i] == 0)    //right but not working
        {
            if((Accumulator[i] + Add_M[i]) == 0)
            {
                Accumulator[i] = 0;
                carry[i-1] = 0;
            }
            else if((Accumulator[i] + Add_M[i]) == 1)
            {
                Accumulator[i] = 1;
                carry[i-1] = 0;
            }
            else
            {
                Accumulator[i] = 0;
                carry[i-1] = 1;
            }
        }
        else //right but not working
        {
            if((Accumulator[i] + Add_M[i]) == 0)
            {
                Accumulator[i] = 1;
                carry[i-1] = 0;
            }
            else if((Accumulator[i] + Add_M[i]) == 1)
            {
                Accumulator[i] = 0;
                carry[i-1] = 1;
            }
            else
            {
                Accumulator[i] = 1;
                carry[i-1] = 1;
            }
        }
    }
}



void ARightShift()
{
    Qminus1 = Q_Bin[count-1];

    for(int i = (count-1); i > 0; i--)
    {
        Q_Bin[i] = Q_Bin[i-1];
    }

    Q_Bin[0] = Accumulator[count-1];

    for(int i = (count-1); i > 0; i--)
    {
        Accumulator[i] = Accumulator[i-1];
    }

    Accumulator[0] = Accumulator[1];
}

void Display(int Flag)
{
    if(Flag == 1)
    {
        printf("A = A + M:\t\t");
    }
    else if(Flag == 2)
    {
        printf("A = A - M:\t\t");
    }
    else
    {
        printf("ASR:\t\t\t");
    }

    for(int i = 0; i < count; i++)
    {
        printf("%d ", Accumulator[i]);
    }
    
    printf("\t|\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d ", Q_Bin[i]);
    }
    printf("\t|\t%d\n", Qminus1);

    if(Flag == 3)
    {
        printf("\t\t\t----------------|-----------------------|----------------\n");
    }
}

void BinToDeci()
{
    int rem, base = 1;  //These variables are used while converting binary back to the decimal format
    int Flag = 0;   // This variable indicates if result was negative or positive

    //concatinates the binary of 'A' and 'Q' into 'result_binary'
    int i = 0, j = 0;
    while(i < count)
    {
        Result_Bin[i] = Accumulator[i];
        i++;
    }
    while(j < count)
    {
        Result_Bin[i] = Q_Bin[j];
        j++;
        i++;
    }

    printf("\n\nThe Binary form of Result is:\t");
    for(i = 0; i < (2*count); i++)
    {
        printf("%d", Result_Bin[i]);
    }

    if(Result_Bin[0] == 1)  //Check if result is in twos comp form and changes it into original number by taking the twos comp again
    {
        printf("\nSince binary result is negative, we take its Two's Complement which is: ");
        Flag = 1;   //Indicates answer is negative

        if(Result_Bin[(2*count)-1] == 1)
        {
            Result_TwosComp[(2*count)-1] = 1;

            for(int i = ((2*count) - 2); i >= 0; i--)
            {
                if(Result_Bin[i] == 0)
                {
                    Result_TwosComp[i] = 1;
                }
                else
                {
                    Result_TwosComp[i] = 0;
                }
            }
        }
        else
        {
            Result_TwosComp[(2*count)-1] = 0;
            int i = (2*count) - 2;

            while(Result_Bin[i] != 1)
            {
                Result_TwosComp[i] = 0;
                i--;
            }

            Result_TwosComp[i] = 1;
            i = i - 1;

            while(i >= 0)
            {
                if(Result_Bin[i] == 0)
                {
                    Result_TwosComp[i] = 1;
                }
                else
                {
                    Result_TwosComp[i] = 0;
                }
                i--;
            }
        }

        for(i = 0; i < (2*count); i++)  //Printing the Twos complement of binary result if it is negative
        {
            printf("%d", Result_TwosComp[i]);
        }
    }


    if(Flag == 1)
    {
        //Converts binary result's Two's Complement to decimal form
        for(i = ((2*count)-1); i >= 0; i--)
        {
            rem = Result_TwosComp[i];
            result = result + (rem * base);
            base = 2*base;
        }
        printf("\nThe Result is:\t-%d\n\n", result);
    }
    else
    {
        //Converts binary result to decimal result
        for(i = ((2*count)-1); i >= 0; i--)
        {
            rem = Result_Bin[i];
            result = result + (rem * base);
            base = 2*base;
        }
        printf("\nThe Result is:\t%d\n\n", result);
    }
}