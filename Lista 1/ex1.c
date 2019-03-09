#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Types definitions for easy coding.
typedef struct Element Element;
typedef struct Queue Queue;

//Struct which represents single element of queue.
struct Element {
    int value;
    Element* prev;
};

//Struct which represents queue with size of it and pinters to head and tail.
struct Queue {
    Element* head;
    Element* tail;
    int size;
};

//Function to malloc size for queue and set start parameters of size, head and tail.
Queue* createQueue () {
    Queue* queue = malloc (sizeof (Queue));
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> size = 0;
    return queue;
}

//Function which checks if queue is empty. If size is 0, queue is empty it returns true), false oth.
bool isEmpty (Queue* queue) {
    if (queue -> size == 0) {
        return true;
    } else {
        return false;
    }
}

//Function called when user is trying to add new element to empty queue.
void initQueue (Queue* queue, int value) {
    Element* element = malloc (sizeof (Element));
    element -> value = value;
    element -> prev = NULL;
    queue -> head = element;
    queue -> tail = element;
    queue -> size = 1;
}

//Function which allows to add new element to queue.
void addToQueue (Queue* queue, int value) {

    //If condition is true function initQueue is called.
    if (isEmpty(queue)) {
        initQueue (queue, value);
        return; 
    }

    //Malloc for new element.
    Element* element = malloc (sizeof (Element));

    //Setting parameters for new element.
    element -> value = value;
    element -> prev = NULL;

    /*Changing pointers in queue (tail -> prev now is pointer to new element, 
    queue -> tail now is pointer to new element). Size is incremented.*/
    queue -> tail -> prev = element;
    queue -> tail = element;
    queue -> size++;
}

//This function allows to take elements from queue.
bool takeFromQueue (Queue* queue) {
    //When queue is empty we can't take any element from it. Function return false.
    if (isEmpty(queue)) {
        return false;
    }

    //Temp variable is used to remember element before head.
    Element* temp = queue -> head -> prev;
    //Free memory which was used by head element.
    free (queue -> head);
    //Chaning pointer to head to previous element. Size of queue is decremented.
    queue -> head = temp;
    queue -> size--;
    //We took element from queue. Function returns true.
    return true;
}

//Fucntion to check if my programs works correctly :--).
void showQueue (Queue* queue) {
    if (isEmpty(queue)) {
        printf("EMPTY!\n");
        return;
    }
    Element* temp;
    temp = queue -> head;
    while (temp != NULL) {
        printf ("%d <- ", temp -> value);
        temp = temp -> prev;
    }
    printf ("NULL\n");
}

int main () {
    Queue* queue = createQueue();
    addToQueue (queue, 16);
    addToQueue (queue, 54);
    addToQueue (queue, 98);
    addToQueue (queue, 17);
    showQueue(queue);
    takeFromQueue (queue);
    showQueue(queue);
    takeFromQueue (queue);
    showQueue(queue);
    takeFromQueue (queue);
    showQueue(queue);
    takeFromQueue (queue);
    showQueue(queue);
    addToQueue(queue, 23);
    showQueue(queue);
    return 0;
}