#include <iostream>
using namespace std;
class A { //A类定义
public: int n; //公有数据成员
	  A(int _n = 10) :n(_n) { cout << "A(" << n << ")构造\t"; } //构造函数
	  ~A() { cout << "A(" << n << ")析构\t"; } //析构函数
};
class B { //B类定义
public: int m; //公有数据成员
	  A a; //A类类型对象a
	  B(int _n = 20) :m(_n), a(_n) { cout << "B(" << m << ")构造" << endl; } //构造函数
	  B(const B& Copy)
	  {
		/*  m = Copy.m;*///如果没有这一行指令，那么m会是未初始化的状态，但如果在函数传参时运行到这一步，应当已经完成了默认构造函数（且实现时确实出现了A的构造函数）
		  a = Copy.a;
		  cout << "B(" << m << ")复制" << endl;
	  }
	  ~B() { cout << "B(" << m << ")析构" << endl; } //析构函数
};
B* gp, gb(30); //全局指针gp,全局B类型对象gb
void fun4() {
	static B b41(41); //静态的B类型局部对象b41
	B b42(42); //局部B类型对象b42
	gp = new B(43); //gp指向自由存储对象
}
void fun5() {
	static
		B b51(51); //静态的B类型局部对象b51
		B b52(52); //局部对象b52
}
B fun6(B b61) //形参对象
{
	cout << "局部对象生成" << endl;
	delete gp; //释放自由存储对象
	cout << "以下为局部对象析构" << endl;
	return b61;//向main作用域进行复制，复制给fun6(b71)
}
int main() {
	cout << "\n----------main start--------- " << endl;
	fun4(); cout << "\n---------fun4 end--------- " << endl;
	fun5(); cout << "\n---------fun5 end--------- " << endl;
	B b71(71), b72(72); //B类型的2个局部对象b71和b72
	b72 = fun6(b71); //对象b71作为形参，函数返回临时对象,这里调用了复制构造函数
	//但为何没有默认构造函数的调用？就是没有默认构造函数，记住每次定义对象只会调用一个构造函数，复制构造函数只在定义时会用，赋值不会调用这个
	//结论：传参会直接调用复制构造函数
	cout << "\n---------main end--------- " << endl;
	return	0;
}