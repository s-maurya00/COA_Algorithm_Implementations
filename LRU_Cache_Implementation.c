// Date : 15-11-2021        Status : Complete

//Objective - Lru cache implementation: accept memory size between 1-5; next ask number of pages to be added; next ask for all page to be added at once; maintatin hit and fault count; remove unused pages if new is to be inserted; display cache storage for each added element; display hit ratio.

//IMP ==> Here, when we declare an array along with initialization, the elements that have not been initialized get initialize to zero directly by the compiler


// hit ratio = (number of hits / (total number cache hits + faults))


#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX 5

// functions: main, lru(will call and maintain counter & hit ratio), 
int convert_input(int [], char []);     // Done  // Takes string input of pages and converts & stores them into integer array
int LRU(int, int, int []);



void main()
{
    int size, pages[100], totFrame = 0, numOfInp;
    char strInp[100];

    while(1)
    {
        printf("\nEnter number of frame(only between 1 & 5) in cache:\t");
        scanf("%d", &totFrame);
        if(totFrame > 0 && totFrame < 6)
        {
            break;
        }
    }

    printf("\nEnter all pages to be added(separated by a blank space):");
    printf("\nNOTE: Input must have a whitespace at the end of the string:");
    printf("\nEg. ==> '1 2 3 2 1 4 3 4 5 3 6 '\n");

    gets(strInp);
    gets(strInp);

    numOfInp = convert_input(pages, strInp);

    printf("The entered pages are: \t");
    for(int i = 0; i <= numOfInp; i++)
    {
        printf("%d ", pages[i]);
    }
    printf("\n");

    LRU(totFrame, numOfInp, pages);
    getch();
}




// converts single line string input into array of integers input and returns its size
int convert_input(int K[], char strInp[200])    // Works Perfectly - 28-11-2021
{
    int j=0, i=0, temp=0;
    while(strInp[i] != '\0')
    {
        temp = 0;
        while(strInp[i] != ' ')
        {
            temp = temp*10 + (strInp[i++] - '0');   // str[i]-'0' works as follows: str[i] returns a string char containing a number. When we perform eg. '4' - '0' ==> we get, subtraction of their ASCII value ==>  52-48 = 4; Hence, we get 4 as a value.
        }
        if(strInp[i] == ' ')
        {
            i++;
        }
        K[j++] = temp;
    }
    return j-1;
}




int LRU(int totFrame, int numOfInp, int pages[])
{
    int hitCount = 0, faultCount = 0;
    int flag = 0;           // To goto next iteration if hit encountered in initial frame filling
    int posToUpdate = 0;    // stores the position for lruArr to update for the first filling of frames
 //   int posLruOrder = totFrame;    // will assign the lruorder in lruArr[1][i] as per requirement
    int frames[totFrame];   // array to store all frames of cache
    int lruArr[2][totFrame];   // 1st row to store the last entered new cache page & 2nd to store entry order. Higher No. of lruArr[1][i] means recently used
    
    for(int i = 0 ; i < 2; i++) //assigns all values as -1 in the 2D-lruArr array
    {
        for(int j = 0; j < totFrame; j++)
        {
            lruArr[i][j] = -1;
        }
    }

    // Prints frame number headings
    printf("\n|  Page Data\t|  Hit/Miss\t");
    for(int i = 0; i < totFrame; i++)
    {
        printf("|  Frm%d\t", i+1);
    }

    // prints appropriate number of frame designs
    printf("|\n|---------------|---------------|");
    for(int i = 0; i < totFrame; i++)
    {
        printf("-------|");
    }
    printf("\n");


    for(int i = 0; i <= numOfInp; i++)
    {
        printf("|  %d\t\t", pages[i]);  //prints page Data for 1st column

        flag = 0;
        for(int j = 0; j < totFrame; j++)   // Loop for checking HITs
        {
            if(lruArr[0][j] == pages[i])   // if HIT, then carry below code and break loop
            {
                hitCount++;
                printf("|  Hit\t\t");
                for(int k = 0; k < totFrame; k++)
                {
                    printf("|  %d\t", lruArr[0][k]);
                }
                printf("|\n");

                // prints design
                printf("|---------------|---------------|");
                for(int k = 0; k < totFrame; k++)
                {
                    printf("-------|");
                }
                printf("\n");

                // To assign LruOrder
                int countUpto = lruArr[1][j];
                lruArr[1][j] = totFrame + 1;    // assigning totFrame+1 since it will be reduced by one in the loop below
                for(int k = 0; k < totFrame; k++)
                {
                    if(countUpto < lruArr[1][k])
                    {
                        lruArr[1][k]--;
                    }
                }

                flag = 1;
                break;
            }
        }
        if(flag == 1)   // goto next iteration since this iteration encountered a hit
        {
            continue;
        }

        faultCount++;

        if(posToUpdate < totFrame)  // if frames are still vacant and it is a fault
        {
            lruArr[0][posToUpdate] = pages[i];
            
            // To assign LruOrder
            lruArr[1][posToUpdate] = totFrame + 1;
            for(int j = 0; j < totFrame; j++)
            {
                if(0 < lruArr[1][j])
                {
                    lruArr[1][j]--;
                }
            }
            posToUpdate++;
            
        }
        else        // if frames are not vacant, we have to replace page
        {
            for(int j = 0; j < totFrame; j++)
            {
                if(lruArr[1][j] == 1)
                {
                    lruArr[0][j] = pages[i];

                    // To assign LruOrder
                    lruArr[1][j] = totFrame + 1;
                    for(int k = 0; k < totFrame; k++)
                    {
                        lruArr[1][k]--;
                    }
                    break;
                }
            }
        }

        printf("|  Miss\t\t");
        for(int j = 0; j < totFrame; j++)
        {
            printf("|  %d\t", lruArr[0][j]);
        }

        //prints design
        printf("|\n|---------------|---------------|");
        for(int j = 0; j < totFrame; j++)
        {
            printf("-------|");
        }
        printf("\n");
    }

    printf("\nThe hit count is:\t%d", hitCount);
    printf("\nThe fault count is:\t%d", faultCount);

    float hitRatio;
    hitRatio = (float)hitCount/(hitCount+ faultCount);

    printf("\nThe Hit Ratio is:\t%f", hitRatio);
}