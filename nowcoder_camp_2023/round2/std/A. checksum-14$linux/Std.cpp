#include <cstdio>
#define MN 100000

using uint32 = unsigned int;

uint32 f[MN * 16 + 100];

void init(int n)
{
	for (int i = 0; i < 32; i++)
	{
		f[i] = 1u << i;
	}
	for (int i = 32; i < 32 + n * 8; i++)
	{
		f[i] ^= f[i - 6];
		f[i] ^= f[i - 9];
		f[i] ^= f[i - 10];
		f[i] ^= f[i - 16];
		f[i] ^= f[i - 20];
		f[i] ^= f[i - 21];
		f[i] ^= f[i - 22];
		f[i] ^= f[i - 24];
		f[i] ^= f[i - 25];
		f[i] ^= f[i - 27];
		f[i] ^= f[i - 28];
		f[i] ^= f[i - 30];
		f[i] ^= f[i - 31];
		f[i] ^= f[i - 32];
	}
}

uint32 x[32];
uint32 v[32];

void add(uint32 a, uint32 b)
{
	for (int i = 31; i >= 0; i--)
	{
		if (a & (1u << i))
		{
			if (x[i] == 0)
			{
				x[i] = a;
				v[i] = b;
				return;
			}
			else
			{
				a ^= x[i];
				b ^= v[i];
			}
		}
	}
}

int main()
{
	int n1, n2;
	scanf("%d%d", &n1, &n2);
	init(n1 + n2 + 4);
	uint32 target = 0;
	for (int i = 1; i <= n1; i++)
	{
		int v;
		scanf("%d", &v);
		for (int j = 7; j >= 0; j--)
		{
			if (v & (1 << j))
			{
				target ^= f[32 + n2 * 8 + 32 + (n1 - i) * 8 + j];
			}
		}
	}
	for (int i = 1; i <= n2; i++)
	{
		int v;
		scanf("%d", &v);
		for (int j = 7; j >= 0; j--)
		{
			if (v & (1 << j))
			{
				target ^= f[32 + (n2 - i) * 8 + j];
			}
		}
	}
	for (int i = 0; i < 32; i++)
	{
		add(f[32 + n2 * 8 + i] ^ (1u << i), 1u << i);
	}
	uint32 ans = 0;
	for (int i = 31; i >= 0; i--)
	{
		if (target & (1u << i))
		{
			if (x[i] == 0)
			{
				puts("-1");
				return 0;
			}
			else
			{
				target ^= x[i];
				ans ^= v[i];
			}
		}
	}
	printf("%u\n", ans);
}
