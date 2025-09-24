#include "map.h"

int main() {
    HashMap map;
    if (init_hashmap(&map, sizeof(int)) == HASHMAP_FAIL) {
        printf("Failed to init hashmap.\n");
    }

    int i = 10;
    push_hashmap(&map, "test 1", &i);
    int* test = (int*)get_hashmap(&map,"test 1");

    if(test != NULL) {
        printf("Test Value: %d\n", *test);
    }

    remove_hashmap(&map, "test 1");
    test = (int*)get_hashmap(&map,"test 1");

    if(test == NULL) {
        printf("Test was removed");
    }
    else {
        printf("Test was not removed");
    }

    free_hashmap(&map);

    return 0;
}
