// Date : 20-10-2021        Status : Incomplete

//Objective - Choice based Short Real or Long Real Representation step by step
//Can try Multiplication, division, addition & subtraction of Floating point numbers also ==> Not required in Exp5(can be self experience)

//IMP ==> Here, when we declare an array along with initialization, the elements that have not been initialized get initialize to zero directly by the compiler

#include <stdio.h>

void IEEE754(int, double);       //function to completely display either Single precision & Double precision format of entered number
void DeciToBin(double num, int BinArr[], int Flag);     //Flag : 0 ==> integer part & 1 ==> fraction part

int count = 0;



void main()
{
    int num_int;            //num_int is integer part of num
    double num, num_fract;   //num is user entered number; num_fract is fractional part of num

    printf("Enter the Floating point number:\t");
    scanf("%lf", &num);

    num_int = (int)num;

    num_fract = (num-num_int);

    IEEE754(num_int, num_fract);
}



void IEEE754(int num_int, double num_fract) //works till date -> 22-10-2021
{
    int num_int_bin[100] = {0}, num_fract_bin[52] = {0};   //Here, when we declare an array along with initialization, the elements that have not been initialized get initialize to zero directly by the compiler
    
    DeciToBin((double)num_int, num_int_bin, 0);

    DeciToBin(num_fract, num_fract_bin, 1);
    
    printf("\nDisplaying num_int_BIN:\t");
    for(int i = 0; i < count; i++)
    {
        printf("%d", num_int_bin[i]);
    }

    printf("\nDisplaying num_fract_BIN:\t");
    for(int i = 0; i < 52; i++)
    {
        printf("%d", num_fract_bin[i]);
    }
}



void DeciToBin(double numFloat, int BinArr[], int Flag) //works till date->22-10-2021
{
    int rem, temp[100];
    double diff;

    if(Flag == 0)
    {
        int num = numFloat;
        while(num > 0)
        {
            rem = num % 2;
            temp[count] = rem;
            num = num / 2;
            count++;
        }
        for(int i = 0; i < count; i++)
        {
            BinArr[i] = temp[count-i-1];
        }
    }
    else
    {
        for(int i = 0; i < 52; i++)
        {
            numFloat = numFloat * 2;    // doubling the fraction part
            rem = (int)numFloat;        // stores the integer part after multiplication by 2

            BinArr[i] = rem;
            
            diff = numFloat - rem;      // stores the fraction part after multiplication by 2

            if(diff != 0.0)
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