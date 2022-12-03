#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/path.h"
#include "../include/list.h"


#define MAX_LINE_LENGTH 50
#define BOOSTS_AT_START 5

int gasConsumption(int accX, int accY, int speedX, int speedY, int inSand)
{
  int gas = accX * accX + accY * accY;
  gas += (int)(sqrt(speedX * speedX + speedY * speedY) * 3.0 / 2.0);
  if (inSand) {
    gas += 1;
  }
  return -gas;
}


int velocityX(path *pa, int step, point* p, map * m){ 
    if (neighboreIsFinish(p, m)){
        return neighboreIsFinish(p, m)->x- p->x;
      }
    return pa->traject[step].x - pa->traject[step-1].x;
}


int velocityY(path *pa, int step, point* p, map * m){ 
    if (neighboreIsFinish(p, m)){
        return neighboreIsFinish(p, m)->y- p->y;
      }
    return pa->traject[step].y - pa->traject[step-1].y;
}


void optimiseTraject(path* pa, map* m){
  int i;
  for (i =0; i<pa->size-2; i++){
            if (pa->traject[i].x == pa->traject[i+2].x && pa->traject[i+1].x != pa->traject[i].x){
              if (m->tab[pa->traject[i+1].y][pa->traject[i].x ] != '.') {pa->traject[i+1].x = pa->traject[i].x;}
            }

            if (pa->traject[i].y == pa->traject[i+2].y && pa->traject[i+1].y != pa->traject[i].y){
              if (m->tab[pa->traject[i].y][pa->traject[i+1].x ] != '.')
              pa->traject[i+1].y = pa->traject[i].y;
            }

  }
}
  

bol isBoostableX(path *pa, int index, int toPredict){
  int i;
  for(i =index-1; i < index + toPredict; i++){
    if(i != index){
      if(!(pa->traject[i].y == pa->traject[index].y)){
       return 0;
      }
    }
  }
  return 1;
}


bol isBoostableY(path *pa, int index, int toPredict){
  int i;
  for(i =index-1; i < index + toPredict; i++){
    if(i != index){
      if(!(pa->traject[i].x == pa->traject[index].x)){
        return 0;
      }
    }
  }
  return 1;
}


bol isBoostable(path *pa, int index, int toPredict){
  return (isBoostableX(pa, index, toPredict) || isBoostableY(pa, index, toPredict));
}





    
int main()
{
  int gasLevel;
  point *begin;
  map* m;
  list* l;
  path *pa;
  point* current;
  int round = 0;
  int accelerationX = 0, accelerationY = 0;
  int speedX = 0, speedY = 0;
  int newSpeedX = 0, newSpeedY = 0;
  char action[100];
  path* final_path;
  int oldX=0, oldY=0;
  int step = round;
  float mapAndPathCharacteristic;
  int counterForPathRegenerating ;
  counterForPathRegenerating = 0;
  m =loadMap(stdin);
  gasLevel = m->gas;



  while (!feof(stdin)) {
    int myX, myY, secondX, secondY, thirdX, thirdY;
    round++;
    step++;
    fprintf(stderr, "=== ROUND %d === step : %d\n", round, step);
    fflush(stderr);
    fflush(stdin);
    fscanf(stdin, "%d %d %d %d %d %d", &myX, &myY, &secondX, &secondY, &thirdX, &thirdY);
    m->tab[secondY][secondX] = '.';
    m->tab[thirdY][thirdX] = '.';
    if (round ==1 || counterForPathRegenerating > 2 ){
      speedX =0;
      speedY =0;
      m->tab[secondY][secondX] = '.';
      m->tab[thirdY][thirdX] = '.';
      step =1;
      begin = createpoint_2D(myX, myY);
      oldX = myX;
      oldY = myY;
      l = findPath(begin, m);
      pa = reconstructpath(l);
      optimiseTraject(pa, m);
      final_path = pa;
      fprintf(stderr, "\n");
      if (!isEquals(begin, &(pa->traject[0]))){
          pa->traject[0].x = begin->x;
          pa->traject[0].y = begin->y;

      }
      mapAndPathCharacteristic = 5*(float)((float)m->gas / (float)final_path->size)*3;
    }

    

    if(round >=3){
      if(!(m->tab[final_path->traject[round -1].y][final_path->traject[round -1].x] == '~')){

        if((float)((float)gasLevel / (float)(final_path->size - round-1)) >= mapAndPathCharacteristic ){
                   
          if(isBoostable(final_path, round-1, 6)){
            int i;
            for(i = round; i < (final_path->size -1); i++){
              final_path->traject[i] = final_path->traject[i+1];
            }
            final_path->traject[final_path->size -1].x = 0;
            final_path->traject[final_path->size -1].y = 0;
            final_path->size--;
          
          }
        }
      }
    }
    if (oldX == myX && oldY ==myY && round != 1 && round!=2 && step != 1){
      speedX = 0;
      speedY = 0;
      newSpeedX = 0;
      newSpeedY = 0;
      (step)--;
      (counterForPathRegenerating)++;
    }
    else{
       counterForPathRegenerating = 0;
    }
    current = createpoint_2D(myX, myY);
    newSpeedX = velocityX(final_path, step, current, m);
    newSpeedY = velocityY(final_path, step, current, m);
    accelerationX = newSpeedX - speedX;
    accelerationY = newSpeedY - speedY;
    fflush(stderr);
    gasLevel += gasConsumption(accelerationX, accelerationY, speedX, speedY, 0);    
    sprintf(action, "%d %d", accelerationX, accelerationY);
    fprintf(stdout, "%s", action);
    fflush(stdout);                           
    speedX = newSpeedX;
    speedY = newSpeedY;
    oldX =myX;
    oldY =myY;
    fflush(stderr);
  }

  return EXIT_SUCCESS;
}
