/*
** EPITECH PROJECT, 2024
** My_radar
** File description:
** linked_list_mana
*/

#include "vfx.h"

linked_list_t *create_lists(void *data, int len)
{
    linked_list_t *head = malloc(sizeof(linked_list_t) * (len + 1));

    if (!head)
        return NULL;
    for (int i = 0; i < len; i++) {
        head[i].id = 0;
        head[i].next = head + i;
        head[i].previous = head + i;
        head[i].data = data;
    }
    return head;
}

linked_list_t *add_element(linked_list_t *head, void *data)
{
    linked_list_t *element = malloc(sizeof(linked_list_t));

    if (!element)
        return NULL;
    element->data = data;
    element->previous = head->previous;
    element->previous->next = element;
    element->next = head;
    head->previous = element;
    head->id--;
    element->id = head->id * -1;
    return element;
}

void *del_element(linked_list_t *head, linked_list_t *element)
{
    void *data = element->data;

    element->previous->next = element->next;
    element->next->previous = element->previous;
    free(element);
    head->id++;
    return data;
}

void free_list(linked_list_t *head, void (*free_func)(void *))
{
    linked_list_t *current = head->next;
    linked_list_t *next;

    while (current->id > 0) {
        next = current->next;
        if (free_func)
            free_func(del_element(head, current));
        else
            del_element(head, current);
        current = next;
    }
    free(head);
}
