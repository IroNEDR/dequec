#include <stdlib.h>
#include <stdbool.h>
#include "deque.h"

error_t *initDeque(Deque *deque)
{
    deque = (Deque *)malloc(sizeof(Deque));
    if (deque == NULL)
    {
        return E_ALLOCATION;
    }
    deque->buffer = (void **)malloc(sizeof(void *) * DEFAULT_CAPACITY);
    if (deque->buffer == NULL)
    {
        return E_ALLOCATION;
    }
    deque->front = -1;
    deque->back = -1;
    deque->capacity = DEFAULT_CAPACITY;
    deque->size = 0;
    return E_SUCCESS;
}

bool isEmpty(Deque *deque)
{
    return deque->size == 0;
}

bool isFull(Deque *deque)
{
    return deque->size == deque->capacity;
}

error_t __resize(Deque *deque)
{
    int32_t capacity = deque->capacity * 2;
    void **buffer = (void **)malloc(sizeof(void *) * capacity);
    if (buffer == NULL)
    {
        return E_ALLOCATION;
    }
    int32_t oldIndex = deque->front;
    int32_t newDequeIndex = 0;

    while (newDequeIndex < deque->size)
    {
        buffer[newDequeIndex] = deque->buffer[oldIndex];
        oldIndex = (oldIndex + 1) % deque->capacity;
        newDequeIndex++;
    }
    free(deque->buffer);
    deque->buffer = buffer;
    deque->front = 0;
    deque->back = deque->size - 1;
    deque->capacity = capacity;
}

void pushFront(Deque *deque, void *insert_data)
{
    if (isFull(deque))
    {
        __resize(deque);
    }
    if (isEmpty(deque))
    {
        deque->front = deque->back = 0;
    }
    else
    {
        deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    }
    deque->buffer[deque->front] = insert_data;
    deque->size++;
}

void pushBack(Deque *deque, void *insert_data)
{
    if (isFull(deque))
    {
        __resize(deque);
    }
    if (isEmpty(deque))
    {
        deque->front = deque->back = 0;
    }
    else
    {
        deque->back = (deque->back + 1) % deque->capacity;
    }
    deque->buffer[deque->back] = insert_data;
    deque->size++;
}

error_t popFront(Deque *deque, void *return_data)
{
    if (isEmpty(deque))
    {
        return E_EMPTY_DEQUE;
    }
    void *removed = deque->buffer[deque->front];
    if (deque->front == deque->back)
    {
        deque->front = deque->back = -1;
    }
    else
    {
        deque->front = (deque->front + 1) % deque->capacity;
    }
    deque->size--;
    return E_SUCCESS;
}

error_t popBack(Deque *deque, void *return_data)
{
    if (isEmpty(deque))
    {
        return E_EMPTY_DEQUE;
    }
    void *removed = deque->buffer[deque->back];
    if (deque->front == deque->back)
    {
        deque->front = deque->back = -1;
    }
    else
    {
        deque->back = (deque->back - 1 + deque->capacity) % deque->capacity;
    }
    deque->size--;
    return E_SUCCESS;
}

void destroyDeque(Deque *deque)
{
    if (deque)
    {
        free(deque->buffer);
        free(deque);
    }
}

char *getErrorDescription(error_t error_code)
{
    for (size_t i = 0; i < (sizeof(errordesc) / sizeof(errordesc[0])); i++)
    {
        if (errordesc[i].code == error_code)
        {
            return errordesc[i].description;
        }
    }

    return "Unknown error";
}