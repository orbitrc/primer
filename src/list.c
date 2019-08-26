#include <primer/list.h>

#include <stdlib.h>

struct pr_list {
    pr_object base_object;
    const pr_type *generic_type;
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

    return list;
}
