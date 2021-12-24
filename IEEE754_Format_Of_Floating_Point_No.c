// Date : 20-10-2021        Status : Incomplete

//Objective - Choice based Short Real or Long Real Representation step by step
//Can try Multiplication, division, addition & subtraction of Floating point numbers also ==> Not required in Exp5(can be self experience)

//IMP ==> Here, when we declare an array along with initialization, the elements that have not been initialized get initialize to zero directly by the compiler

#include <stdio.h>

void IEEE754(int, double);       //function to completely display either Single precision & Double precision format of entered number
void DeciToBin(double num, int BinArr[], int Flag);     //Flag : 0 ==> integer part & 1 ==> fraction part
void SinglePrecision(int[]);
void DoublePrecision(int[]);

int count = 0, Sign = 0;
double num;


void main()
{
    int num_int;            //num_int is integer part of num
    double num_fract;       //num is user entered number; num_fract is fractional part of num

    printf("\nEnter the Floating point number:\t");
    scanf("%lf", &num);

    if(num > 0.0)
    {
        Sign = 0;
    }
    else if(num == 0.0)
    {
        //Display code:
        printf("\nSingle Precision Representation of the Floating point No %lf is:\n\n", num);
        printf("------------------------------------------------\n");
        printf("| 0 | 0000 0000 | 0000 0000 0000 0000 0000 000 |");
        printf("\n------------------------------------------------\n");

        printf("\nDouble Precision Representation of the Floating point No %lf is:\n\n", num);
        printf("----------------------------------------------------------------------------------------\n");
        printf("| 0 | 000 0000 0000 | 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 |");
        printf("\n----------------------------------------------------------------------------------------\n");
        return;
    }
    else    //If number if negative, Just change the Sign bit to 1 and num to its positive value for calculation purpose
    {
        Sign = 1;
        num = -num; 
    }
    num_int = (int)num;

    num_fract = (num-num_int);

    IEEE754(num_int, num_fract);
    getch();
}



void IEEE754(int num_int, double num_fract) //works till date -> 22-10-2021
{
    int num_int_bin[52] = {0}, num_fract_bin[104] = {0};   //Here, when we declare an array along with initialization, the elements that have not been initialized get initialize to zero directly by the compiler
    
    if(num_int != 0)    //checks if num_int is non-zero
    {
        DeciToBin((double)num_int, num_int_bin, 0); //converting integer part to binary
    }

    DeciToBin(num_fract, num_fract_bin, 1);     //converting fraction part to binary

    printf("\nBefore: Displaying reversed num_int_BIN:\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d", num_int_bin[i]);
    }

    printf("\nDisplaying reversed num_fract_BIN:\t");
    for(int i = 0; i < 52; i++)
    {
        printf("%d", num_fract_bin[i]);
    }

    if((num_int != 0) || (num_int != 1))
    {
        for(int i = 51; i >= count-1; i--)  //loop for shifting the mantissa part to get the space for adding the bits of num_int_bin
        {
            num_fract_bin[i] = num_fract_bin[i-(count-1)];
        }

        for(int i = count-1; i > 0; i--)    //loop for inserting count-1 elements in begining of mantissa
        {
            num_fract_bin[i-1] = num_int_bin[i];
        }
    }
    else if(num_int == 0)
    {
        
    }

    SinglePrecision(num_fract_bin);
    DoublePrecision(num_fract_bin);
}



void DeciToBin(double numFloat, int BinArr[], int Flag) //works till date->22-10-2021
{
    int rem, temp_count; //temp[52];
    double diff;

    if(Flag == 0)   //For integer part & Exponent part
    {
        temp_count = 0;
        int n = numFloat;
        while(n > 0)
        {
            rem = n % 2;
            BinArr[temp_count] = rem;
            n = n / 2;
            temp_count++;
        }
        // for(int i = 0; i < temp_count; i++)
        // {
        //     BinArr[i] = temp[temp_count-i-1];
        // }
        if(count == 0)
        {
            count = temp_count;
        }
    }
    else    //For fraction part
    {
        for(int i = 0; i < 52; i++)
        {
            numFloat = numFloat * 2;    // doubling the fraction part
            rem = (int)numFloat;        // stores the integer part after multiplication by 2

            BinArr[i] = rem;
            
            diff = numFloat - rem;      // stores the fraction part after multiplication by 2

            if(diff != 0.0)             // if diff is zero that means that the remaining bits of num_fract will be zero
            {
                numFloat = diff;
            }
            else
            {
                return;
            }

        }
    }
}




void SinglePrecision(int BinFract[])    //calculates biased exponenet for SinglePrecision Representation
{
    int exp_bin[8] = {0};
    int exp;

    exp = 126 + count;  //biase to be added is 127 + count - 1

    DeciToBin(exp, exp_bin, 0);

    //Display code:
    printf("\nSingle Precision Representation of the Floating point No %lf is:\n\n", num);

    printf("-------------------------------------------------\n");
    printf("| %d | ", Sign);

    for(int i = 0; i < 8; i++)
    {
        if(i == 4)
        {
            printf(" ");
        }
        printf("%d", exp_bin[i]);
    }

    printf(" | ");
    
    for(int i = 0; i < 23; i++)
    {
        if(i % 4 == 0)
        {
            printf(" ");
        }
        printf("%d", BinFract[i]);
    }

    printf(" | ");
    printf("\n-------------------------------------------------\n");
}




void DoublePrecision(int BinFract[])    //calculates biased exponenet for DoublePrecision Representation
{
    int exp_bin[11] = {0};
    int exp;

    exp = 1022 + count;  //biase to be added is 1023 + count - 1

    DeciToBin(exp, exp_bin, 0);

    //Display code:
    printf("\nDouble Precision Representation of the Floating point No %lf is:\n\n", num);

    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %d | ", Sign);

    for(int i = 0; i < 11; i++)
    {
        if((i == 3) || (i == 7))
        {
            printf(" ");
        }
        printf("%d", exp_bin[i]);
    }

    printf(" | ");
    
    for(int i = 0; i < 52; i++)
    {
        if(i % 4 == 0)
        {
            printf(" ");
        }
        printf("%d", BinFract[i]);
    }

    printf(" | ");
    printf("\n-----------------------------------------------------------------------------------------\n");
}