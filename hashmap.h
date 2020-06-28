//
// Created by George on 28-Jun-20.
// COPYRIGHT: https://github.com/petewarden/c_hashmap/blob/master/hashmap.h
//

#ifndef __HASHMAP_H__
#define __HASHMAP_H__

//errors
#define MISSING_MAP - 3 //no such element
#define MAP_FULL -2
#define MAP_MEM_FULL -1 //no more memory to insert items into the map
#define MAP_OK -1 //everything is fine

//allows to put arbitary structs into the hashmap
typedef void *any_t ;

//can take any two any_t arguments and
//return an integer (aka the status code)
typedef int (*PFany)(any_t, any_t) ;

//Internally maintain data structures, clients of
//this package do not need to know how the hashmaps
//are represented they see and manipulated only map_t
typedef any_t map_t;

//return an empty hashmap - by default this will
//actively return null
extern map_t hashmap_new();

//iterate through the F argument which represents the
//item and the data for each element in the hashmap, the
//function must return a map status code, if it returns anything
//other than MAP_OK the traversal is terminated. F must
//not reenter any of the functions or deadlock can occur.
extern int hashmap_iterate(map_t in, PFany f, any_t item);

//add an element from the hashmap
extern int hashmap_put(map_t in, char *key, any_t value);

//return an element
extern int hashmap_get(map_t in, char* key, any_t *arg);

//remove an element
extern int hashmap_remove(map_t in, char* key);

/*
 * Get any element. Return MAP_OK or MAP_MISSING.
 * remove - should the element be removed from the hashmap
 */
extern int hashmap_get_one(map_t in, any_t *arg, int remove);

//free the map from meory
extern void hashmap_free(map_t in);

//returns the current size of the map
extern int hashmap_length(map_t in);

#endif