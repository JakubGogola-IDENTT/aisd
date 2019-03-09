#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Typedefs for structs to make coding easier. 
typedef struct Element Element;
typedef struct List List;

//This struct represents elment of list.
struct Element {
    int value;
    Element* next;
};

//This struct represent list. It holds pointers to head and tail of list and size of it.
struct List {
    Element* head;
    Element* tail;
    int size;
};

//This function checks if list is empty. Returns true if it' empty, false oth.
bool isEmpty (List* list) {
    if (list -> size == 0) {
        return true;
    } else {
        return false;
    }
}

//Creating new list with starting parameters - head and tail are NULL, size is 0.
List* createList () {
    List* list = malloc (sizeof (List));
    list -> head = NULL;
    list -> tail = NULL;
    list -> size = 0;
    return list;
}

/* Initializing list when user tries to add new element to empty list.
Pointer to head and tail are conttected with the same element.
Size is 1.
*/
void initList (List* list, int value) {
    Element* element = malloc (sizeof (Element));
    element -> value = value;
    element -> next = NULL;
    list -> head = element;
    list -> tail = element;
    list -> size = 1;
}

/*Adding new element to list. 
New element is added to head of the list.
*/
void addToList (List* list, int value) {
    //When list is empty function initList is called.
    if (isEmpty (list)) {
        initList (list, value);
        return;
    }

    //Malloc for new element.
    Element* element = malloc (sizeof (Element));
    //Setting parameters to new element. 
    element -> value = value;
    //New element is first, so the pointer to next element is NULL.
    element -> next = NULL;
    //Pointer next of old head now is connected to new element.
    list -> head -> next = element;
    //New element is new head.
    list -> head = element;
    //Size of list is incremented.
    list -> size++;
}

/* Taking element from list.
Returns true if element was sucessfully taken (index exists), false oth.
*/
bool takeFromList (List* list, int index) {
    //When index is out of bound funtcion returns false.
    if (index >= list -> size) {
        return false;
    }

    Element* temp = list -> tail;
    Element* prev = NULL;

    if (index == 0) {
        //If last element from list is taken, new tail is next element.
        list -> tail = list -> tail -> next;
    } else {
        //Oth we're searching index in list.
        for (int i = 1; i <= index; i++) {
            //Var prev remembers pointer to element with index - 1.
            prev = temp;
            //Temp finally is element with index.
            temp = temp -> next;
        }
        //Previous element (index - 1) has pointer next to elment next to current element (index).
        prev -> next = temp -> next;
    }
    //Free memory for element to delete.
    free (temp);
    //Decrementing size of list.
    list -> size--;
    return true;
}

//Checking if value is on the list.
bool check (List* list, int value) {
    //This var will be a pointer to every next element of list.
    Element* temp = list -> tail;
    while (temp != NULL) {
        if (temp -> value == value) {
            //Func returns true if value from element equals searched value.
            return true;
        } else {
            //Oth we go to next element.
            temp = temp -> next;
        }
    }
    //When vaule is not on the list, func returns false.
    return false;
}

//Finding value from index.
int find (List* list, int index) {

    //If index doesn't exist, func returns -1.
    if (index >= list -> size) {
        return -1;
    }
    
    Element* temp = list -> tail;
    for (int i = 1; i <= index; i++) {
        //We go to element with searched index.
        temp = temp -> next;
    }
    //Returning value from index.
    return temp -> value;
}

void showList (List* list) {
    if (isEmpty (list)) {
        printf ("EMPTY!\n");
        return;
    }
    
    Element* temp = list -> tail;
    while (temp != NULL) {
        printf ("%d -> ", temp -> value);
        temp = temp -> next;
    }
    printf ("NULL\n");
}

//Merging two lists.
List* megre (List* list1, List* list2) {
    List* merged = createList();
    Element* temp = list1 -> tail;

    //Adding elements from first list to new lists.
    while (temp != NULL) {
        addToList (merged, temp -> value);
        temp = temp -> next;
    }

    temp = list2 -> tail;

    //Adding elements from second list to new lists.
    while (temp != NULL) {
        addToList (merged, temp -> value);
        temp = temp -> next;
    }

    return merged;
}

int main () {
    //Testing implemented functions.
    List* list1 = createList();
    addToList (list1, 10);
    showList (list1);
    addToList (list1, 11);
    showList (list1);
    addToList (list1, 12);
    showList (list1);
    printf ("%d\n", check(list1, 12));
    printf ("%d\n", find(list1, 0));
    takeFromList(list1, 0);
    showList (list1);

    List* list2 = createList();
    addToList (list2, 16);
    addToList (list2, 18);
    addToList (list2, 87);

    List* merged = megre (list1, list2);
    showList (merged);

    //------------------------ Time measuring -------------------------------------

    int value;
    int index;
    double executionTime;
    clock_t startTime;
    clock_t endTime;

    //Creating list which will be put to time tests.
    List* test = createList ();

    //Adding random values to the list.
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        value = rand() % 2137;
        addToList (test, value);
    }

    //Testing the same element everytime with random index.
    index = rand() % test -> size - 1;
    
    //Number of tests.
    int n = 10000;

    //Starting time measuring.
    startTime = clock();
    for (int i = 0; i < n; i++) {
        //Testing the same element n times.
        find (test, index);
    }
    endTime = clock();

    //Computing execution time for one find(...) call.
    executionTime = (double) (endTime - startTime) / (CLOCKS_PER_SEC * n);
    printf ("Checking element %d everytime lasts %f15.\n", index, executionTime);


    //Testing random elements.

    //Preparing array with random indexes.
    int* randomIndex = malloc (n * sizeof (int));

    for (int i = 0; i < n; i++) {
        randomIndex[i] = rand() % (test -> size);
    }

    //Starting measuring time.
    startTime = clock();
    for (int i = 0; i < n; i++) {
        //Testing n random elements.
        find (test, randomIndex[i]);
    }
    endTime = clock();

    //Computing execution time for one find(...) call.
    executionTime = (double) (endTime - startTime) / (CLOCKS_PER_SEC * n);
    printf ("Checking random elements lasts %f15.\n", executionTime);

    free (randomIndex);
    return 0;
}


