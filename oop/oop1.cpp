#include<iostream>
#include"oop_doc.h"
using namespace std;

class Point;//ǰ��������û�����壬�޷�ʵ�������������û�ָ��

class haha
{
private:
	int test;//��ֹ��������ʱ�Գ�Ա������ʼ��
public:
	haha()//���캯��
	{
		test = -1;//��ҪĿ�ģ���ʼ�������е�˽��/������Ա
	}
	haha(int in)
	{
		test = in;
	}
	void helloworld(int, const haha&);
	haha& x();//��Ҫ���ؾֲ������ָ������ã��ᵼ������ָ��
	haha* y();
};

//���캯�����޲�������:
haha ��;
//���캯�����в�������:
haha ��(0);

class Point
{
public:
	int x,y;
}p{ 10,10 };//����౾��ĳ�Ա�������ǹ����ģ���ô�����ô�����ֱ�ӳ�ʼ��

void haha::helloworld(int a,const haha& b)//�����ϣ������/ָ������ݱ���д��const�ؼ��ʿ��Է�ֹ�ں������ڸ�д����
{
	return;
}

int main()
{
	haha A, B;
	A = B;//ֻ��ԷǾ�̬��Ա�������и�ֵ��
	//�����ֻ��ͬ������������
	haha* p;
	p = new haha;//Caution������Ϊ����̬����ռ�� **����** ���ų���������Զ�����
	delete p;//�����ֶ�delete
}