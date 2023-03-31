#include<iostream>
#include"oop_doc.h"
using namespace std;

class Point;//前向声明，没有类体，无法实例化，可以引用或当指针

class haha
{

	//this: 每个成员函数的隐式形参，是一个对象指针
	//每次编译都会对成员函数进行重写
	//所以实际上每次调用的时候都会把对象的地址传参给this
	//需要返回对象自身的函数可以返回*this
	//如果成员名和形参名相同时也可以用this指针来区分
	//如果成员函数是const常函数，那么重写时this形参会变成const 类名 *const this，成为指向常对象的常指针
private:
	int test;//禁止在类声明时对成员变量初始化
	char* str;
public:
	int what;
	haha()//构造函数--》没有参数的构造函数即默认构造函数
	//没有任何构造函数的定义时编译器会自动定义合成默认构造函数
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
		//一般初始化（不用对象初始化对象）都会调用构造函数，无论是 对象名(参数)，还是 对象名=参数
	{
		cout << test;
	}
	haha(const haha& r) :test(r.test)//复制构造函数
		//有且只有一个参数：本类类型的对象引用
		//赋值：对已有对象赋予值
		//复制：生成一个和已有对象相同的原本不存在的对象
		//每个类必须有一个复制构造函数
		//如果没有定义，那么系统会生成一个合成复制构造函数，会逐个成员初始化（针对非静态成员）
		//在函数传参和返回对象、一般的用对象初始化对象、*用元素初始化列表初始化数组元素*时
		//浅复制：没有对数据的动态内存部分进行复制，而仅仅复制了一个指针
		//		浅复制的问题，一旦源本被撤销，那么副本会丢失数据
		//深复制：动态内存部分也复制了
		//合成复制构造函数一般是浅复制
	{
		test = r.test;
		str = new char[test];
		if (str != 0)
			strcpy(str, r.str);
		//以上为深复制
		str = r.str;
		//以上为浅复制
	}
	void helloworld(int, const haha&);
	haha& x();//不要返回局部对象的指针或引用，会导致迷向指针
	haha* y();
	~haha()//析构函数，销毁对象用，有且仅有一个，不可重载，在对象离开作用域后系统会自动调用
		//编译器总会生成一个合成析构函数，不论有没有定义析构函数
		//合成析构函数只删除指针，分配的内存空间是不会被合成析构函数回收的
		//如果类需要析构函数，那么几乎一定要定义复制构造函数和赋值运算符重载，又称析构函数三法则
		//合成析构函数是没有delete指令的
	{

	}
	//析构和构造的调用次序：先构造的后析构，后构造的先析构。
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

//类的作用域：
//即类定义时的类体内，注意:即使有同成员列表的类，名字不同时是完全不同的作用域
//类作用域外只能用对象、指针或引用的方式来访问成员
//静态成员和类中类型成员需要用类作用域运算符访问（::）

//作用域运算符视为类作用域的延伸
/*
* 类成员声明中的名字查找：
*	1. 检查出现在名字使用之前的声明
*	2. 如果1查找失败，则查找包含类作用域中的声明和出现在类定义
*	   之前的声明
* 类成员定义中的名字查找：
*	1. 检查成员函数局部作用域中的声明
*	2. 如果1失败，则检查所有类成员的声明
*	3. 如果2失败，则检查在此类定义之前的作用域中的声明
*/

class T//外围类
{
public:
	int z;
private:
	int y;
	static int m;
	enum alpha { A, B, C, D };
	class Q
	{
		alpha A;
		int x;
		Q()
		{
			x = m;
			x = y;
			x = z;
		}
		//嵌套类
		/*
		* 嵌套类是独立的类
		* 与外围类相互独立（对象也是），且只在外围类的作用域中可见其名字
		* 即不会在其他作用域中发货所能名冲突
		* 完全独立的类，可以按照一般类来理解其定义方式
		* 外围类的对象不包括嵌套类，反之亦然
		* 嵌套类可以直接引用外围类的静态成员、类型名和枚举成员
		* 外围类作用域之外的成员引用则需要作用域运算符
		*/
	};
};

int w = 1;

void none()
{
	int x = 10;
	static int z = 10;
	class P
	{
		int y;
		P()
		{
			y = w;
			y = z;
			y = x;//出错
		}
		//局部类
		/*
		* 所有成员必须定义在类体内
		* 只能访问外围的作用域中定义的类型名、静态变量和枚举成员
		* 函数中的动态变量无法使用，包括参数
		*/
	};
}

//按照生命期的分类：
/*
* 1. 局部对象：仅存在于函数体内，函数结束则自动释放
* 2. 静态局部对象：作用域仅限函数体内，但生命期自第一次定义开始到程序结束被释放
* 3. 全局对象：程序开始到程序结束被释放
* 4. 自由存储对象：由new开始，由delete结束(没有delete的话即使运行结束也是不会释放的）
*/

//释放均是通过析构函数释放

//const 限定： 将函数/变量限定为只读
const haha A;
haha const B;
const int C;
//常引用
const haha& b;
//指向常变量的指针
const int* p;
//常指针
int const* q;
class what
{
	int fun() const//表示常成员函数-->内部对于成员的修改都会被拒绝
	{

	}
	const int fun1()//表示返回常量的函数
	{

	}
};

//静态数据成员
/*
* 使用前必须初始化
* 初始化有且仅有一次，不会受到public/private/protected限制
* 初始化时无须静态关键字，但需要类作用域运算符
* 可以作为成员函数的默认参数
* e.g.   void func(int i = _static_int)
* 可以被定义为所在类的对象
*/
//静态成员函数
/*
* 只能访问静态成员（包括变量和函数）
* 由于静态成员函数不会隐式创建this指针，所以可以不定义对象而直接调用静态成员函数
*/
int main()
{
	haha A, B;
	const haha* const th = &A;
	haha list[2] = { haha(6), haha(6) };//可以用这种方式定义对象数组
	haha why[3] = { 2,3,4 };//这里是将{}内的值作为实参分别传给具有单个形参（不包括默认参数）的构造函数进行对象初始化。
	//构造函数的调用次序是按照数组序号从小到大，析构相反
	//没有初始化就会开始调用默认构造函数
	haha* p = &A;
	p->helloworld(1, B);
	int* q = &A.what;//可以指向非私有成员，不可指向私有成员
	int haha::*w = &haha::what;//数据成员指针：数据成员类型 类名::*指针变量名=成员地址初值;
	A = B;//只会对非静态成员变量进行赋值。
	//上语句只对同类对象变量成立
	void (haha:: * f)(int a, const haha& b) = &haha::helloworld;
	//成员函数指针：
	//返回类型 (类名::*指针变量名)(形式参数列表) <const> =成员函数地址初值
	//const对于 常函数 是需要的，一般函数不加
	//常函数： 返回类型 函数名(形参列表) const{函数体};

	//typedef char (Data::*GETFUNC)(Data::index,Data::index) const;
	//可以用这种方式使用类型别名，简化语句

	//类成员指针的使用：
	(A.*f)(1, B);
	p->*w;
	p = new haha;//Caution：这里为对象动态分配空间后 **不会** 随着程序结束而自动销毁
	delete p;//必须手动delete
}