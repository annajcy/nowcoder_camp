n = int(input().strip())
s = []
for i in range(n):
	s.append(input().strip())
nosol = 2 * n
diffx, diffy = 0, 0
for i in range(n):
	cur = 0
	for j in range(n):
		if s[i][j] != s[0][j]:
			cur += 1
	if cur == n:
		diffx += 1
	if cur != 0 and cur != n:
		nosol = -1
for j in range(n):
	cur = 0
	for i in range(n):
		if s[i][j] != s[i][0]:
			cur += 1
	if cur == n:
		diffy += 1
	if cur != 0 and cur != n:
		nosol = -1
diffx = min(diffx, n - diffx)
diffy = min(diffy, n - diffy)
print(min(nosol, diffx + diffy))