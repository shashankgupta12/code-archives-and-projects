import random
import math

def ackley(x):
	sqrsum = sum([i**2 for i in x])
	cosi = sum([math.cos(2*3.14*i) for i in x])
	fx = 20 - 20*math.exp(-0.2*math.sqrt(sqrsum/len(x))) + math.exp(1) - math.exp(cosi/len(x))
	return fx

def optimize():
	bestfitness = 9999
	N = 10

	for i in range(3000):
		
		x = [random.randint(-15, 30) for _ in range(10)]
		fitness = ackley(x)
		
		# x = [0]*10
		print(x)
		print(fitness)
		
		if fitness < bestfitness:
			bestfitness = fitness
			bestparam = x

	return (bestfitness, bestparam)

print(optimize())