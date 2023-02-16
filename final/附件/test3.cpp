#include <iostream>
#include <stack>
#include <vector>
#include <ctime>
#include <cstdio>
using namespace std;
int R[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int L[] = {1, 2, 2, 1, -1, -2, -2, -1};
int v[8][8] = {0};
int s[64];
void sourse(int n, int m)
{
    for(int i = 0; i != n; i++)
    {
        for(int j = 0; j != m; j++)
        {
            v[i][j] = 0;
        }
    }
    v[n - 1][0] = 1;
    int r = n - 1, l = 0;
    int top = 0;
    while (top != m * n - 1)
    {
        int next = 0, rn = r + R[next], ln = l + L[next];
        while (!(rn >= 0 && rn < n && ln >= 0 && ln < m) || v[rn][ln])
        {
            next++;
            while (next == 8)
            {
                int last;
                if (top == 0)
                {
                    cout << "QAQ";
                    return;
                }
                last = s[top - 1];
                top--;
                v[r][l] = 0;
                r -= R[last];
                l -= L[last];
                next = last + 1;
            }
            rn = r + R[next];
            ln = l + L[next];
        }
        s[top++] = next;
        r = rn;
        l = ln;
        v[r][l] = top + 1;
    }
    for (int i = 0; i != n; i++)
    {
        for (int j = 0; j != m; j++)
        {
            cout << v[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    int N[] = {4, 7, 8, 6};
    int M[] = {8, 7, 8, 8};
    double t[4];
    clock_t begin, end;
    int n, m;
    for(int a = 0; a != 4; a++)
    {
        n = N[a];
        m = M[a];
        begin = clock();
        sourse(n, m);
        end = clock();
        t[a] = double(end - begin) / CLOCKS_PER_SEC * 1000;
    }
    printf("N\t");
    for(int i = 0; i != 4; i++)
    {
        printf("%d\t\t", N[i]);
    }
    putchar('\n');
    printf("M\t");
    for(int i = 0; i != 4; i++)
    {
        printf("%d\t\t", M[i]);
    }
    putchar('\n');
    printf("time\t");
    for(int i = 0; i != 4; i++)
    {
        printf("%f\t", t[i]);
    }
    putchar('\n');
}