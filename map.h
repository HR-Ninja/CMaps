#ifndef MAP_H
#define MAP_H

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MULTIPLIER 37

typedef struct {
    char* key;
    void* value;
} HashMapEntry;

typedef struct {
    HashMapEntry* entries;
    uint32_t element_size;
    uint32_t size;
    uint32_t capacity;
} HashMap;

extern void init_hashmap(HashMap* map, const uint32_t element_size);
extern void push_hashmap(HashMap* map, const char* key, const void* data);
extern void* get_hashmap(HashMap* map, const char* key);
extern void remove_hashmap(HashMap* map, const char* key);
extern void grow_hashmap(HashMap* map);

// hashing function
static inline uint32_t hash(const char* str) {
    uint32_t h = 0;

    for (unsigned char* p = (unsigned char*)str; *p != '\0'; p++) {
        h = MULTIPLIER * h + *p;
    }
    
    return h;
}

static inline void free_hashmap(HashMap* map) {
    for (uint32_t i = 0; i < map->capacity; i++) {
        HashMapEntry* entry = &map->entries[i];
        if (entry->key != NULL) {
            free(entry->key);
            free(entry->value);
        }
    }
    free(map->entries);
}

#endif 