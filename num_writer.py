import random
import sys
#creates a file filled with random integers on each line for n body simulations
#format(args): filename, left boundary, right boundary, number of elements to create.
f = open(sys.argv[1], 'w')
random.seed()
start = int(sys.argv[2])
end = int(sys.argv[3])
size = int(sys.argv[4])
i = 0
while(i < size):
	i += 1	
	f.write(str(random.randint(start, end)) + " ")
	f.write(str(random.randint(start, end))+ " ")
	f.write(str(0) + " ")
	f.write(str(0) + " ")
	f.write(str(random.randint(0, end)) + "\n")
