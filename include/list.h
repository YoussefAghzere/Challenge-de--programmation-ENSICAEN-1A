#ifndef LIST_H
#define LIST_H

#include "../include/point_2D.h"
#include "../include/map.h"
#include "../include/node.h"




typedef struct _list
{
    node* head;
    int size;
}list;

node* createNode(point* p);

list* createlist ();

bol isEmpty (list* l);

void add(list* l, node* n);

void delete(list *l, node *n);

node* search(list *l, node* n);


node* bestNode(list* l);
void add_adjacent_squares(list* openList, list* closedList, node *n, map *m);
void addClosedList(node *n, list *openList, list *closedList);

#endif
