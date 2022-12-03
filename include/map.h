#ifndef MAP_H
#define MAP_H
#include "../include/point_2D.h"
#include "../include/node.h"


typedef struct _map
{
    int height, width, gas;
    char** tab;

}map;

map* loadMap(FILE* fp);

bol isRoad(node *n, map *m);

bol isSand(node *n, map *m);

bol isWall(node *n, map *m);

bol isFinish(node *n, map *m);


point* neighboreIsFinish(point* p, map * m);


#endif