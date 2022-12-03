#include"../include/path.h"



list* findPath(point* begin, map* m){
    list* openlist, *closedlist;
    node * start;
    node * current;
    list* traject;
    int i;
    openlist = createlist();
    closedlist = createlist();
    start = createNode(begin);
    add(openlist, start);
    addClosedList(start, openlist, closedlist);
    add_adjacent_squares(openlist,closedlist,start,m);
    
    while (!isEmpty(openlist)){
        current = bestNode(openlist);
        
        addClosedList(current, openlist, closedlist);
        add_adjacent_squares(openlist,closedlist, current, m);
        if (isFinish(current, m)){
            break;
        }
    }
    
    current = closedlist->head;
    traject = createlist();
    while(current->next){
        current = current->next;
    }
    
    i = 0;
    while (current){
        add(traject, current);
        traject->size++;
        i++;
        current = current->parent;
    }
    traject->size = i;

    
    return traject;

}


path* reconstructpath(list *traject_list){
    path* pa;
    node *tmp;
    int size, i;
    pa = (path *)malloc(sizeof(path));
    pa->size = 0;

    tmp = traject_list->head;
    
    pa->size = traject_list->size ;
    size = pa->size ;
    pa->traject = (point*)malloc(size * sizeof(point));
    i = 0;
    while (tmp && i < size){
            pa->traject[size - i -1].x=tmp->p.x;
            pa->traject[size - i -1].y=tmp->p.y;
            i++;
            tmp = tmp->next;
    }
    return pa;
}

