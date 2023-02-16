#include <iostream>
#include <stack>
#include <vector>
#include <ctime>
#include <cstdio>
using namespace std;
int R[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int L[] = {1, 2, 2, 1, -1, -2, -2, -1};
int v[12][12] = {0};
int s[64];
void sourse(int n, int m)
{
    clock_t begin, end;
    begin = clock();
    for(int k = 0; k != 1000; k++)
    {
    for(int i = 2; i != n + 2; i++)
    {
        for(int j = 2; j != m + 2; j++)
        {
            v[i][j] = 0;
        }
    }
    /*a*/
    for(int i = 0; i != n + 4; i++)
    {
        v[i][0] = -1;
    }
    for(int i = 0; i != n + 4; i++)
    {
        v[i][1] = -1;
    }
    for(int i = 0; i != n + 4; i++)
    {
        v[i][m + 2] = -1;
    }
    for(int i = 0; i != n + 4; i++)
    {
        v[i][m + 3] = -1;
    }
    for(int i = 0; i != m + 4; i++)
    {
        v[0][i] = -1;
    }
    for(int i = 0; i != m + 4; i++)
    {
        v[1][i] = -1;
    }
    for(int i = 0; i != m + 4; i++)
    {
        v[n + 2][i] = -1;
    }
    for(int i = 0; i != m + 4; i++)
    {
        v[n + 3][i] = -1;
    }
    /*b*/
    /*for(int i = 0; i != n + 4; i++)
    {
        v[i][0] = -1;
        v[i][1] = -1;
        v[i][m + 2] = -1;
        v[i][m + 3] = -1;
    }
    for(int i = 0; i != m + 4; i++)
    {
        v[0][i] = -1;
        v[1][i] = -1;
        v[n + 2][i] = -1;
        v[n + 3][i] = -1;
    }*/
    }
    end = clock();
    cout << "initial time\t" << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
    return;
    v[n + 1][2] = 1;
    int r = n + 1, l = 2;
    int top = 0;
    while (top != m * n - 1)
    {
        int next = 0, rn = r + R[next], ln = l + L[next];
        while (v[rn][ln])
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
    for (int i = 2; i != n + 2; i++)
    {
        for (int j = 2; j != m + 2; j++)
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
    begin = clock();
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
    end = clock();
    cout << "outputtime\t" << double(end - begin) / CLOCKS_PER_SEC * 1000 << endl;
}