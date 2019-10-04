#include <primer/list.h>

#include <string.h>
#include <stdlib.h>

struct pr_list {
    pr_object base_object;
    const pr_type *generic_type;
    int64_t m_capacity;
    int64_t m_count;
    void *m_items;
};

const pr_type pr_list_t_val = {
    .name = "list",
    .size = 0
};

const pr_type *pr_list_t = &pr_list_t_val;


pr_list* pr_list_new(const pr_type *type)
{
    pr_list *list = (pr_list*)malloc(sizeof(pr_list));

    ((pr_object*)list)->base = PR_CLASS;
    ((pr_object*)list)->rc = 1;
    list->generic_type = type;

    /* Initialize list. */
    list->m_capacity = 8;
    list->m_count = 0;
    if (type->size == 0) { /* Generic type is class. */
        list->m_items = malloc(sizeof(void*) * list->m_capacity);
    } else { /* Generic type is struct. */
        list->m_items = malloc(type->size * list->m_capacity);
    }

    return list;
}


void pr_list_push(pr_list *list, const void *val)
{
    int64_t size = list->generic_type->size; /* Size of generic type */

    /* Insert to list. */
    if (size == 0) {
        memcpy(
            (list->m_items + size * sizeof(void*)),
            val,
            sizeof(void*)
        );
    } else {
        memcpy(
            (list->m_items + size * (list->m_count)),
            val,
            size
        );
    }
    list->m_count += 1;

    // Re-allocate if capacity is full.
}


void pr_list_insert(pr_list *list, int64_t i, const void *val)
{
    /* TODO: implement */
}


int64_t pr_list_count(pr_list *list)
{
    return list->m_count;
}


void* pr_list_at(pr_list *list, int64_t i)
{
    /* TODO: implement */
    char *c_p = (char*)(list->m_items + i);
    return (void*)c_p;
}


void* pr_list_pop(pr_list *list)
{
    /* TODO: implement */
}


void pr_list_remove(pr_list *list, int64_t i)
{
    /* TODO: implement */
}
