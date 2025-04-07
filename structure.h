#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>	// I/O control 
#include <stdlib.h>	// Memory allocation and macros
#include <stdbool.h>	// Implementing bool type
#include <string.h>	// String operations

// Singular data type definition
typedef const char* string;
typedef struct Elmt* elmtAddress;

typedef struct List {
	elmtAddress front;
} List;

// Node and list structure
typedef struct Elmt {
	string name;
	List* pCitizen;		// Optional variable for city nodes to point to citizen lists 
	elmtAddress next;
} Elmt;

/* Constructors */
elmtAddress allocate(string name);
void createList(List* list);

/* Destructors */
void deallocate(elmtAddress node);
void deleteList(List* list);

/* Verification */
bool listEmpty(List list);

/* Getter */
int getTotalElmt(List list);

/* List processing*/
// Printing
void printElmt(elmtAddress node);
void printList(List list);

// Search
elmtAddress searchList(List list, string query);

/* List I/O */
// Insertions
void insFront(List* list, elmtAddress node);
void insRear(List* list, elmtAddress node);
void insManual(List* list, elmtAddress node, unsigned short position);	

// Deletions
void delFront(List* list);
void delRear(List* list);
void delManual(List* list, unsigned short position);	

#endif
