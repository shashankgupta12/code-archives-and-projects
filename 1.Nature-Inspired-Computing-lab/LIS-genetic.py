import sys
import random
m = [[0]*3 for i in range(3)]
idx1 = 0
idx2 = 0

while not(idx1 == (len(m) - 1) and idx2 == (len(m) - 1)):
	direc = random.randint(0, 1)
	if direc == 0 and not idx1 == (len(m) - 1): 
		idx1 += 1
		m[idx1][idx2] = 1
	elif direc == 1 and not idx2 == (len(m) - 1):
		idx2 += 1
		m[idx1][idx2] = 1
	else:
		break

l = [int (i) for i in sys.argv[1:]]

n = len(l)
count = [1]*n
for i in range (1 , n):
	for j in range(0 , i):
		if l[i] > l[j] and count[i] < count[j] + 1 :
			count[i] = count[j] + 1

print(max(count))