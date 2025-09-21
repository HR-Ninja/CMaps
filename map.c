#include "map.h"

void init_hashmap(HashMap* map, const uint32_t element_size) {
    map->size = 0;
    map->element_size = element_size;
    map->capacity = 100;

    map->entries = (HashMapEntry*)calloc(map->capacity, sizeof(HashMapEntry));
    if (map->entries == NULL) {
        printf("Failed to allocate memory for HashMap.\n");
        exit(EXIT_FAILURE);
    }
}

void push_hashmap(HashMap* map, const char* key, const void* data) {

    if(map->size == map->capacity / 2) {
        grow_hashmap(map);
    }

    uint32_t index = hash(key) % map->capacity;

    for (uint32_t i = 0; i < map->capacity; i++) {
        uint32_t try = (index + i) % map->capacity;
        HashMapEntry* entry = &map->entries[try];

        if (entry->key == NULL) {
            entry->key = strdup(key);
            entry->value = malloc(map->element_size);
            memcpy(entry->value, data, map->element_size);
            map->size++;
            return;
        }

        if (strcmp(entry->key, key) == 0) {
            memcpy(entry->value, data, map->element_size);
            return;
        }
    }
}

void* get_hashmap(HashMap* map, const char* key) {
    uint32_t index = hash(key) % map->capacity;

    for (uint32_t i = 0; i < map->capacity; i++) {
        uint32_t try = (index + i) % map->capacity;
        HashMapEntry* entry = &map->entries[try];

        if (entry->key == NULL) {
            return NULL;
        }

        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
    }

    return NULL; 
}

void remove_hashmap(HashMap* map, const char* key) {
    uint32_t index = hash(key) % map->capacity;

    for (uint32_t i = 0; i < map->capacity; i++) {
        uint32_t try = (index + i) % map->capacity;
        HashMapEntry* entry = &map->entries[try];

        if (entry->key == NULL) {
            return;
        }

        if (strcmp(entry->key, key) == 0) {
            entry->key = NULL;
            memset(entry->value, 0, map->element_size);
        }

    }
}

// grow and re-hash old entries
void grow_hashmap(HashMap* map) {
    uint32_t old_capicity = map->capacity;
    map->capacity *= 2;
    HashMapEntry* temp = (HashMapEntry*)calloc(map->capacity, sizeof(HashMapEntry));

    for (uint32_t i = 0; i < old_capicity; i++) {
        HashMapEntry* entry = &map->entries[i];
        if (entry->key == NULL) {
            continue;
        }

        uint32_t index = hash(entry->key) % map->capacity;

        for (uint32_t j = 0; j < map->capacity; j++) {
            uint32_t try = (index + j) % map->capacity;
            HashMapEntry* temp_entry = &temp[try];

            if (temp_entry->key == NULL) {
                temp_entry->key = strdup(entry->key);
                temp_entry->value = malloc(map->element_size);
                memcpy(temp_entry->value, entry->value, map->element_size);
                break;
            }

            if (strcmp(temp_entry->key, entry->key) == 0) {
                memcpy(temp_entry->value, entry->value, map->element_size);
                break;
            }
        }
    }

    free(map->entries);
    map->entries = temp;
}