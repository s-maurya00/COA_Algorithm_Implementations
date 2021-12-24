// Date: 22-11-2021     Status: Incomplete      Understood: NO

// Objective: implement FIFO cache clearing techinique

#include <stdio.h>

void FIFO(int, int, int []);
int convert_input(int[], char[]);


void main()
{
    int totFrame, numOfInp;
    int pages[100]; 
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

    FIFO(totFrame, numOfInp, pages);

    getch();
}



int convert_input(int K[], char strInp[])
{
    int i = 0, j = 0, temp = 0;
    while(strInp[i] != '\0')
    {
        temp = 0;
        while(strInp[i] != ' ')
        {
            temp = temp*10 + (strInp[i++] - '0');
        }
        if(strInp[i] == ' ')
        {
            i++;
        }
        K[j++] = temp;
    }
    return j-1;
}



void FIFO(int totFrame, int numOfInp, int pages[])
{
    int hitCount = 0, faultCount = 0;
    int flag = 0;   //for continuing the loop if hit is found 
    int posToUpdate = 0;    //for remembering place in empty frame to fill
    int frames[totFrame];

    for(int i = 0; i < totFrame; i++)
    {
        frames[i] = -1;
    }

    printf("\nFIFO Implementation:\n\n");

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
        for(int j = 0; j < totFrame; j++)   //checks if hit is found or not
        {
            if(frames[j] == pages[i])
            {
                hitCount++;
                printf("|  Hit\t\t");
                for(int k = 0; k < totFrame; k++)
                {
                    printf("|  %d\t", frames[k]);
                }
                printf("|\n");

                // prints design
                printf("|---------------|---------------|");
                for(int k = 0; k < totFrame; k++)
                {
                    printf("-------|");
                }
                printf("\n");

                flag = 1;
                break;
            }
        }
        if(flag == 1)
        {
            continue;
        }

        faultCount++;

        frames[posToUpdate] = pages[i];
        if(posToUpdate == totFrame-1)
        {
            posToUpdate = 0;
        }
        else
        {
            posToUpdate++;
        }

        printf("|  Miss\t\t");
        for(int j = 0; j < totFrame; j++)
        {
            printf("|  %d\t", frames[j]);
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