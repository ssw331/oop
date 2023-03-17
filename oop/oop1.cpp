#include<iostream>
#include"oop_doc.h"
using namespace std;

class Point;//前向声明，没有类体，无法实例化，可以引用或当指针

class haha
{
private:
	int test;//禁止在类声明时对成员变量初始化
public:
	haha()//构造函数
	{
		test = -1;//主要目的：初始化对象中的私有/保护成员
	}
	haha(int in)
	{
		test = in;
	}
	void helloworld(int, const haha&);
	haha& x();//不要返回局部对象的指针或引用，会导致迷向指针
	haha* y();
};

//构造函数的无参数调用:
haha 你;
//构造函数的有参数调用:
haha 我(0);

class Point
{
public:
	int x,y;
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