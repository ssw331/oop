#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
using namespace std;

class fraction
{
private:
    int frac_m; //��ĸ
    int frac_c; //����
public:
    //Ĭ�Ϲ��캯��
    fraction() {
        frac_c = -1;
        frac_m = -1;
    }
    //��ʼ�����캯��
    fraction(int c, int m) {
        frac_c = c;
        if (m == 0) {
            cout << "0������Ϊ��ĸ" << endl;
        }
        frac_m = m;
    }
    //���ƹ��캯��
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
//ȡ��
fraction fraction::Inverse() {
    fraction n_f(-1 * this->frac_c, this->frac_m);
    return n_f;
}
//ȡ����
fraction fraction::Reciprocal() {
    fraction n_f(this->frac_c, this->frac_m);
    if (this->frac_c == 0)
    {
        cout << "0�޵���������ʾԭֵ";
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
//ͨ�֣�����ͨ�ֵĽ��
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
        // �˴��ɱ���Խ�磬�� n * b ����int����
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
//doubleתfraction
void fraction::DtoF(double target) {
    int m = 1000000;
    int c = int(target * m);
    //���0
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
//stringתfraction
void fraction::StoF(string target) {
    int m = 0, c = 0;//�����洢ת����ķ�ĸ�ͷ���
    string m_s, c_s;//�����洢��ĸ�ͷ��ӵ�string����������ֱ�ת��
    int count = 0;//count����λ��
    int i = 0;
    int label = 0;//label����Ƿ�Ϊ����������1������0
    for (; target[i] != '/' && target[i] != '\0'; i++) {
        //�Զ�ȡ���ַ����м��
        //�����ֻ򸺺���ͨ����������ֹ
        if (target[i] > '9' || target[i] < '0') {
            if (i == 0 && target[i] == '-')
                label = 1;
            else
            {
                cout << "Ŀ���ַ����Ƿ���" << endl;
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
    //������������������ֱ�ӵõ�����
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
            cout << "Ŀ���ַ����Ƿ���" << endl;
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
//ͨ�֣���%����
fraction fraction::operator%(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = this->frac_c * a.frac_m;
    return n_f;
}
//������
fraction fraction::operator+(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = (this->frac_c * a.frac_m) + (this->frac_m * a.frac_c);
    n_f.Reduction();
    return n_f;
}
//������
fraction fraction::operator-(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = (this->frac_c * a.frac_m) - (this->frac_m * a.frac_c);
    n_f.Reduction();
    return n_f;
}
//������
fraction fraction::operator*(const fraction& a) {
    fraction n_f(0, 1);
    n_f.frac_m = this->frac_m * a.frac_m;
    n_f.frac_c = this->frac_c * a.frac_c;
    if (n_f.frac_c == 0)
        return n_f;
    n_f.Reduction();
    return n_f;
}
//������
fraction fraction::operator/(const fraction& a) {
    fraction n_f(0, 1);
    //����ĸ�Ƿ�Ϊ��
    if (a.frac_m * a.frac_c == 0)
    {
        cout << "0������Ϊ����" << endl;
        exit(-1);
    }
    n_f.frac_m = this->frac_m * a.frac_c;
    n_f.frac_c = this->frac_c * a.frac_m;
    n_f.Reduction();
    return n_f;
}
//��ʾ����
void fraction::display() {
    this->Reduction();
    //����Ƿ�Ϊ�Ϸ�0
    if (this->frac_c == 0 && this->frac_m != 0)
    {
        cout << 0 ;
        return;
    }
    else
    {
        //���1
        if (this->frac_m == 1)
        {
            cout << this->frac_c;
            return;
        }
        //����ĸ
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
            cout << "0������Ϊ��ĸ" << endl;
            return;
        }
    }
}
//����>
bool fraction::operator>(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c > a_c)
        return true;
    return false;
}
//����<
bool fraction::operator<(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c < a_c)
        return true;
    return false;
}
//����>=
bool fraction::operator>=(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c >= a_c)
        return true;
    return false;
}
//����<=
bool fraction::operator<=(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c <= a_c)
        return true;
    return false;
}
//����==
bool fraction::operator==(const fraction& a) {
    int t_c = 0;
    int a_c = 0;
    t_c = this->frac_c * a.frac_m;
    a_c = this->frac_m * a.frac_c;
    if (t_c == a_c)
        return true;
    return false;
}
//����!=
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
        cout << "���������η��Ӻͷ�ĸ" << endl;
        cin >> c >> m;
        if (!cin.good())
        {
            cin.clear();
            cin.ignore(INF, '\n');
        }
        else if (m == 0)
            cout << "0������Ϊ��ĸ" << endl;
        else
            break;
    }
    fraction f(c, m), t(12, 7);
    cout << "display��" << endl;
    f.display();
    cout << endl;
    cout << "��һ���֣�" << endl;
    fraction Inv;
    cout << "Inverse��" << endl;
    Inv = f.Inverse();
    Inv.display();
    cout << endl;
    fraction Rec;
    cout << "Reciprocal��" << endl;
    Rec = f.Reciprocal();
    Rec.display();
    cout << endl;
    Sleep(1000);
    double d;
    fraction f1;
    cout << "������һ��С��" << endl;
    cin >> d;
    f1.DtoF(d);
    f1.display();
    cout << endl;
    Sleep(1000);
    string s;
    fraction f2;
    cout << "�������������ʽ������/������" << endl;
    cin >> s;
    f2.StoF(s);
    f2.display();
    cout << endl;
    Sleep(2000);
    cout << "�ڶ����֣�" << endl;
    fraction result;
    cout << "��������������������������Զ���Ϊ�ʼ����ķ�����12/7" << endl;
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
    cout << "=(��ͨ��)";
    result = f % t;
    result.display();
    cout << endl;
    Sleep(2000);
    cout << "�������֣�" << endl;
    cout << "�����������ԱȽ�����������Զ���Ϊ�ʼ����ķ�����12/7" << endl;
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
