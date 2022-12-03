#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/map.h"

#define MAX_LINE_LENGTH 1024
#define BOOSTS_AT_START 5

map* loadMap(FILE* fp)
{ 
  map* m = malloc(sizeof(map));
  int i;
  fscanf(fp,"%d %d %d",&(m->width),&(m->height),&(m->gas));

  m->tab=(char**)malloc((m->height)*sizeof(char*));
  for(i=0;i<m->height;i++)
    { 
      m->tab[i]=(char*)malloc((m->width)*sizeof(char));
      fscanf(fp,"%s",m->tab[i]);

      fflush(fp);
    }
  fflush(fp);
  return m;
}



bol isRoad(node *n, map *m){
    return m->tab[n->p.y][n->p.x] == '#';
}

bol isSand(node *n, map *m){
    return m->tab[n->p.y][n->p.x] == '~';
}

bol isWall(node *n, map *m){
    return (m->tab[n->p.y][n->p.x] == '.');
}

bol isFinish(node *n, map *m){
    return m->tab[n->p.y][n->p.x] == '=';
}







point* neighboreIsFinish(point* p, map * m){
    int i, j;
      for(i = -2; i <= 2; i++){
        if((p->x)+i < 0 || (p->x)+i >= m->width){
            continue;
        }
        for(j = -2; j <= 2; j++){
            if((p->y)+j < 0 || (p->y)+j >= m->height){
                continue;
            }

            if( !i && !j){
                continue;
            }
            if (m->tab[(p->y)+j][(p->x)+i] == '='){
              point *finish = malloc(sizeof(point));
              finish->x = (p->x)+i;
              finish->y = (p->y)+j;
              return finish;

            }
        }
      } return NULL;


}



