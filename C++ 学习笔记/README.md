# C++面试题学习笔记

## 语法

### std::sort

[std::sort源码剖析](http://feihu.me/blog/2014/sgi-std-sort/)

### const
* 修饰常指针
> const int *A; //const修饰指向的对象，A可变，A指向的对象不可变  
> int const *A; //const修饰指向的对象，A可变，A指向的对象不可变  
> int *const A; //const修饰指针A， A不可变，A指向的对象可变  
> const int *const A;//指针A和A指向的对象都不可变  
[C/C++中的const的用法](https://www.jianshu.com/p/2b68d0974ea1)

### static
C语言:  

* 静态全局变量:
> 1. 在全局变量前加上 static 关键字，即为静态全局变量
> 2. 静态全局变量在程序的数据区分配内存，若未初始化则默认初始化为0，直到程序结束才销毁
> 3. 静态全局变量在该文件内可见，从变量定义处开始直到文件结束(普通全局变量在同一程序的其他文件中可见，默认是 external 属性，而静态全局变量是 internal 属性)， 而在其他文件中不可见

* 静态局部变量:
> 1. 在局部变量前加上 static 关键字，即为静态局部变量
> 2. 静态局部变量也存储在数据区(不在栈区)，程序执行之前就已分配内存，程序执行结束后才销毁
> 3. 静态局部变量只在首次执行到声明处初始化一次，之后再执行该语句时不在初始化，若没有初始化则编译器会将其初始化为0
> 4. 其作用域与局部变量的作用域一样，从定义处到所处语句块结束

* 静态函数:
> 1. 在普通函数的返回类型前加上 static 关键字，即为静态函数
> 2. 只能在本文件中使用



C++:  
* 静态数据成员
> 1. 在类内数据成员前加上 static 关键字，即为静态数据成员
> 2. 对于类静态数据成员，无论有多少个该类的对象，该静态数据成员在内存中只有一份拷贝(其他普通数据成员，每个类对象都有自己的内存拷贝)，该静态数据成员由所有该类对象共享
> 3. 静态数据成员存储在全局数据区，在定义时分配存储空间，程序运行结束时销毁
> 4. 静态数据成员不能再类中定义和初始化，只能在类中声明，在类外进行定义和初始化，默认初始化为0
> 5. 静态数据成员的初始化为 <类型名> <类名>::<变量名> = <值>
> 6. 静态数据成员遵从 public private protected 访问规则
> 7. 静态数据成员可以直接使用类名加作用域运算符(::)直接访问 <类名>::<变量名>(访问规则允许的情况下)

* 静态成员函数
> 1. 在普通类成员函数前加上 static 关键字，即为静态成员函数
> 2. 在类外定义静态成员函数时，不用再加 static 关键字，只要在类中声明时加上即可
> 3. 静态成员函数只能访问静态数据成员和静态成员函数，普通成员函数可以访问静态成员函数和静态数据成员
> 4. 静态成员函数属于类，不属于任意一个类对象
> 5. 静态成员函数没有 this 指针
> 6. 可以使用 <类名>::<函数名> 访问，也可由类对象使用(./->)访问


[C/C++ 中 static 的用法](https://www.jianshu.com/p/7034c4dbc496)

### sizeof 字节数
* 空 struct 和空 class  
sizeof(Empty) = 1。  

* 32 位 64 位  
最大区别是 32 位指针大小为 4byte，而 64 位的指针大小为 8byte。  
[C++ 32位64位的区别](https://blog.csdn.net/crystal_lpx/article/details/71600721)  

* 字节对齐  

  [四字节内存对齐](https://blog.csdn.net/liujianli123/article/details/47045929)
> **准则**  
> 字节对齐的细节和具体编译器实现相关，但一般而言，满足三个准则：
> 1) 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；
> 2) 结构体每个成员相对于结构体首地址的偏移量都是成员大小的整数倍，如有需要编译器会在成员之间加上填充字节；
> 3) 结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要编译器会在最末一个成员之后加上填充字节。
> 
> 例子：
> ```C++
> struct Test
> {
>     int a;
>     char b;
>     double c[10];
>     char d;
> };
> ```
> 1. 如果只有 a，那么是 4。  
> 2. 如果只有 a 和 b，那么应用第 3 条，会在 b 后面填充字节，所以是 4 + 1 + (3)。
> 3. 如果只有 a 和 c，那么应用第 2 条，会在c前面填充，所以是 4 + (4) + 8 * 10。
> 4. 如果只有 b 和 c，同上，1 + (7) + 8 * 10。
> 4. 如果abcd，那么应用第3条，会在 c 后面填充字节，所以是 4 + 1 + (3) + 8 * 10 + 1 + (7)。  
> 
> 所以sizeof(Test) = 96  

* 位域字节对齐  
> 使用位域的主要目的是压缩存储，其大致规则为：
> 1) 如果相邻位域字段的类型相同，且其位宽之和小于类型的sizeof大小，则后面的字段将紧邻前一个字段存储，直到不能容纳为止；
> 2) 如果相邻位域字段的类型相同，但其位宽之和大于类型的sizeof大小，则后面的字段将从新的存储单元开始，其偏移量为其类型大小的整数倍；
> 3) 如果相邻的位域字段的类型不同，则各编译器的具体实现有差异，VC6采取不压缩方式，Dev-C++采取压缩方式；
> 4) 如果位域字段之间穿插着非位域字段，则不进行压缩；
> 5) 整个结构体的总大小为最宽基本类型成员大小的整数倍。
> 
> 例子：  
> ```C++
> struct Test_bit
> {
> 	int a : 8;
> 	int b : 8;
> 	int c : 8;
> 	char f;
> 	int d : 8;
> 	int e : 8;
> 	char g;
> };
> ```
> 1. int，4个字节，32位。
> 2. 如果只有abcd，那么是4。
> 3. 如果abcde，那么超过了32位，所以是4 + 4。
> 4. 如果abc f de，因为f是不同类型，所以是4 + 1 + (3) + 4。
> 5. 如果是abc f de g，同上，所以是4 + 1 + (3) + 4 + 1 + (3)。  
> 
> 所以sizeof(Test_bit) = 16

* sizeof(shared_ptr)  
由于control_block的存在，shared_ptr的size通常是2倍裸指针或unique_ptr的大小，此外，shared_ptr的引用计数增减是原子操作。



### Functor 仿函数
[详细](https://www.cnblogs.com/decade-dnbc66/p/5347088.html)

### 类成员函数
```C++
// 一段代码，说一下运行结果
class A {
public: 
    void f1() {}
    virtual void f2() {}
};

int main()
{
	A* a = nullptr;
	a->f1();
	a->f2();
}
```

类的成员函数并不与具体对象绑定，所有的对象共用同一份成员函数体。  

当程序被编译后，成员函数的地址即已确定，这份共有的成员函数体之所以能够把不同对象的数据区分开来，靠的是隐式传递给成员函数的this指针，成员函数中对成员变量的访问都是转化成"this->数据成员"的方式。  

因此，从这一角度说，成员函数与普通函数一样，只是多了一个隐式参数，即指向对象的this指针。  

而类的静态成员函数只能访问静态成员变量，不能访问非静态成员变量，所以静态成员函数不需要指向对象的this指针作为隐式参数。  

[详细](https://blog.csdn.net/chenzrcd/article/details/60472616)

### 命令行启动参数
```C++
int main(int argc, char * argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
}
```

---

## C++11
### 智能指针
std::shared_ptr采用引用计数，每一个shared_ptr的拷贝都指向相同的内容，当最后一个shared_ptr析构的时候，内存被释放。  

unique_ptr是一个独占指针，它不允许其他的智能指针共享其内部的指针。

弱引用指针weak_ptr是用来监视shared_ptr的，不会使引用计数加1或减1。  
它作为一个旁观者来监视shared_ptr管理的资源是否存在，也可以用来返回this指针或解决循环引用问题。  
它不共享指针，没有重载*和->， 因此不能操作资源

> 正确使用智能指针的基本规范：  
> * 不使用相同的内置指针值初始化（或reset）多个智能指针。
> * 不delete get()返回的指针。
> * 不使用get()初始化或reset另一个智能指针。
> * 如果你使用get()返回的指针，记住当最后一个对应的智能指针销毁后，你的指针就变为无效了。
> * 如果你使用智能指针管理的资源不是new分配的内存，记住传递给它一个删除器。

[智能指针 shared_ptr](https://www.jianshu.com/p/d304cfa56ca0)  
[智能指针 unique_ptr](https://www.jianshu.com/p/7aa369cc5c0b)  
[智能指针 weak_ptr](https://www.jianshu.com/p/d459616d5ba2)  



[实现智能指针1：unique_ptr](https://www.jianshu.com/p/77c2988be336)  



### 委托构造函数（Delegating constructors）
C++11扩展了构造函数的功能，增加了委托构造函数的概念，使得一个构造函数可以委托其他构造函数完成工作。  


> 和其他构造函数一样，一个委托构造函数也有一个成员初始值的列表和函数体。  
> 在委托构造函数内，成员初始值列表只有一个唯一的入口，就是类名本身。  
> 和其他成员初始值一样，类名后面紧跟圆括号括起来的参数列表，参数列表必须与类中另外一个构造函数匹配。  

```C++
struct Rect
{
	Rect() : Rect(0, 0, 0, 0, 0, 0) {}

	Rect(int l, int t, int r, int b) : Rect(l, t, r, b, 0, 0) {}

	Rect(int l, int t, int r, int b, int lc, int fc)
		: left(l), top(t), right(r), bottom(b), line_color(lc), fill_color(fc)
	{
		//do something else...
	}

	int left;
	int top;
	int right;
	int bottom;
	int line_color;
	int fill_color;
};
```
[委托构造函数](https://www.jianshu.com/p/01c9dd886ff1)



### 右值引用、移动语义和完美转发

[我理解的右值引用、移动语义和完美转发](https://www.jianshu.com/p/d19fc8447eaa)



### emplace

emplace_back是模板函数，对于{0}它无法确定是啥东东。push_back不是模板函数，它会直接构造一个对应的对象拷过去。



### 输入输出流重定向

```cpp
    FILE* ssin;
    freopen_s(&ssin, "1.in", "r", stdin);

    FILE* ssans;
    freopen_s(&ssans, "1.ans", "w", stdout);

    Solution sln;
    sln.main();

    freopen_s(&ssans, "CON", "w", stdout);
```



[C语言中输入输出重定向，freopen()妙用。](https://blog.csdn.net/zz460833359/article/details/48734935?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task)

---
## 知识

### C++三大特性
封装，继承，多态  
封装可以隐藏实现细节，使得代码模块化，继承可以扩展已存在的模块，它们目的都是为了：代码重用。而多态是为了实现另一个目的：接口重用。

[详细](https://blog.csdn.net/doo66/article/details/52208922)

### C++中的动态类型与动态绑定、虚函数、运行时多态的实现
静态绑定：编译时绑定，通过对象调用  
动态绑定：运行时绑定，通过地址实现  
[详细](https://blog.csdn.net/iicy266/article/details/11906509)

### C++堆和栈的区别和联系
[C++堆和栈的区别和联系](https://blog.csdn.net/yangyong0717/article/details/78001609)

### C++ 虚函数表剖析
[C++ 虚函数表剖析](https://www.jianshu.com/p/4649fae206ea)  

### C++类内存分布
[C++ 对象内存模型](https://www.jianshu.com/p/9fb37bb3094f)  
[深入研究C++多态（虚函数和虚继承）](https://www.jianshu.com/p/02183498a2c2)

### C++中引用和指针的区别
[C++中引用和指针的区别](https://blog.csdn.net/listening_music/article/details/6921608)