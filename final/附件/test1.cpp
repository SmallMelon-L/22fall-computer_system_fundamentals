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
    stack<int> s;
    while (s.size() != m * n - 1)
    {
        int next = 0;
        while (!(r + R[next] >= 0 && r + R[next] < n && l + L[next] >= 0 && l + L[next] < m) || v[r + R[next]][l + L[next]])
        {
            next++;
            while (next == 8)
            {
                int last;
                if (s.size() == 0)
                {
                    cout << "QAQ";
                    return;
                }
                last = s.top();
                s.pop();
                v[r][l] = 0;
                r -= R[last];
                l -= L[last];
                next = last + 1;
            }
        }
        s.push(next);
        r += R[next];
        l += L[next];
        v[r][l] = s.size() + 1;
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