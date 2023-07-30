#include <cstdio>

void solve()
{
	int n, a, b, c;
	scanf("%d%d%d%d", &n, &a, &b, &c);
	if (n % 2 == 0)
	{
		puts("Alice");
	}
	else
	{
		puts((a + b + c) & 1 ? "Bob" : "Alice");
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}
