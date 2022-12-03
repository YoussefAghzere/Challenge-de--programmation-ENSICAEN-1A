

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/point_2D.h"

point* createpoint_2D(int x, int y){
    point* p;
    p = malloc(sizeof(point));
    p->x = x;
    p->y = y;
    return p;
}

bol isEquals(point* a, point *b)
{
    return (a->x ==b->x && a->y ==b->y);
}

point* addPoint(point* a, point* b)
{
 point* c ;
 c = malloc(sizeof(point));
 c->x = a->x +b->x;
 c->y = a->y +b->y;
 return c;
}




