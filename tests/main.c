#include <primer/primer.h>

void test_list()
{
    pr_int i = 5;
    pr_list *list;

    list = pr_list_new(pr_int_t);
    pr_list_push(list, (void*)(&i));

    pr_object_deref((pr_object*)list);
}

int main(int argc, char argv[])
{
    // list
    test_list();

    return 0;
}
