#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
int main()
{
	FILE *a, *b;
	a = fopen("my.cpp", "r");
	b = fopen("ans.cpp", "r");
	long long int i;
	for(i = 0; 1; i++)
	{
		char c, d;
		c = fgetc(a);
		d = fgetc(b);
		if(c == -1)
		{
			break;
		}
		if(c != d)
		{
			cout << i << ' ';
		}
	}
	cout << "great " << i;
}