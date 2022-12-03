#ifndef POINT_H
#define POINT_H

typedef enum {FALSE, TRUE} bol;
 
typedef struct _point
{
    int x, y;
}point;


bol isEquals(point* a, point* b);

point* createpoint_2D(int x, int y);

point* addPoint(point* a, point* b);



#endif