#ifndef _TEST_CLASS_H_
#define _TEST_CLASS_H_

#include<vector>

class B;

class A
{
    public:
        A(){privateVal=0;}                      //默认构造函数
        A(int val){privateVal=val;}             //带参数的构造函数
        void set(int val){privateVal=val;}      //成员函数
        int get() const {return privateVal;};   //成员函数
        int cs();
        int publicVal;                          //公共数据成员
        std::vector<B> m_vB;
    private:
        int privateVal;                           //私有数据成员
};

class B
{
    public:
        B(){}
        ~B(){}
        int pos;
        int len;
};

int accumulate(const std::vector<A>& v_A);
int addA(A &a, int addVal);                   //普通函数，有返回值，通过引用修改参数
void printA(const A& a);

#endif
