# CMaps — A Simple C HashMap Implementation

CMaps is a lightweight, type-generic hashmap (associative array) implementation in C. It uses open addressing and linear probing for collision resolution and supports automatic resizing when the table becomes half full.

## Features

- Key-value storage using string keys
- Type-generic values via `void*`
- Open addressing with linear probing
- Dynamic resizing
- Minimal dependencies (`stdlib.h`, `string.h`, `stdint.h`, `stdio.h`)

## Example Usage

```c
#include "map.h"

int main() {
    HashMap map;
    init_hashmap(&map, sizeof(int));

    int value = 42;
    push_hashmap(&map, "answer", &value);

    int* retrieved = (int*)get_hashmap(&map, "answer");
    if (retrieved) {
        printf("Value: %d\n", *retrieved); // Output: Value: 42
    }

    remove_hashmap(&map, "answer");
    free_hashmap(&map);
    return 0;
}
