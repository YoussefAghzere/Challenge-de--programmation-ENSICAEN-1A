#ifndef NODE_H
#define NODE_H


#include "../include/point_2D.h"

typedef struct _node
{
    float cost;
    struct _node* parent;
    struct _node* next;

    point p;
}node;
#endif