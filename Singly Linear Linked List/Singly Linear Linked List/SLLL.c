#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#pragma warning(disable:4996)

#define LMAX 35

typedef struct node {
	int inf;           // value of current element
	struct node* next; // address of next element in list
} Node;

typedef struct list {
	Node* head;      // address of first element in list
} List;

char menu[][LMAX] = { "1. Insertion", "2. Delete", "3. Search", "4. Show",
					  "5. Sort list elements", "0. Exit" };

char submenu1[][LMAX] = { "1. Insert at beginning", "2. Inserare at end",
						  "3. Insert after an element", "0. Return" };

char submenu2[][LMAX] = { "1. Delete first element",
						  "2. Delete last element",
						  "3. Delete of an element", "0. Return" };

/*
*  The function allocates memory for an element of the list and initializes the fields
* inf and next.
* @param value - the whole value with which the inf field will be initialized
* @return      - the address of the memory area where space was allocated for
*                an element
*/
Node* createNode(int value) {
	Node* p;

	p = (Node*)malloc(sizeof(Node));
	p->inf = value;
	p->next = NULL;

	return p;
}

/*
*  The function initializez a list with an empty list (the head and tail fields will have
* value NULL).
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
*/
void initList(List* list) {
	list->head = NULL;
}

/*
*  The function searches for an element with a specified value between the elements of a linear
* singly linked list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linear singly linked list.
* @param value - an int value to be searched in the list
* @return  - address of the first element which has the information equal to the searched value
*            or NULL if there isn't such an element
*/
Node* searchElement(List* list, int value) {
	Node* current;

	current = list->head;
	while ((current != NULL) && (current->inf != value)) {
		current = current->next;
	}

	return current;
}

/*
*  The function returns the address of the last element of a list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linear linked list.
* @return  - address of the last element of a list
*            or NULL if the list is empty
*/
Node* getLastElement(List* list) {
	Node* current;

	current = list->head;
	if (current != NULL) {
		while (current->next != NULL) {
			current = current->next;
		}
	}

	return current;
}

/*
*   Adds an element with a specified value at the beginning of a singly
* linear linked list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linear linked list.
* @param value - an int value to be added to the list
*/
void insertBeforeHead(List* list, int value) {
	Node* p;

	p = createNode(value);      // creates a new element

	p->next = list->head;       // adds the current element to the beginning of the list
	list->head = p;             // first element becomes current element
}

/*
*   Adds an element with a specified value to the end of a singly
* linear linked list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
* @param value - an int value to be added to the list
*/
void insertAfterEnd(List* list, int value) {
	Node* p;
	Node* current;

	p = createNode(value);      // creates a new element

	if (list->head == NULL) {
		list->head = p;
	}
	else {
		current = getLastElement(list);
		current->next = p;
	}
}

/*
*   Inserts an element with a specified value after an element's
* information is equal to another specified value2. If the element with the value2
* inside the linked list doesn't exist, then,
* the insertion is not done.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linear linked list.
* @param value1 - an int value to be added to the list
* @param value2 - int value of the element after which will be added the new
*                 element to the list
* @return  - 1 if the insertion is successful
*            0 if the insertion is not done
*/
int insertAfterElement(List* list, int value1, int value2) {
	Node* p, * current;

	//searches for the element with the information equal to value2
	current = searchElement(list, value2);

	if (current != NULL) {      // if the element exists
		p = createNode(value1);   // creates a new element

		p->next = current->next; // adds the newly created elementa after the current element
		current->next = p;
	}

	return (current != NULL);
}

/*
*  Deletes the element found at the beginning of a singly linear linked list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
*/
void deleteHead(List* list) {
	Node* current;

	if (list->head != NULL) {
		current = list->head;
		list->head = current->next;

		free(current);
	}
}

/*
*  Deletes the element found at the end of a singly linear linked list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
*/
void deleteTail(List* list) {
	Node* current;
	Node* previous;

	if (list->head != NULL) {      // if the list is not empty
		current = list->head;
		if (current->next == NULL) { // if the list has a single element
			list->head = NULL;
		}
		else {
			previous = current;
			current = current->next;
			while (current->next != NULL) {
				previous = current;
				current = current->next;
			}

			previous->next = NULL;
		}

		free(current);
	}
}

/*
*   Deletes from a singly linear linked list the first element of which
* information is equal to a specified value.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
* @param value - value of the element that's about to be deleted from the list
* @return      - 1 if the deletion has been successful
*                0 if the deletion couldn't be done
*/
int deleteElementByValue(List* list, int value) {
	Node* current, * previous;
	int found = 0;

	if (list->head != NULL) {         // if the list is not empty
		current = list->head;
		if (current->inf == value) {    // if the element to be deleted is the first one
			deleteHead(list);             // delete the first element from the list
			found = 1;                    // deletion has been done
		}
		else {
			previous = current;         // previous element of the current one
			current = current->next;    // we pass to the second element
										// we search in the list the element that needs to be deleted
			while ((current != NULL) && (current->inf != value)) {
				previous = current;
				current = current->next;
			}

			if (current != NULL) {      // if the element was found
				found = 1;                // performs deletion
				previous->next = current->next; // skip over current element

				free(current);
			}
		}
	}

	return found;
}

/*
*   Sorts in ascending order by the value of the information field the elements of a singly
* linear linked list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
*/
void sortList(List* list) {
	Node* p, * q;
	int tmp;

	p = list->head;
	// while we haven't reached the end of the list
	while (p) {      // equivalent with: while (p != NULL)
		q = p->next;   // next element of current one
		while (q) {    // while we haven't reached the end of the list
			if (p->inf > q->inf) {
				tmp = p->inf; p->inf = q->inf; q->inf = tmp;
			}

			q = q->next;          // skip to the next element
		}

		p = p->next;            // skip to the next element
	}
}

/*
*  Shows the values of elements of a singly linear linked list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
*/
void printAll(List* list) {
	Node* current = list->head;

	printf("[");
	while (current) {
		printf("%d", current->inf);
		current = current->next;

		if (current != NULL) {
			printf(", ");
		}
	}
	printf("]\n");
}

/*
*  Reads a character from the standard input device.
* @return  - ASCII code of a character read from the keyboard
*/
int input() {
	int ch = 0;

	ch = _getch();

	return ch;
}

/*
*  Shows the strings passed as a function argument.
* @param menuItems - an array of chars
* @param n         - number of chars in the array
*/
void printMenu(char menuItems[][LMAX], int n) {
	int i;

	for (i = 0; i < n; i++) {
		printf("%s\n", menuItems[i]);
	}
	printf("\n");
}

/*
*  Shows the elements of submenu 1, reads user input and,
* accordingly, performs insertion of an element from a list.
* @param list - pointer to an element of type List: this has a field, head,
*               that keeps the address of the first element of a linked list.
*/
void dosubmenu1(List* list) {
	int ch;
	int value, value2;

	printMenu(submenu1, sizeof(submenu1) / sizeof(submenu1[0]));
	while ((ch = input()) != '0') {
		switch (ch) {
		case '1': printf("Input value of element to be inserted: ");
			scanf("%d", &value);
			insertBeforeHead(list, value);
			break;
		case '2': printf("Input value of element to be inserted: ");
			scanf("%d", &value);
			insertAfterEnd(list, value);
			break;
		case '3': printf("Input value of element to be inserted: ");
			scanf("%d", &value);
			printf("Input value of element after which it inserts: ");
			scanf("%d", &value2);

			if (insertAfterElement(list, value, value2) == 0) {
				printf("Element with value %d was not found!\n", value2);
			}
			break;
		default: printf("Unknown command!\n");
		}

		printMenu(submenu1, sizeof(submenu1) / sizeof(submenu1[0]));
	}
}

/*
*  Shows elements of submenu 2, read user input and,
* accordingly, performs deletion of an element from a list.
* @param list - pointer catre un element de tip List: acesta are un camp, head,
*               ce pastreaza adresa primului element al unei liste liniare.
*/
void dosubmenu2(List* list) {
	int ch;
	int value;

	printMenu(submenu2, sizeof(submenu2) / sizeof(submenu2[0]));
	while ((ch = input()) != '0') {
		switch (ch) {
		case '1': printf("An attempt is being made to delete the first element from the list!\n");
			deleteHead(list);
			break;
		case '2': printf("An attempt is being made to delete the last element from the list!\n");
			deleteTail(list);
			break;
		case '3': printf("Input value of element to be deleted: ");
			scanf("%d", &value);

			if (deleteElementByValue(list, value) == 0) {
				printf("Element with value %d was not found!\n", value);
			}
			break;
		default: printf("Unknown command!\n");
		}

		printMenu(submenu2, sizeof(submenu2) / sizeof(submenu2[0]));
	}
}

int main() {
	List list;
	Node* p;
	int ch;
	int value;

	initList(&list);

	printMenu(menu, sizeof(menu) / sizeof(menu[0]));
	while ((ch = input()) != '0') {
		switch (ch) {
		case '1': dosubmenu1(&list);
			break;
		case '2': dosubmenu2(&list);
			break;
		case '3': printf("Input value of element to be searched: ");
			scanf("%d", &value);

			p = searchElement(&list, value);
			if (p == NULL) {
				printf("Element with value %d was not found!\n", value);
			}
			else {
				printf("Element with value %d was found!\n", value);
			}
			break;
		case '4': printf("Show list elements:\n");
			printAll(&list);
			break;
		case '5': printf("Sorting list elements after value.\n");
			sortList(&list);
			break;
		default:  printf("Unknown command!\n");
		}

		printMenu(menu, sizeof(menu) / sizeof(menu[0]));
	}

	return 0;
}
