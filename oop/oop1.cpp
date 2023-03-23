#include<iostream>
#include"oop_doc.h"
using namespace std;

class Point;//前向声明，没有类体，无法实例化，可以引用或当指针

class haha
{
private:
	int test;//禁止在类声明时对成员变量初始化
public:
	haha()//构造函数--》没有参数的构造函数即默认构造函数
	{
		test = -1;//主要目的：初始化对象中的私有/保护成员
	}
	haha(int in, int out = -1)//构造函数重载
	{
		test = in;
	}
	haha(int why, int so) :test(1)//构造函数的初始化列表（:之后的玩意儿）
		//如果没有初始化列表，同时没有默认构造函数，那么系统会报错
		//因为没有初始化列表的话，系统会调用默认构造函数
		//初始化列表不在声明中指明，而是在定义中指明
		//即构造函数在体外定义时才指明初始化列表
		//初始化列表中每个成员只能被指定一次
		//实际的初始化顺序和列表的顺序无关，和成员在类中的定义顺序绑定
		//避免用成员初始化成员
	{
		cout << test;
	}
	void helloworld(int, const haha&);
	haha& x();//不要返回局部对象的指针或引用，会导致迷向指针
	haha* y();
};

//构造函数的无参数调用:
haha 你;
//构造函数的有参数调用:
haha 我(0);

//构造函数在定义对象时自动调用，其余生命期无法主动调用
//这玩意儿一般是公有的，毕竟私有了你也没法在类外初始化对象了
/*
* 对于构造函数，一般不提倡在里面干初始化之外的事
* 构造函数应当对每个成员函数进行初始化
* 构造函数一次用一种
* 还是那句话，构造函数依然是函数。默认参数也是可以加入的
* 但同样的，一旦出现重载和默认参数的参数列表有冲突（二义性出现），调用会出问题
* 默认参数只能在类内指定（其实就是必须在声明时指定）
* 
* 类有且仅有一个默认构造函数，当类内没有默认构造函数的定义的时候，编译器会自动定义一个默认构造函数（空函数）
*/

class Point
{
public:
	int x,y;
	Point(const string& obj);
	//构造函数隐式转换实现：
    // 类名(const 指定数据类型& obj)
    // 可以在类内对构造函数用explicit关键字来禁止构造函数的隐式转换
}p{ 10,10 };//如果类本身的成员函数都是公共的，那么可以用大括号直接初始化

void haha::helloworld(int a,const haha& b)//如果不希望引用/指针的内容被改写，const关键词可以防止在函数体内改写数据
{
	return;
}

int main()
{
	haha A, B;
	A = B;//只会对非静态成员变量进行赋值。
	//上语句只对同类对象变量成立
	haha* p;
	p = new haha;//Caution：这里为对象动态分配空间后 **不会** 随着程序结束而自动销毁
	delete p;//必须手动delete
}