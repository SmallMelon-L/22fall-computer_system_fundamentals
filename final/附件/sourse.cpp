#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> v0(m, 0), R(8), L(8);
    R[0] = -2; R[1] = -1; R[2] = 1; R[3] = 2; R[4] = 2; R[5] = 1; R[6] = -1; R[7] = -2;
    L[0] = 1; L[1] = 2; L[2] = 2; L[3] = 1; L[4] = -1; L[5] = -2; L[6] = -2; L[7] = -1;
    vector<vector<int> > v(n, v0);
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