import random

def repair(m):
	
	idx1 = 0
	idx2 = 0

	while not(idx1 == (len(m) - 1) and idx2 == (len(m) - 1)):
		if not m[idx1 + 1][idx2] == 1 and not m[idx1][idx2 + 1] == 1:
			direc = random.randint(0, 1)
			if direc == 0 and not idx1 == (len(m) - 1): 
				idx1 += 1
				m[idx1][idx2] = 1
			elif direc == 1 and not idx2 == (len(m) - 1):
				idx2 += 1
				m[idx1][idx2] = 1
		else:
			break
	return m

def crossover(m):
	m[0], m[len(m) - 1] = m[len(m) - 1], m[0]
	return m

def mutation(m):
	mrate = 0.04
	mrate = (len(m)**2) * mrate
	mrate = round(mrate)
	for _ in range(mrate):
		x = random.randint(0, len(m))
		y = random.randint(0, len(m))
		m[x][y] = 0 if m[x][y] == 1 else 1 
	return m

def maxSum(l, dim):
	_max = 0

	m = [[0]*dim for i in range(dim)]
	m[0][0] = 1
	
	idx1 = 0
	idx2 = 0
	
	for _ in range(1000):

		while not(idx1 == (dim - 1) and idx2 == (dim - 1)):
			direc = random.randint(0, 1)
			if direc == 0 and not idx1 == (dim - 1): 
				idx1 += 1
				m[idx1][idx2] = 1
			elif direc == 1 and not idx2 == (dim - 1):
				idx2 += 1
				m[idx1][idx2] = 1
		
		_sum = 0
		for i in range(dim):
			for j in range(dim):
				if m[i][j] == 1:
					_sum += l[i][j]


		_max = max(_max, _sum)
		
		m = crossover(m)
		m = mutation(m)
		m = repair(m)
		
		idx1 = 0
		idx2 = 0

	return _max

l = [[3, 11, 12], [8, 18, 19], [-1, 2, -5]]
b = maxSum(l, len(l[0]))
print(b)