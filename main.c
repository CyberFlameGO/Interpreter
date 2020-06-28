#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

void test_hashmap();

#define MAX_KEY_LENGTH 256
#define PREFIX "key"
#define COUNT 1024 * 1024

//test data for the hashmap
typedef struct _test_data_struct_s {
    char key_string[MAX_KEY_LENGTH];
    int number;

} test_data;
int main(void) {
    return 0;
}

void test_hashmap() {
    int index, error;
    map_t  test_map;
    char key_string[MAX_KEY_LENGTH];
    test_data* value;
    test_map = hashmap_new();

    for(index = 0; index < COUNT; index++) {
        value = malloc(sizeof(test_data));
        snprintf(value->key_string, MAX_KEY_LENGTH, "%s%d", PREFIX, index);
        value->number = index;
        error = hashmap_put(test_map, value->key_string, value);
    }

    for(index = 0; index < COUNT; index++) {
        snprintf(key_string, MAX_KEY_LENGTH, "%s%d", PREFIX, index);
        error = hashmap_get(test_map, key_string, (void**)(&value));
    }

    error = hashmap_get(test_map, key_string, (void**)(&value));

    for(index = 0; index < COUNT; index += 1) {
        snprintf(key_string, MAX_KEY_LENGTH, "%s%d", PREFIX, index);
        error = hashmap_get(test_map, key_string, (void**)(&value));
        error = hashmap_remove(test_map, key_string);
        free(value);
    }
    hashmap_free(test_map);
}