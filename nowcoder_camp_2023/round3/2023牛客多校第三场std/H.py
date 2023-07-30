n = int(input())
s = sum(map(int, input().split()))
p = lambda x : x > 1 and sum(1 if x % i == 0 else 0 for i in range(2, int(x ** 0.5) + 1)) == 0
if n == 1:
	print('Yes' if p(s) else 'No')
if n == 2:
	print('Yes' if s >= 4 and (s % 2 == 0 or p(s - 2)) else 'No')
if n > 2:
	print('Yes' if s >= 2 * n else 'No')