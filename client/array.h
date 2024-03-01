struct array{
    unsigned int size; // Count of items currently in list
    unsigned int capacity; // Allocated memory size, in items
    void **body; // Pointer to allocated memory for items (of size capacity * sizeof(void*))
};


void destroy_array(struct array *l);

void *get_from_array(struct array *l, unsigned int index);

void add_to_array(struct array *l, void *item);

struct array *create_array();