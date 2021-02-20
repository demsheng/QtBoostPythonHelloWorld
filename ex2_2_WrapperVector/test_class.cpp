//test_class.cpp

#include <stdio.h>
#include "test_class.h"

int A::cs()
{
    return privateVal;
}

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

int accumulate(const std::vector<A>& v_A)
{
    int ret = 0;
    for (size_t i = 0; i < v_A.size(); i++)
    {
        ret += v_A[i].get();
    }
    return ret;
}
