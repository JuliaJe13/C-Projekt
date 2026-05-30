#include "list.h"
#include <stdio.h>

void insert(Element **head, int order, std::string content) {
    Element *newElement = new Element;
    newElement->order = order;
    newElement->content = content;
    newElement->next = NULL;

    if (*head == NULL) {
        *head= newElement;
    } else {
        Element *current = *head;
        while (current->next != NULL && current->next->order <= order) {
            current = current->next;
        }
        newElement->next = current->next;
        current->next = newElement;
    }
}

void printList(Element *head) {
        Element *current = head;
        while (current != NULL) {
            printf("%s\n", current->content.c_str());
            current = current->next;
        }
    }

void freeList(Element *head) {
    Element *current = head;    
    while (current != NULL) {
        Element *next = current->next;
        delete current;
        current = next;
    }
}