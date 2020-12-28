#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define SINGLE_WORD 1

single_node *make_new_node (char *word) {   

	single_node *new_node = (single_node*)malloc(sizeof(single_node));
	if (new_node == NULL){
		return NULL;
	}
	new_node->key = (char*)malloc(strlen(word)+1*sizeof(char));
	strcpy(new_node->key,word);
	new_node->num = SINGLE_WORD;
	new_node->next = NULL;
	return new_node;
}

void insert_node (map *map, char *word) {

	single_node *new_node = make_new_node(word);
	if (map->head == NULL){
	    map->head = new_node;
	} else {
		map->tail->next = new_node;
	}
	map->tail = new_node;
}


single_node *find(map *map, char *word) {
	single_node *tmp = map->head;
	while (tmp != NULL) {
		if (strcmp(tmp->key, word) == 0){
			return tmp;
		} else {
			tmp = tmp->next;
		}
	}
	return NULL;
}

void free_map (map *map) {

	single_node *tmp;
	while (map->head != NULL){
		tmp = map->head;
		map->head = map->head->next;
		free(tmp->key);
		free(tmp);
	}
}

map *init_map (){
	map *new_map = (map*)malloc(sizeof(map));
	new_map->head = NULL;
	new_map->tail = NULL;

	return new_map;
}
