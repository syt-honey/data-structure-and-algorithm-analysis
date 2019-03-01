/**
功能：使用双链表实现LRU算法（不带哨兵）
前提：
1. size为某一指定大小
原理：
1. 存放某一数据，链表中有，则该数据提到第一个结点处，其余结点往后copy
2. 链表中没有，将新结点放至第一个结点，删除尾节点
*/
#include <stdio.h>

typedef struct DlistNode {
  struct DlistNode *pre;
  struct DlistNode *next;
  int data;
}stDlistNode;  // 定义双链表中的每一个结点

typedef struct Dlisthead {
  stDlistNode *head;
  stDlistNode *tail;
  int size;
}stDlist;  //定义双链表

// 初始化双链表
void dlist_init(stDlist *dlist) {
  dlist->size = 0;
  dlist->head = NULL;
  dlist->tail = NULL;
  return;
}

// 销毁双链表(释放结点内存)
void dlist_destory(stDlist *dlist){
  stDlistNode *p = NULL;
  while(dlist->size != 0 ) {
    p = dlist->head;
    dlist->head = dlist->head->next;
    free(p);
    --dlist->size;
  }
  memset(dlist, 0, sizeof(stDlist));
  return;
}

//从头部插入结点
int dlist_insert_head(stDlist *dlist, stDlistNode *p, int data) {
  if(p == NULL) {
    p = (stDlistNode *)malloc(sizeof(stDlistNode));
    if(p == NULL) {
      return -1;
    }
  }

  p->data = data;
  p->pre = NULL;
  p->next = NULL;

  if(dlist->size == 0) {
    dlist->head = p;
    dlist->tail = p;
  } else {
    p->next = dlist->head;
    dlist->head->pre = p;
    dlist->head = p;
  }
  dlist->size++;
  return 0;
}

// 从尾部移除结点
stDlistNode* dlist_remove_tail(stDlist *dlist) {
  stDlistNode *p = NULL;
  if(dlist->size == 0){
    return NULL;
  }
  p = dlist->tail;
  if(dlist->size == 1) {
    dlist->head = NULL;
    dlist->tail = NULL;
  } else {
    dlist->tail = dlist->tail->pre;
    dlist->tail->next = NULL;
  }
  dlist->size--;
  return p;
}

// 从中间某个地方删除结点
void dlist_remove_node(stDlist *dlist, stDlistNode *p) {
  if((dlist->size == 0) || (p == NULL)) {
    return ;
  }
  if(p == dlist->head) {
    dlist->head = dlist->head->next;
  }else if(p == dlist->tail) {
    dlist->tail = dlist->tail->pre;
    dlist->tail->next = NULL;
  }else {
    p->pre->next = p->next;
    p->next->pre = p->pre;
    p->pre = NULL;
    p->next = NULL;
  }
  dlist->size--;
  return;
}

// 从链表中查找data
stDlistNode* dlist_find(stDlist *dlist, int data) {
  stDlistNode *p = dlist->head;
  while(p != NULL) {
    if(p->data == data) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}

// 输出链表
void dlist_print(stDlist *dlist) {
  if(dlist->size == 0) {
    return ;
  }
  stDlistNode *p = NULL;
  p = dlist->head;
  printf("\n");
  while(p != NULL) {
    printf("%d ", p->data);
    p = p->next;
  }
  return;
}

// 实现 LRU
void lru_list(stDlist *dlist, int data, int size) {
  stDlistNode *p = NULL;
  p = dlist_find(dlist, data);
  if(p != NULL) {
    dlist_remove_node(dlist, p);
  } else if(dlist->size >= size){  
    p = dlist_remove_tail(dlist);
  }
  dlist_insert_head(dlist, p, data);

  return;
}

int main() {
  stDlist dlist = {0};
  stDlistNode *p = NULL;

  dlist_init(&dlist);

  printf("*****insert 1, 2, 3, 4 *****");

  dlist_insert_head(&dlist, NULL, 1);
  dlist_insert_head(&dlist, NULL, 2);
  dlist_insert_head(&dlist, NULL, 3);
  dlist_insert_head(&dlist, NULL, 4);
  
  dlist_print(&dlist);
  
  lru_list(&dlist, 5, 5);
  
  dlist_print(&dlist);
  
  lru_list(&dlist, 6, 5);
  
  dlist_print(&dlist);
  
  lru_list(&dlist, 4, 5);
  
  dlist_print(&dlist);

}





