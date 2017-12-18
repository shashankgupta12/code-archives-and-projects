import sys
sys.argv[0] = 0
for index, i in enumerate(sys.argv[1:]): sys.argv[index + 1] = max(int(sys.argv[index]) + int(i), 0)
print(max(sys.argv))