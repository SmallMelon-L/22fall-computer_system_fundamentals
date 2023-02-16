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