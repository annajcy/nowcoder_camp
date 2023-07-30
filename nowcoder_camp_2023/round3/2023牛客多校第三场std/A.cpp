#include <cstdio>

using namespace std;

long long x, y;

long long readll()
{
	char c = 0;
	long long r = 0;
	while (c < '0')
		scanf("%c", &c);
	while ('0' <= c && c <= '1')
	{
		r = r * 2 + c - '0';
		scanf("%c", &c);
	}
	return r;
}

int main()
{
	x = readll();
	y = readll();
	if (x == y)
	{
		printf("0\n");
		return 0;
	}
	if (x == 0)
	{
		printf("-1\n");
		return 0;
	}
	printf("%lld\n", x > y ? x - y : y - x);
	return 0;
}