#include <primer/base.h>

const pr_type pr_int_t_val = {
    .name = "int",
    .size = sizeof(pr_int)
};

const pr_type *pr_int_t = &pr_int_t_val;

const pr_type pr_real_t_val = {
    .name = "real",
    .size = sizeof(pr_real)
};

const pr_type *pr_real_t = &pr_real_t_val;


void pr_object_ref(pr_object *obj)
{
    obj->rc += 1;
}

void pr_object_deref(pr_object *obj)
{
    obj->rc -= 1;
    if (obj->base == PR_CLASS && obj->rc <= 0) {
        obj->destructor(obj);
    }
}