import random
import math
from functools import reduce
import operator

def objective(x):
	return sum(x)

def initialize():
	genes = 10
	chromosomes = 100 # population size
	return [[random.randint(1, 10) for _ in range(genes)] for _ in range(chromosomes)]

def evaluate(population):
	return [objective(x) for x in population]

def repair(population):
	for i in range(len(population)):
		for j in range(len(population[0])):
			if population[i][j] < 1:
				population[i][j] = 1 
			elif population[i][j] > 10:
				population[i][j] = 10
	return population

def mutation(mutationRate, population):
	mutationPerGeneration = round(mutationRate*len(population)*len(population[0]))
	chromo = [random.choice(range(len(population)-5)) for _ in range(mutationPerGeneration)] # to prevent selecting the same element again and again for mutation
	gene = [random.choice(range(len(population[0]))) for _ in range(mutationPerGeneration)] # to prevent selecting the same element again and again for mutation
	for i in range(mutationPerGeneration):
		population[chromo[i]][gene[i]] = random.randint(1, 10)
	return population	

def heuristic(parentsForCrossover):
	fitness1 = objective(parentsForCrossover[0])
	fitness2 = objective(parentsForCrossover[1])
	bestParent = parentsForCrossover[0] if fitness1>fitness2 else parentsForCrossover[1]
	worstParent = parentsForCrossover[0] if fitness1<fitness2 else parentsForCrossover[1]
	r = random.uniform(0, 1)
	sub = list(map(operator.sub, bestParent, worstParent))
	offspring1 = list(map(operator.add, bestParent, [i*r for i in sub]))
	offspring2 = bestParent
	return (offspring1, offspring2)

def onePoint(parentsForCrossover):
	parent1 = parentsForCrossover[0]
	parent2 = parentsForCrossover[1]
	offspring1 = parent1[:5] + parent2[5:]
	offspring2 = parent2[:5] + parent1[5:]
	return (offspring1, offspring2)

def crossover(crossoverRate, population):# one-point crossover
	newPopulation = []
	crossoverPerGeneration = round((crossoverRate*len(population))/2)
	for _ in range(crossoverPerGeneration):
		parentsForCrossover = random.sample(population, 2)
		population.remove(parentsForCrossover[0])
		population.remove(parentsForCrossover[1])
		offsprings = heuristic(parentsForCrossover) # method for crossover
		newPopulation.append(offsprings[0])
		newPopulation.append(offsprings[1])

	newPopulation.extend(population)
	return newPopulation

def selection(population, fitnessList):
	newPopulation = []
	probFitness = [i/sum(fitnessList) for i in fitnessList]
	expectedCount = [i*len(population) for i in probFitness]
	actualCount = [round(i) + 1 for i in expectedCount] # check that population size remains constant after this step
	# this actual count calculation is not working properly, therefore 1 has been added
	while(len(newPopulation)<=100):
		maximum = max(actualCount)
		idx = actualCount.index(maximum)
		for _ in range(maximum):
			newPopulation.append(population[idx])
		actualCount.remove(maximum)
	return newPopulation

def optimize(crossoverRate, mutationRate):
	population = initialize()
	fitnessList = evaluate(population)

	for _ in range(1000):
		population = selection(population, fitnessList)
		population = crossover(crossoverRate, population)
		population = mutation(mutationRate, population)
		population = repair(population) # most important function because heuristic crossover produces out of range offsprings
		fitnessList = evaluate(population)

	return fitnessList

if __name__ == '__main__':
	fitlist = optimize(0.5, 0.04)
	print(fitlist)
	print(max(fitlist))