#include <vector.h>

#include <stdlib.h>
#include <string.h>


/**
 *    Private
 */

struct vector_t
{
    void **data;
    unsigned int size;
    unsigned int capacity;
}; 


/**
 *    Public methods
 */

Vector * vector_create(void)
{
    Vector *vector = (Vector *)malloc(sizeof(Vector));

    if (vector) {
        memset(vector, 0, sizeof(*vector));

        vector->data = NULL;
        vector->size = 0;
        vector->capacity = 0;
    }

    return vector;
}

void vector_destroy(Vector *vector)
{
    free(vector->data);
    free(vector);
}

unsigned int vector_size(const Vector *vector)
{
    return vector->size;
}

unsigned int vector_capacity(const Vector *vector)
{
    return vector->capacity;
}

void * vector_at(const Vector *vector, unsigned int index)
{
    if (index < vector->size) {
        return vector->data[index];
    }

    return NULL;
}

void * vector_front(const Vector *vector)
{
    return vector_at(vector, 0);
}

void * vector_back(const Vector *vector)
{
    return vector_at(vector, vector->size - 1);
}

void ** vector_begin(const Vector *vector)
{
    return vector->data;
}

void ** vector_end(const Vector *vector)
{
    return vector->data + vector->size;
}

void vector_push_back(Vector *vector, void *element)
{
    if (vector->size >= vector->capacity) {
        vector->capacity = (vector->capacity)?  vector->capacity << 1 : 1;

        const size_t data_size = sizeof(void *) * vector->capacity;

        if (vector->data) {
            vector->data = (void **)realloc(vector->data, data_size);
        }
        else {
            vector->data = (void **)malloc(data_size);
        }
    }

    if (!vector->data) {
        vector->size = 0;
        vector->capacity = 0;

        return;
    }

    vector->data[vector->size++] = element;
}

void vector_pop_back(Vector *vector)
{
    if (vector->size) {
        vector->data[--vector->size] = NULL;
    }
}

int vector_index_of(Vector *vector,
                    void *object,
                    bool (*compare)(const void *element, const void *object))
{
    if (!object ||
        !compare)
    {
        return -1;
    }

    int index;

    for (index = 0; index < vector->size; ++index) {
        void *element = vector_at(vector, index);

        if (compare(element, object)) {
            return index;
        }
    }

    return -1;
}