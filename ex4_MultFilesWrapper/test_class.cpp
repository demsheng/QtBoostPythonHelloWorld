//test_class.cpp
#include <stdio.h>
#include "test_class.h"

int addA(A &a, int addVal)
{
    int val = a.get();
    val += addVal;
    a.set(val);
    return val;
}
void printA(const A& a)
{
    printf("%d\n", a.get());
}
