#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
using namespace std;

class fraction
{
private:
    int frac_m; //分母
    int frac_c; //分子
public:
    //默认构造函数
    fraction() {
        frac_c = -1;
        frac_m = -1;
    }
    //初始化构造函数
    fraction(int c, int m) {
        frac_c = c;
        if (m == 0) {
            cout << "0不可作为分母" << endl;
        }
        frac_m = m;
    }
    //复制构造函数
    fraction(fraction& copy) {
        frac_m = copy.frac_m;
        frac_c = copy.frac_c;
    }
    fraction Inverse();
    fraction Reciprocal();
    void Reduction();
    void DtoF(double target);
    void StoF(string target);
    fraction operator+(const fraction& a);
    fraction operator-(const fraction& a);
    fraction operator*(const fraction& a);
    fraction operator/(const fraction& a);
    fraction operator%(const fraction& a);
    bool operator>(const fraction& a);
    bool operator<(const fraction& a);
    bool operator>=(const fraction& a);
    bool operator<=(const fraction& a);
    bool operator==(const fraction& a);
    bool operator!=(const fraction& a);
    void display();
    ~fraction() {
        frac_c = frac_m = 0;
    }
};
//取反
fraction fraction::Inverse() {
    fraction n_f(-1 * this->frac_c, this->frac_m);
    return n_f;
}
//取倒数
fraction fraction::Reciprocal() {
    fraction n_f(this->frac_c, this->frac_m);
    if (this->frac_c == 0)
    {
        cout << "0无倒数，故显示原值";
    }
    else
    {
        n_f.frac_c = this->frac_m;
        n_f.frac_m = this->frac_c;
    }
    if (this->frac_c < 0)
    {
        n_f.frac_c *= -1;
        n_f.frac_m *= -1;
    }
    return n_f;
}
//通分，返回通分的结果
void fraction::Reduction() {
    int n, b;
    if (this->frac_c == 0 || this->frac_m == 0)
        return;
    this->frac_c > this->frac_m ? (n = this->frac_c, b = this->frac_m) : (n = this->frac_m, b = this->frac_c);
    if (n * b < 0)
    {
        if (n < 0)
            n *= -1;
        else if(b < 0)
            b *= -1;
        // 此处可避免越界，即 n * b 超过int上限
    }
    int r = n % b;
    while (r > 1)
    {
        n = b;
        b = r;
        r = n % b;
    }
    if (r == 0)
    {
        this->frac_c /= b;
        this->frac_m /= b;
    }
}
//double转fraction
void fraction::DtoF(double target) {
    int m = 1000000;
    int c = int(target * m);
    //检查0
    if (target == 0)
    {
        this->frac_c = 0;
        this->frac_m = 1;
    }
    else
    {
        this->frac_m = m;
        this->frac_c = c;
        this->Reduction();
    }
}
//string转fraction
void fraction::StoF(string target) {
    int m = 0, c = 0;//用来存储转换后的分母和分子
    string m_s, c_s;//用来存储分母和分子的string，方便后续分别转换
    int count = 0;//count计算位数
    int i = 0;
    int label = 0;//label标记是否为负数，是则1，否则0
    for (; target[i] != '/' && target[i] != '\0'; i++) {
        //对读取的字符进行检查
        //是数字或负号则通过，否则终止
        if (target[i] > '9' || target[i] < '0') {
            if (i == 0 && target[i] == '-')
                label = 1;
            else
            {
                cout << "目标字符串非分数" << endl;
                return;
            }
        }
        else if (target[0] == '0')
        {
            this->frac_c = 0;
            this->frac_m = 1;
            return;
        }
        count++;
        c_s += target[i];
    }
    int temp_c = count;
    if (label)
    {
        temp_c--;
        for (int j = 1; j < count; j++) {
            c += (char(c_s[j]) - '0') * pow(10, temp_c - 1);
            temp_c--;
        }
    }
    else
    {
        for (int j = 0; j < count; j++) {
            c += (char(c_s[j]) - '0') * pow(10, temp_c - 1);
            temp_c--;
        }
    }
    //如果输入的是整数，则直接得到分数
    if (target[i] == '\0')
    {
        this->frac_c = c;
        this->frac_m = 1;
        return;
    }
    count = 0;
    i++;
    for (; target[i] != '\0'; i++) {
        if (target[i] > '9' || target[i] < '0') {
            cout << "目标字符串非分数" << endl;
            return;
        }
        count++;
        m_s += target[i];
    }
    temp_c = count;
    for (int j = 0; j < count; j++) {
        m += (char(m_s[j]) - '0') * pow(10, temp_c - 1);
        temp_c--;
    }
    if (label)
        c *= -1;
    this->frac_c = c;
    this->frac_m = m;
    this->Reduction();
}
//通分，用%重载
fraction fraction::operator%(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = this->frac_c * a.frac_m;
    return n_f;
}
//加重载
fraction fraction::operator+(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = (this->frac_c * a.frac_m) + (this->frac_m * a.frac_c);
    n_f.Reduction();
    return n_f;
}
//减重载
fraction fraction::operator-(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = (this->frac_c * a.frac_m) - (this->frac_m * a.frac_c);
    n_f.Reduction();
    return n_f;
}
//乘重载
fraction fraction::operator*(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = this->frac_c * a.frac_c;
    if (n_f.frac_c == 0)
        return n_f;
    n_f.Reduction();
    return n_f;
}
//除重载
fraction fraction::operator/(const fraction& a) {
    fraction n_f(0, 1);
    //检查分母是否为零
    if (a.frac_m * a.frac_c == 0)
    {
        cout << "0不可作为除数" << endl;
        exit(-1);
    }
    n_f.frac_m = this->frac_m * a.frac_c;
    n_f.frac_c = this->frac_c * a.frac_m;
    n_f.Reduction();
    return n_f;
}
//显示函数
void fraction::display() {
    this->Reduction();
    //检查是否为合法0
    if (this->frac_c == 0 && this->frac_m != 0)
    {
        cout << 0 ;
        return;
    }
    else
    {
        //检查1
        if (this->frac_m == 1)
        {
            cout << this->frac_c;
            return;
        }
        //检查分母
        else if (this->frac_m != 0)
        {
            if (this->frac_c != this->frac_m && (this->frac_c * -1) != this->frac_m)
                cout << this->frac_c << '/' << this->frac_m;
            else if (this->frac_c == this->frac_m)
                cout << 1;
            else
                cout << -1;
            return;
        }
        else
        {
            cout << "0不可作为分母" << endl;
            return;
        }
    }
}
//重载>
bool fraction::operator>(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c > a_c)
        return true;
    return false;
}
//重载<
bool fraction::operator<(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c < a_c)
        return true;
    return false;
}
//重载>=
bool fraction::operator>=(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c >= a_c)
        return true;
    return false;
}
//重载<=
bool fraction::operator<=(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c <= a_c)
        return true;
    return false;
}
//重载==
bool fraction::operator==(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c == a_c)
        return true;
    return false;
}
//重载!=
bool fraction::operator!=(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c != a_c)
        return true;
    return false;
}

int main() {
    int INF = 999;
    int m, c;
    while (1)
    {
        cout << "请输入依次分子和分母" << endl;
        cin >> c >> m;
        if (!cin.good())
        {
            cin.clear();
            cin.ignore(INF, '\n');
        }
        else if (m == 0)
            cout << "0不可作为分母" << endl;
        else
            break;
    }
    fraction f(c, m), t(12, 7);
    cout << "display：" << endl;
    f.display();
    cout << endl;
    cout << "第一部分：" << endl;
    fraction Inv;
    cout << "Inverse：" << endl;
    Inv = f.Inverse();
    Inv.display();
    cout << endl;
    fraction Rec;
    cout << "Reciprocal：" << endl;
    Rec = f.Reciprocal();
    Rec.display();
    cout << endl;
    Sleep(1000);
    double d;
    fraction f1;
    cout << "请输入一个小数" << endl;
    cin >> d;
    f1.DtoF(d);
    f1.display();
    cout << endl;
    Sleep(1000);
    string s;
    fraction f2;
    cout << "请输入分数（格式：整数/整数）" << endl;
    cin >> s;
    f2.StoF(s);
    f2.display();
    cout << endl;
    Sleep(2000);
    cout << "第二部分：" << endl;
    fraction result;
    cout << "接下来将测试算术运算符，测试对象为最开始输入的分数和12/7" << endl;
    f.display();
    cout << "+";
    t.display();
    cout << "=";
    result = f + t;
    result.display();
    cout << endl;
    f.display();
    cout << "-";
    t.display();
    cout << "=";
    result = f - t;
    result.display();
    cout << endl;
    f.display();
    cout << "*";
    t.display();
    cout << "=";
    result = f * t;
    result.display();
    cout << endl;
    f.display();
    cout << "/(";
    t.display();
    cout << ")=";
    result = f / t;
    result.display();
    cout << endl;
    f.display();
    cout << "%";
    t.display();
    cout << "=(即通分)";
    result = f % t;
    result.display();
    cout << endl;
    Sleep(2000);
    cout << "第三部分：" << endl;
    cout << "接下来将测试比较运算符，测试对象为最开始输入的分数和12/7" << endl;
    f.display();
    cout << ">";
    t.display();
    cout << ":";
    cout << (f > t) << endl;
    f.display();
    cout << "<";
    t.display();
    cout << ":";
    cout << (f < t) << endl;
    f.display();
    cout << ">=";
    t.display();
    cout << ":";
    cout << (f >= t) << endl;
    f.display();
    cout << "<=";
    t.display();
    cout << ":";
    cout << (f <= t) << endl;
    f.display();
    cout << "!=";
    t.display();
    cout << ":";
    cout << (f != t) << endl;
    f.display();
    cout << "==";
    t.display();
    cout << ":";
    cout << (f == t) << endl;

    return 0;
}
