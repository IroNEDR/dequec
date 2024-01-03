#ifndef __DEQUE_H__
#define __DEQUE_H__
#include <stdint.h>
#define DEFAULT_CAPACITY 10

typedef enum
{
    E_SUCCESS = 0,
    E_ALLOCATION = 1,
    E_EMPTY_DEQUE = 2,
} error_t;

struct _errordesc
{
    int code;
    char *description;
} errordesc[] = {
    {E_SUCCESS, "No error"},
    {E_ALLOCATION, "Memory allocation error"},
    {E_EMPTY_DEQUE, "The given deque is empty"},
};

typedef struct
{
    void **buffer;
    int32_t front;
    int32_t back;
    int32_t capacity;
    int32_t size;
} Deque;

error_t *initDeque(Deque *deque);
bool isEmpty(Deque *deque);
bool isFull(Deque *deque);
void pushFront(Deque *deque, void *insert_data);
void pushBack(Deque *deque, void *insert_data);
error_t popFront(Deque *deque, void *return_data);
error_t popBack(Deque *deque, void *return_data);
void destroyDeque(Deque *deque);
char *getErrorDescription(error_t error_code);
#endif