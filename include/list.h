#ifndef LIST_H
#define LIST_H
// verkettete Liste
#include <string>

struct Element {
    int order;
    std::string inhalt;
    Element *next;
};

void insert(Element **head, int order, std::string content);

#endif