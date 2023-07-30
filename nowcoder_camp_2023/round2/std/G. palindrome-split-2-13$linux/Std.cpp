#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
#define MN 1000000

using std::greater;
using std::min;
using std::priority_queue;
using std::vector;

char rev[256];

char _s[MN + 5], s[MN * 2 + 5];

bool dc(char a, char b)
{
	return b == rev[a];
}

void init()
{
	for (int i = 0; i < 256; i++)
	{
		rev[i] = 1;
	}
	rev['b'] = 'q';
	rev['d'] = 'p';
	rev['p'] = 'd';
	rev['q'] = 'b';
	rev['n'] = 'u';
	rev['u'] = 'n';
	rev['o'] = 'o';
	rev['s'] = 's';
	rev['x'] = 'x';
	rev['z'] = 'z';
	rev['#'] = '#';
}

void solve()
{
	scanf("%s", _s);
	int n = strlen(_s);
	s[0] = '$';
	for (int i = 0; i < n; i++)
	{
		s[i * 2 + 1] = '#';
		s[i * 2 + 2] = _s[i];
	}
	n = n * 2;
	s[++n] = '#';
	s[n + 1] = '\0';
	int rc = 0;
	vector<int> r(n + 1);
	int start = 1;
	for (int i = 1; i <= n; i++)
	{
		if (rc + r[rc] >= i)
		{
			r[i] = min(r[rc - (i - rc)], r[rc] - (i - rc));
		}
		else
		{
			r[i] = -1;
		}
		while (dc(s[i - r[i] - 1], s[i + r[i] + 1]))
		{
			r[i]++;
		}
		if (i + r[i] > rc + r[rc])
		{
			rc = i;
		}
		if (r[i] > 0 && i - r[i] <= start)
		{
			s[i + r[i] - 1] = '$';
			start = i + r[i];
			i = i + r[i] - 1;
		}
	}
	puts(start == n ? "Yes" : "No");
}

int main()
{
	init();
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}
