#include "cpu.h"

using namespace std;

int main()
{
	vector<char> ctx;//code
	read(ctx);
	printf("[");
	run(ctx);
	printf("]");
}