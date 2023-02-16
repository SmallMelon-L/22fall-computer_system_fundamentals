#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int s[64];
int R[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int L[] = {1, 2, 2, 1, -1, -2, -2, -1};
int v[8][8] = {0};
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i != n + 4; i++)
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
    }
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
                    return 0;
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