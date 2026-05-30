#ifndef LIST_H
#define LIST_H
// verkettete Liste
#include <string>
#include <stdio.h>

struct Element {
    int order;
    std::string content;
    Element *next;
};

void insert(Element **head, int order, std::string content);

void printList(Element *head, FILE *output);

void freeList(Element *head);

#endif