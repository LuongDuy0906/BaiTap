#include <iostream>
using namespace std;

class MT
{
private:
    int m;
    int n;
    float a[10][10];

public:
    MT()
    {
        m = 1;
        n = 1;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = 0;
    }

    friend ostream &operator<<(ostream &os, const MT &x)
    {
        for (int i = 1; i <= x.m; i++)
        {
            for (int j = 1; j <= x.n; j++)
                os << x.a[i][j] << " ";
            os << "\n";
        }
        return os;
    }

    friend istream &operator>>(istream &is, MT &x)
    {
        cout << "Nhap so hang :";
        is >> x.m;
        cout << "Nhap so cot :";
        is >> x.n;
        for (int i = 1; i <= x.m; i++)
            for (int j = 1; j <= x.n; j++)
            {
                cout << "Nhap phan tu hang " << i << ", cot " << j << " : ";
                is >> x.a[i][j];
            }
        return is;
    }

    MT operator+(MT x2)
    {
        if (m != x2.m || n != x2.n)
        {
            cout << "Khong thuc hien duoc phep cong ma tran \n";
            return x2;
        }
        else
        {
            MT x3;
            x3.m = x2.m;
            x3.n = x2.n;
            for (int i = 1; i <= m; i++)
                for (int j = 1; j <= n; j++)
                {
                    x3.a[i][j] = a[i][j] + x2.a[i][j];
                }

            return x3;
        }
    }

    MT operator-(MT x2)
    {
        if (m != x2.m || n != x2.n)
        {
            cout << "Khong thuc hien duoc phep tru ma tran \n";
            return x2;
        }
        else
        {
            MT x3;
            x3.m = x2.m;
            x3.n = x2.n;
            for (int i = 1; i <= m; i++)
                for (int j = 1; j <= n; j++)
                {
                    x3.a[i][j] = a[i][j] - x2.a[i][j];
                }

            return x3;
        }
    }

    MT operator*(MT x2)
    {
        if (this->n != x2.m)
        {
            cout << "Khong nhan duoc 2 ma tran \n";
            return x2;
        }
        else
        {
            MT x3;
            x3.m = m;
            x3.n = x2.n;
            for (int i = 1; i <= m; i++)
                for (int j = 1; j <= n; j++)
                {
                    x3.a[i][j] = 0;
                    for (int k = 1; k <= x2.m; k++)
                        x3.a[i][j] += a[i][k] * x2.a[k][j];
                }
            return x3;
        }
    }
};

int main()
{
    MT d, b, c, e, f;
    cin >> c >> b;
    d = c + b;
    e = c - b;
    f = c * b;
    cout << "Tong 2 ma tran :\n"
         << d;
    cout << "Hieu 2 ma tran :\n"
         << e;
    cout << "Tich 2 ma tran :\n"
         << f;

    return 0;
}
