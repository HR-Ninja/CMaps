# CMaps — A Simple C HashMap Implementation

CMaps is a lightweight, type-generic hashmap (associative array) implementation in C.  
It uses open addressing with linear probing (and tombstones for deletions) and supports automatic resizing when the table exceeds a 70% load factor.

## Features

- Key-value storage using string keys
- Type-generic values via fixed-size allocations (`element_size` set at initialization)
- Open addressing with linear probing and tombstone deletion
- Dynamic resizing at 70% load factor
- Minimal dependencies (`stdlib.h`, `string.h`, `stdint.h`, `stdio.h`)

## Example Usage

```c
#include "map.h"

int main() {
    HashMap map;
    if (init_hashmap(&map, sizeof(int)) == HASHMAP_FAIL) {
        printf("Failed to init hashmap.\n");
    }

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
```
## Details

- **Hashing**: Uses the FNV-1a hash function for fast and well-distributed string hashing  
- **Collisions**: Resolved via linear probing with tombstone markers for efficient deletions  
- **Memory**: Keys are duplicated with `strdup`, and values are heap-allocated according to the fixed `element_size` set at initialization. 

All memory (keys, values, and entry array) is automatically freed using `free_hashmap`.  


## License
MIT License. Feel free to use, modify, and distribute.
