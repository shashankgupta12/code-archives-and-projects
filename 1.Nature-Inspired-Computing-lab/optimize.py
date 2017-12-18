import random

def objective(x):
	su = 0
	pr = 1
	for i in x:
		su += abs(i)
		pr *= abs(i)
	return su + pr


def optimize():
	bestparam = []
	bestfitness = 50
	result = 0
	for i in range(1000):
		x = random.sample(range(-10,11),10)
		fitness = objective(x)
		if fitness < bestfitness:
			bestparam = x
			result = fitness
	return result

print(optimize())

# print(objective([-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]))