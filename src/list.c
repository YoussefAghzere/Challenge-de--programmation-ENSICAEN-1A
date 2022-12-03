#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"



node* createNode(point* p){
    node* n; 
    n = calloc( 1, sizeof(node));
    n->p = *p;
    n->parent = NULL;
    n->next = NULL;
    n->cost = 0;
    return n;
}

list* createlist(){
    list* l;
    l = calloc(1, sizeof(list));
    l->head = NULL;
    l->size = 0;
    return l;
}

bol isEmpty (list* l){
    if (!l->size) return TRUE;
    return FALSE;
}

void add(list *l, node *n){
    node *tmp;
    if(!l->head){
        l->head = n;
        l->head->next = NULL;
    }
    else{
        tmp = l->head;
        while(tmp->next){
            tmp = tmp->next;
        }
        tmp->next = n;
        tmp->next->next = NULL;
    }
    l->size++;
}


node* search(list *l, node* n){
    node* m;
    if (!l) return NULL;
    m = l->head;
    while(m){
        if(isEquals(&(m->p),&(n->p))) return n;
        m = m->next;
    }
    return NULL;
}

void delete(list *l, node *n){
    node *cell;
    node *tmp, *tmp_previous;
    if(isEmpty(l)){
        printf("list is empty ! Can't delete node \n");
    }
    else{
        if(l->head == n){
            
            cell = l->head;
            l->head = cell->next;
            free(cell);
        }
        else{
            
            tmp = l->head;
            while((tmp != n) && tmp->next){
                tmp_previous = tmp;
                tmp = tmp->next;
            }
            
            tmp_previous->next = tmp->next;
        }
        l->size--;
    }
}


void add_adjacent_squares(list* openList, list* closedList, node *n, map *m){
    int i, j;
    int cost;
    node *curr;
    point *p;

    for(i = -1; i <= 1; i++){
        if((n->p.x)+i < 0 || (n->p.x)+i >= m->width){
            continue;
        }
        for(j = -1; j <= 1; j++){
            if((n->p.y)+j < 0 || (n->p.y)+j >= m->height){
                continue;
            }

            if( !i && !j){
                continue;
            }

            if (isSand(n, m)){
                    if (abs(i) == abs(j)){
                        continue;
                    }
            }
            
            p = createpoint_2D(n->p.x+i, n->p.y+j);
            curr = createNode(p);
            curr->parent = n;
            cost = n->cost;
            
            if(isWall(curr, m)){
                continue;
            }



            if(!search(closedList, curr)){
                
                if (isSand(curr, m)){
                    
                     curr->cost = cost  +100;
                }
                
                
                
                else if(abs(i) == abs(j)){
		           
                     curr->cost = cost   +100;
                }

                

                else {    
                    curr->cost = cost ;
                }
                if(search(openList, curr)){
                    if(curr->cost < search(openList, curr)->cost){
                        search(openList, curr)->cost = curr->cost;
                    }
                }
                else{
                    add(openList, curr);
                }
            }
        }
    }
}


node* bestNode(list* l){
    node *tmp, *best;
    tmp = l->head, best = tmp;
    while(tmp){
        if (tmp->cost <= best->cost) {
            best = tmp;
        }
        tmp = tmp->next;
    }
    return best;
}


void addClosedList(node *n, list *openList, list *closedList){
    if(search(openList, n)){
        delete(openList, n);
        add(closedList, n);
    }
    

}
