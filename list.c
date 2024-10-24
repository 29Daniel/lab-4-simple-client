// list/list.c
// 
// Implementation for linked list.
//
// Daniel Webster

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}


void list_free(list_t *l) {
  node_t* curr = l->head;
  node_t* next;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  free(l);
}

void list_print(list_t *l) {
  node_t* curr = l->head;
  while (curr != NULL) {
    printf("%d->", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  buf[0] = '\0';  // Initialize to an empty string
  char tbuf[20];

  node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    strcat(buf, tbuf);
    curr = curr->next;
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  int count = 0;
  node_t* curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count;
}

void list_add_to_back(list_t *l, elem value) {
    node_t* cur_node = (node_t *) malloc(sizeof(node_t));
  cur_node->value = value;
  cur_node->next = NULL;

  /* Insert to back */
  node_t* curr = l->head;
  if (curr == NULL) {
    l->head = cur_node;
    return;
  }
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = cur_node;
}

void list_add_to_front(list_t *l, elem value) {
  node_t* cur_node = (node_t *) malloc(sizeof(node_t));
  cur_node->value = value;
  cur_node->next = l->head;  // Point to current head
  l->head = cur_node;        // Update the head to new node
}


void list_add_at_index(list_t *l, elem value, int index) {
  node_t* cur_node = (node_t *) malloc(sizeof(node_t));
  cur_node->value = value;
  cur_node->next = NULL;

  if (index == 0) {
    cur_node->next = l->head;
    l->head = cur_node;
    return;
  }

  node_t* curr = l->head;
  int i = 0;
  while (i < index - 1) {
    if (curr == NULL) {
      return;
    }
    curr = curr->next;
    i++;
  }
  if (curr == NULL) {
    return;
  }
  cur_node->next = curr->next;
  curr->next = cur_node;
}

elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) {
    return -1;
  }
  if (l->head->next == NULL) {
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    return value;
  }

  node_t* curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  elem value = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return value;
}
elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) {
    return -1;  // or some other sentinel value
  }
  node_t* temp = l->head;
  elem value = temp->value;
  l->head = l->head->next;  // Move head to next node
  free(temp);
  return value;
}

elem list_remove_at_index(list_t *l, int index) {
  if (index == 0) {
    node_t* temp = l->head;
    l->head = l->head->next;
    elem value = temp->value;
    free(temp);
    return value;
  }

  node_t* curr = l->head;
  int i = 0;
  while (i < index - 1) {
    if (curr == NULL) {
      return -1;
    }
    curr = curr->next;
    i++;
  }
  if (curr == NULL || curr->next == NULL) {
    return -1;
  }
  node_t* temp = curr->next;
  elem value = temp->value;
  curr->next = curr->next->next;
  free(temp);
  return value;
}

bool list_is_in(list_t *l, elem value) {
  node_t* curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

elem list_get_elem_at(list_t *l, int index) { 
  if (index < 0) {
    return -1;
  }
  node_t* curr = l->head;
  int i = 0;
  while (i < index) {
    if (curr == NULL) {
      return -1;
    }
    curr = curr->next;
    i++;
  }
  if (curr == NULL) {
    return -1;
  }
  return curr->value;
}

int list_get_index_of(list_t *l, elem value) {
  node_t* curr = l->head;
  int i = 0;
  while (curr != NULL) {
    if (curr->value == value) {
      return i;
    }
    curr = curr->next;
    i++;
  }
  return -1;
}

