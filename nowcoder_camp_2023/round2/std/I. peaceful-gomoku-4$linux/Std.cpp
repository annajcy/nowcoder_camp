#include <cstdio>
#define MN 1000

const int rb[5] = {0, 2, 4, 1, 3};
const int rw[5] = {1, 3, 0, 2, 4};

char s[MN + 5][MN + 5];

void solve()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int cx = (n * m + 1) / 2;
	int co = n * m / 2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			s[i][j] = '\0';
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (j % 5 == rb[i % 5])
			{
				s[i][j] = 'x';
				cx--;
			}
			if (j % 5 == rw[i % 5])
			{
				s[i][j] = 'o';
				co--;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (s[i][j] == '\0')
			{
				if (cx > 0)
				{
					s[i][j] = 'x';
					cx--;
				}
				else if (co > 0)
				{
					s[i][j] = 'o';
					co--;
				}
				else
				{
					puts("[Error] Too few piece.");
				}
			}
			putchar(s[i][j]);
		}
		putchar('\n');
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}
