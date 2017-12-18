def maxSum(l, dim):
	position = maximum = 0
	for idx1, i in enumerate(l):
		for idx2, j in enumerate(l[idx1]):

			if not idx1 - 1 < 0 and not idx2 - 1 < 0:
				position = max(j + l[idx1 - 1][idx2], j + l[idx1][idx2 - 1], 0)
			
			elif not idx1 - 1 < 0 and idx2 - 1 < 0:
				position = max(j + l[idx1 - 1][idx2], 0)
			
			elif idx1 - 1 < 0 and not idx2 - 1 < 0:
				position = max(j + l[idx1][idx2 - 1], 0)

			elif idx1 - 1 < 0 and idx2 - 1 < 0:
				position = j
			
			l[idx1][idx2] = position
			maximum = max(maximum, position)
	
	return maximum

l = [[3, 11, 12], [8, 18, 19], [-1, 2, -5]]
b = maxSum(l, len(l[0]))
print(b)