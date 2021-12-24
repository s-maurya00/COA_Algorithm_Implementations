#include <stdio.h>
#include <string.h>
#include <malloc.h>


struct queue
{
    struct queue *link;
    int pageData;
};

struct queue *front = NULL, *rear = NULL;   // Initialization of front and rear of the queue to null

void display(struct queue *);   // display for queue
void addq(struct queue **, int);
void deq(struct queue **);

// Create a queue to store last entered page

void main()
{
    struct queue *q = NULL;

    addq(&q, 10);
    addq(&q, 20);
    addq(&q, 30);
    addq(&q, 40);
    addq(&q, 50);

    deq(&q);
    display(q);

    deq(&q);
    display(q);

    deq(&q);
    display(q);

    deq(&q);
    display(q);

    deq(&q);
    display(q);
}



void addq(struct queue **q, int num)//maybe done
{
    struct queue *temp;
    temp = (struct queue *)malloc(sizeof(struct queue));

    if(temp == NULL)
    {
        printf("\nMemory is Full!!!");
        return;
    }
    
    temp->pageData = num;
    temp->link = NULL;

    if(front == NULL)
    {
        front = rear = temp;
        front->link = NULL;
        rear->link = front;
    }
    else
    {
        temp->link = rear;
        rear = temp;
    }
}




void deq(struct queue **q)
{
    struct queue *temp; // For storing and then freeing the dequeued Element's node

    if(front == NULL)
    {
        printf("The Queue is already empty!!!");
        return;
    }

    if(front == rear) // If the element is the last element in the queue
    {
        temp = front;
        front = rear = NULL;
        free(temp); 
        return;
    }

    temp = front;
    front = front->link;
    free(temp);
}



void display(struct queue *q)
{
    struct queue *temp;
    
    if(front == NULL)
    {
        printf("The Queue is empty");
    }
    else
    {
        temp = front;
        while(temp != NULL)
        {
            printf("%d ", temp->pageData);
            temp = temp->link;
        }
    }
}