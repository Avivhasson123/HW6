//functions.h
#ifndef functions_h
#define functions_h
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*linked list definitions- as shown in recitation
 * key=word, num= number of apperances         */
typedef struct single_node single_node;
typedef struct map map;

struct single_node {

	char *key;
	int num;
	single_node *next;
};

struct map {
	single_node *head;
	single_node *tail;
};

/*function declarations*/
single_node *make_new_node (char *word);
void insert_node (map *map, char *word);
single_node *find(map *map, char *word);
void free_map (map *map);
map *init_map ();

#endif

