import random
import statistics
from heapq import nsmallest
from decimal import *

def obj(a, b, c, d):
	LOC_given = [10, 17, 10, 24, 10, 10, 10, 15, 10, 10, 17, 11, 15, 15, 13]
	
	TDEV_given = [13, 12, 15, 18, 13, 14, 15, 13, 12, 12, 22, 19, 18, 19, 21]
	TDEV_calculated = [Decimal(Decimal(c) * Decimal(pow(Decimal(a) * Decimal(pow(loc, b)), Decimal(d)))) for loc in LOC_given]

	TDEV = Decimal(sum([(g - c)/g for g, c in zip(TDEV_given, TDEV_calculated)])/15)
	return float('%.2f'%TDEV)

max_iter = 3

# for j in range(9):
# 	for k in range(9):
# 		for l in range(9):

a = [float('%.2f'%random.uniform(0, 2)) for _ in range(10)]
b = [float('%.2f'%random.uniform(0.5, 1.5)) for _ in range(10)]
c = [float('%.2f'%random.uniform(0, 2)) for _ in range(10)]
d = [float('%.2f'%random.uniform(0.5, 1.5)) for _ in range(10)]

for current_iter in range(max_iter):
	
	fx = [obj(_a, _b, _c, _d) for _a, _b, _c, _d in zip(a, b, c, d)]
	small1, small2, small3 = [fx.index(value) for value in nsmallest(3, fx)]

	alpha = a[small1], b[small1], c[small1], d[small1]	
	beta = a[small2], b[small2], c[small2], d[small2]
	delta = a[small3], b[small3], c[small3], d[small3]

	C = 2*random.random()
	A1 = 2 - 2*((current_iter + 1)/max_iter)
	A2 = 2*A1*random.random() - A1

	for index, coefficients in enumerate(zip(a, b, c, d)):
		
		D_alpha = [abs(C*alpha[i] - coefficients[i]) for i in range(4)]
		D_beta = [abs(C*beta[i] - coefficients[i]) for i in range(4)]
		D_delta = [abs(C*delta[i] - coefficients[i]) for i in range(4)]
		
		X1 = [(alpha[i] - A2*D_alpha[i]) for i in range(4)]
		X2 = [(beta[i] - A2*D_beta[i]) for i in range(4)]
		X3 = [(delta[i] - A2*D_delta[i]) for i in range(4)]

		a[index] = float('%.2f'%random.uniform(0, 2)) if float('%.2f'%((X1[0] + X2[0] + X3[0])/3)) < 0 else float('%.2f'%((X1[0] + X2[0] + X3[0])/3))
		b[index] = float('%.2f'%random.uniform(0.5, 1.5)) if float('%.2f'%((X1[1] + X2[1] + X3[1])/3)) < 0 else float('%.2f'%((X1[1] + X2[1] + X3[1])/3))
		c[index] = float('%.2f'%random.uniform(0, 2)) if float('%.2f'%((X1[2] + X2[2] + X3[2])/3)) < 0 else float('%.2f'%((X1[2] + X2[2] + X3[2])/3))
		d[index] = float('%.2f'%random.uniform(0.5, 1.5)) if float('%.2f'%((X1[3] + X2[3] + X3[3])/3)) < 0 else float('%.2f'%((X1[3] + X2[3] + X3[3])/3))

		# a[index], b[index], c[index], d[index] = [abs(float('%.2f'%((X1[i] + X2[i] + X3[i])/3))) for i in range(4)]

	DT = Decimal(Decimal(alpha[2]) * Decimal(pow(Decimal(alpha[0]) * Decimal(pow(14, alpha[1])), Decimal(alpha[3]))))
	DT = float('%.2f'%DT)
	
	# if current_iter == (max_iter - 1):
	# 	# if DT >= 18 and DT <= 22:
	# 		# print('Alpha: {} {}'.format(alpha, DT))
	print('Alpha: {} {}'.format(alpha, DT))
		