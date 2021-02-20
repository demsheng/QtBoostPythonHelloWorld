import test_class
a1 = test_class.A()
b1 = test_class.B()    # 实例化一个B
b1.pos = 1
b1.len = 1
b2 = test_class.B()    # 实例化另一个B
b2.pos = 2
b2.len = 2
a1.vB.append(b1)      # a1.vB是vector<B>在python中对应类型的对象，接口类似list，但只能添加B类型的对象
a1.vB.append(b2)
print (a1.vB[-1].len)        # a1.vB支持list的下标引用

a1.set(1)
a2 = test_class.A(2)
a3 = test_class.A(3)
vA = test_class.VecA()    # vector<A>在python中对应的类型
vA.append(a1)
vA.append(a2)
vA.append(a3)
print (test_class.accumulate(vA))      # 调用以vector<A>为参数的函数
