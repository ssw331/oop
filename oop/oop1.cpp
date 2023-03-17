#include<iostream>
#include"oop_doc.h"
using namespace std;

class Point;//前向声明，没有类体，无法实例化，可以引用或当指针

class haha
{
private:
	int test;
public:
	haha()
	{
		test = -1;
	}
	void helloworld();
};

void haha::helloworld()
{
	return;
}

int main()
{

}