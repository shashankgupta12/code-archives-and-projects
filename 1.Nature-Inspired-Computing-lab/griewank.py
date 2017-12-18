import random
import math

def griewank(x):
	sqrsum = sum([i**2 for i in x])
	cosi = reduce(lambda x, y: x*y, [math.cos(i/math.sqrt(index + 1)) for index, i in enumerate(x)])
	fx = (sqrsum/4000) - cosi + 1
	return fx

def optimize():
	bestfitness = 9999
	N = 10

	for i in range(3000):
		
		x = [random.randint(-600, 600) for _ in range(10)]
		# x = [0]*10
		fitness = griewank(x)
		
		print(x)
		print(fitness)

		if fitness < bestfitness:
			bestfitness = fitness
			bestparam = x
		
	return (bestfitness, bestparam)

print(optimize())