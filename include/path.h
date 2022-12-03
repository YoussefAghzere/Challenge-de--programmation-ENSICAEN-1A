#ifndef PATH_H
#define PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/point_2D.h"
#include "../include/list.h"
#include "../include/map.h"

typedef struct _path{
    point* traject;
    int size;
}path;


list* findPath(point* begin, map* m);

path* reconstructpath(list *);


#endif
