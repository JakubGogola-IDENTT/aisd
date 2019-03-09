#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Typedefs for easy coding.
typedef struct Element Element;
typedef struct List List;

/*This struct represents element of list.
Value is integer value of element.
Next is pointer to next element, prev is pointer to previous element.
*/
struct Element {
    int value;
    Element* next;
    Element* prev;
};

/* This struct representes list.
Size is size of list.
Head is "virtual" first element of list.
*/
struct List {
    int size;
    Element* head;
};

//This func checks if list is empty.
bool isEmpty (List* list) {
    //Returns true when size of list is 0.
    if (list -> size == 0) {
        return true;
    } else {
        //Oth returns false.
        return false;
    }
}

//Creating new list with starting parameters - size 0 and head NULL.
List* createList () {
    List* list = malloc (sizeof (List));
    list -> head = NULL;
    list -> size = 0;
    return list;
}

//Initializing list when we're trying add element to empty list.
void initList (List* list, int value) {
    Element* element = malloc (sizeof (Element));
    element -> value = value;
    //Next and prev are pointers to self.
    element -> next = element;
    element -> prev = element;
    list -> head = element;
    list -> size = 1;
}

//Adding element to list (before head).
void addToList (List* list, int value) {
    if (isEmpty (list)) {
        //When list is empty func initList(...) is called.
        initList (list, value);
        return;
    }

    //Malloc for new element in list.
    Element* element = malloc (sizeof (Element));
    //Setting value of new element.
    element -> value = value;
    //Pointer prev of new element is old pointer head -> prev.
    element -> prev = list -> head -> prev;
    //Pointer next of new element is head.
    element -> next = list -> head;
    //Pointer next of head -> prev is new element.
    list -> head -> prev -> next = element;
    //Pointer prev of head is new element.
    list -> head -> prev = element;
    //Size of list is incremented.
    list -> size++;
}

/* Taking element from index.
*/
bool takeFromList (List* list, int index) {
    //If index is out of bound, func returns false.
    if (index >= list -> size) {
        return false;
    }

    Element* temp = list -> head;;

    //When index if first element on the list...
    if (index == 0) {
        //Deleting old head element and merging old "tail" to new head (new head is old next element to head).
        temp -> next -> prev = temp -> prev;
        temp -> prev -> next = temp -> next;
        list -> head = temp -> next;
        free (temp);
        list -> size--;
        return true;
    }

    //If index is in "first part" of list we incrementing index from 0 to searched value.
    if (index < list -> size / 2) {
        for (int i = 1; i <= index; i++) {
            temp = temp -> next;
        }
    } else {
        //Oth we decrementing index from bigest value to searched value.
        int start = list -> size - 1;

        for (int i = start; i >= index; i--) {
            temp = temp -> prev;
        }
    }

    //Deleting element and changing pointer on next and prev elements.
    temp -> next -> prev = temp -> prev;
    temp -> prev -> next = temp -> next;
    //Decrementing size of list.
    list -> size--;
    free (temp);
    return true;
}

//Checking if value is on the list.
bool check (List* list, int value) {
    //Starting from head.
    Element* temp = list -> head;
    int end = list -> size;

    for (int i = 0; i < end; i++) {
        //If value is on current element return true.
        if (temp -> value ==  value) {
            return true;
        } else {
            //Oth go to next element.
            temp = temp -> next;
        }
    }
    //If element is not on the list return false.
    return false;
}

//Finding value on index. 
int find (List* list, int index) {
    //When index is out of bound return -1.
    if (index >= list -> size) {
        return -1;
    }

    Element* temp = list -> head;

    //When index is in "first part" of list we incrementing index from 0 to searched value of index.
    if (index < list -> size / 2) {
        for (int i = 1; i <= index; i++) {
            temp = temp -> next;
        }
    } else {
        //Oth we decrementing index from biggest to searched value.
        int start = list -> size - 1;

        for (int i = start; i >= index; i--) {
            temp = temp -> prev;
        }
    }

    //Returning value from searched element.
    return temp -> value;
}

void showList (List* list) {
    if (isEmpty (list)) {
        printf ("EMPTY!\n");
        return;
    }

    Element* temp = list -> head;
    int end = list -> size;

    printf ("(H) ");
    for (int i = 0; i < end; i++) {
        printf ("%d -> ", temp -> value);
        temp = temp -> next;
    }

    printf ("%d (H)\n", list -> head -> value);
}

//Merging two lists.
List* megre (List* list1, List* list2) {
    List* merged = createList ();

    //Adding elements from first list to merged list.
    Element* temp = list1 -> head;
    int end = list1 -> size;

    for (int i = 0; i < end; i++) {
        addToList (merged, temp -> value);
        temp = temp -> next;
    }

    //Adding elements from second list to merged list.
    temp = list2 -> head;
    end = list2 -> size;

    for (int i = 0; i < end; i++) {
        addToList (merged, temp -> value);
        temp = temp -> next;
    }

    //Returning merged list.
    return merged;
}

int main () {
    //tetsing implemented functions.
    List* list1 = createList();
    addToList (list1, 10);
    showList (list1);
    addToList (list1, 11);
    showList (list1);
    addToList (list1, 12);
    showList (list1);
    addToList (list1, 15);
    showList (list1);
    addToList (list1, 17);
    showList (list1);
    addToList (list1, 18);
    showList (list1);
    printf ("%d\n", check(list1, 12));
    printf ("%d\n", find(list1, 1));
    printf ("%d\n", find(list1, 4));
    takeFromList(list1, 0);
    showList (list1);

    List* list2 = createList ();
    addToList (list2, 198);
    addToList (list2, 76);
    addToList (list2, 99);

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