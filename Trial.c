// // What is getch() present in conio.h header file
// #include <stdio.h>
// #include <math.h>

// void RightShift(); //
// void TwosComp(int BinForm[], int TwosCompForm[]); //
// void AddBina(int a[], int M_comp[]); //
// void DeciToBin(int, int, int); // Complete

// int BinToDeci(); //
// int Q_Bin[50], M_Bin[50], M_TwosComp[50], Q_TwosComp[50], c[4], temp[4], Qminus1 = 0;
// int count = 0; //Globally stores the size of signed bit that is larger of the inputed two numbers
// int Accumulator[50];
// int o[8] = {0,0,0,1}; //??


// void main()
// {
//     int M, Q;   // Multiplicant == M and Multiplier == Q
//     int *p_m_temp, *p_m_twoscomp;

//     printf("Enter the multiplicand: \n");
//     scanf("%d", &M);

//     printf("Enter the multiplier: \n");
//     scanf("%d", &Q);

//     DeciToBin(M, Q, 1);    
    
//     printf("\nThe count using global variable is: %d\n", count);

//     p_m_temp = &M_Bin;
//     p_m_twoscomp = &M_TwosComp;

//     for(int i = 0; i < count; i++)
//     {
//         *(p_m_twoscomp + i) = *(p_m_temp + i);
//     }

//     printf("\nprinting m_bin\n");
//     for(int i = 0; i < count; i++)
//     {
//         printf("%d", M_Bin[i]);
//     }

//     printf("\nprinting m_twoscomp\n");
//     for(int i = 0; i < count; i++)
//     {
//         printf("%d", M_TwosComp[i]);
//     }
// }



// void DeciToBin(int M, int Q, int Flag) //Complete
// // This function converts decimal to binary and makes the number of bits to 'NumberOfBitsOfMaxNumber + 1'
// {
//     int count_M = 0, count_Q = 0, rem = 0, i = 0, j = 0, bin_rev_M[50], bin_rev_Q[50];
    
//     while(M > 0) //Loop for converting 'M' in reversed binary
//     {
//         rem = M % 2;
//         bin_rev_M[count_M] = rem;
//         M = M / 2;
//         count_M++;
//     }

//     while(Q > 0) //Loop for converting 'Q' in reversed binary
//     {
//         rem = Q % 2;
//         bin_rev_Q[count_Q] = rem;
//         Q = Q / 2;
//         count_Q++;
//     }

//     if(count_M > count_Q)
//     {
//         count = count_M + 1; //The number of digits in total signed array

//         bin_rev_M[count_M] = 0; // for adding one '0' bit to array 'M'

//         for(i = count_Q; i <= count_M; i++) // for adding ((count_M + 1) - count_Q) number of bits to array 'Q'
//         {
//             bin_rev_Q[i] = 0;
//         }
//     }
//     else
//     {
//         count = count_Q + 1; //The number of digits in total signed array
        
//         bin_rev_Q[count_Q] = 0; // for adding one '0' bit to array 'Q'

//         for(i = count_M; i <= count_Q; i++) // for adding ((count_Q + 1(this +1 is for an extra signed bit)) - count_M) number of bits to array 'M'
//         {
//             bin_rev_M[i] = 0;
//         }        
//     }

//     switch(Flag)
//     {
//         case 1: // Both +ve
//         {
//             for(i = 0, j = count_M; i <=  count_M; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
//             {
//                 M_Bin[i] = bin_rev_M[j];
//             }

//             for(i = 0, j = count_Q; i <= count_Q; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
//             {
//                 Q_Bin[i] = bin_rev_Q[j];
//             }
//             break;
//         }
//         case 2: // M +ve & Q -ve
//         {
//             for(i = 0, j = count_M; i <=  count_M; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
//             {
//                 M_Bin[i] = bin_rev_M[j];
//             }

//             for(i = 0, j = count_Q; i <= count_Q; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
//             {
//                 Q_TwosComp[i] = bin_rev_Q[j];
//             }
//             // TwosComp(Q_TwosComp, Q_Bin);
//             break;
//         }
//         case 3: // M -ve & Q +ve
//         {
//             for(i = 0, j = count_M; i <=  count_M; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
//             {
//                 M_TwosComp[i] = bin_rev_M[j];
//             }

//             for(i = 0, j = count_Q; i <= count_Q; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
//             {
//                 Q_Bin[i] = bin_rev_Q[j];
//             }
//             break;
//         }
//         case 4: // Both -ve
//         {
//             for(i = 0, j = count_M; i <=  count_M; i++, j--) //Loop for reversing 'M' and bringing the binary digits in correct order
//             {
//                 M_TwosComp[i] = bin_rev_M[j];
//             }

//             for(i = 0, j = count_Q; i <= count_Q; i++, j--) //Loop for reversing 'Q' and bringing the binary digits in correct order
//             {
//                 Q_TwosComp[i] = bin_rev_Q[j];
//             }
//             // TwosComp(Q_TwosComp, Q_Bin);
//             break;
//         }
//     }

// }

#include <stdio.h>

void main()
{
    int rem, result = 0, base = 1;
    int Result_Bin[] = {0,0,1,1,1,1,1,0,0,0,0,0,0,1};
    for(int i = 13; i >= 0; i--)
    {
        rem = Result_Bin[i];
        result = result + (rem * base);
        base = base * 2;
    }
    printf("%d", result);
}