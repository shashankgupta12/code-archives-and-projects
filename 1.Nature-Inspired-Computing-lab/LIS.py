import sys
l = [int (i) for i in sys.argv[1:]]

n = len(l)
count = [1]*n
for i in range (1 , n):
	for j in range(0 , i):
		if l[i] > l[j] and count[i] < count[j] + 1 :
			count[i] = count[j] + 1

print(max(count))