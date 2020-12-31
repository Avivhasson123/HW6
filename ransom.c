#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SINGLE_WORD 1


/*linked list definitions- as shown in recitation
 * key=word, num= number of apperances         */
typedef struct single_node single_node_t;
typedef struct map map_t;

struct single_node {

	char *key;
	int num;
	single_node_t *next;
};

struct map {
	single_node_t *head;
	single_node_t *tail;
};


char* readline();
char** split_string(char*);
single_node_t *make_new_node (char *word);
void insert_node (map_t *map, char *word);
single_node_t *find(map_t *map, char *word);
void free_map (map_t *map);
map_t *init_map();

void checkMagazine(int magazine_count,
				   char** magazine,
				   int note_count,
				   char** note) {

	/*initialize map- memory allocation + head&tail resets to NULL*/
	map_t *magazine_map = init_map();
	map_t *note_map = init_map();

	/*we will run on word list, and search if its already in map
	 *if so, increase num of apperances, else add it to map   */
	for (int i=0; i<magazine_count; i++){
		single_node_t *node = find(magazine_map, magazine[i]);
		if (node == NULL) {
			insert_node(magazine_map, magazine[i]);
		} else {
			node->num++;
		}
	}
	for (int i=0; i<note_count; i++){
		single_node_t *node = find(note_map, note[i]);
		if (node == NULL) {
			insert_node(note_map, note[i]);
		} else {
			node->num++;
		}
	}

	/* we will run over note map and check if word appears in magazine
	 * map & num of appearances, and print yes if ransom is possible */
	bool flag = 1;
	single_node_t *tmp = note_map->head;
	while (tmp != NULL){
		single_node_t *node = find(magazine_map, tmp->key);
		if (node == NULL || tmp->num > node->num){
			flag = 0;
		}
		tmp = tmp->next;
	}
	if (flag == 1) {
		printf("Yes");
	} else {
		printf("No");
	}

	free_map(magazine_map);
	free_map(note_map);
	free(magazine_map);
	free(note_map);
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

/*check malloc return value twice*/
single_node_t *make_new_node (char *word) {

	single_node_t *new_node = (single_node_t*)malloc(sizeof(single_node_t));
	if (new_node == NULL){
		printf("");
	}
	new_node->key = (char*)malloc(strlen(word)+1*sizeof(char));
	if(new_node->key == NULL) {
		printf("");
	}
	strcpy(new_node->key,word);
	new_node->num = SINGLE_WORD;
	new_node->next = NULL;
	return new_node;
}

void insert_node (map_t *map, char *word) {

	single_node_t *new_node = make_new_node(word);
	if (map->head == NULL){
	    map->head = new_node;
	} else {
		map->tail->next = new_node;
	}
	map->tail = new_node;
}


single_node_t *find(map_t *map, char *word) {
	single_node_t *tmp = map->head;
	while (tmp != NULL) {
		if (strcmp(tmp->key, word) == 0){
			return tmp;
		} else {
			tmp = tmp->next;
		}
	}
	return NULL;
}

void free_map (map_t *map) {

	single_node_t *tmp;
	while (map->head != NULL){
		tmp = map->head;
		map->head = map->head->next;
		free(tmp->key);
		free(tmp);
	}
}

/*check malloc return value*/
map_t *init_map (){
	map_t *new_map = (map_t*)malloc(sizeof(map_t));
	if (new_map == NULL) {
		printf("");
	}
	new_map->head = NULL;
	new_map->tail = NULL;

	return new_map;
}

