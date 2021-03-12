#include <iostream>
using namespace std;

struct A
{
    int *xp[10];
    int d[5];
    int *k;
};

struct B
{
    A *xt;
    B *r;
};

B *task1(int num)
{
    B *p;
    p = new B;
    p->xt = new A;
    p->xt->k = new int[20];

    for (int i = 0; i < 20; i++)
        p->xt->k[i] = 1;

    if (num-- != 1)
        p->r = task1(num);

    return p;
}

B *task2(int num)
{
    B *p;
    p = new B;
    p->xt = new A;

    for (int i = 0; i < 10; i++)
    {
        p->xt->xp[i] = new int;
        *(p->xt->xp[i]) = 1;
    }

    if (num-- != 1)
        p->r = task2(num);

    return p;
}

int main()
{
    B *h, *p, *t, g[50];

    // 1.B
    h = task1(100);

    // 1.Г
    h = task2(100);
    return 0;
}
