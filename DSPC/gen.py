import sys
from random import randrange, random
eSize = 0 #32767

def gen_matrix(size):
    matrix = []
    for i in range(size):
        row = []
        for j in range(size):
            #rand_num = randrange(1,size+1)
            rand_num = random()
            row.append(rand_num)
        # ensure diagonal dominance here:
        row[i] = sum(row) + 1
        matrix.append(row)
    return matrix


def get_random_solution(size):
    solution = []
    for i in range(size):
        #rand_num = randrange(1,size+1)
        rand_num = random()
        solution.append(rand_num)
    return solution


if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Usage: python gen_diag_dominant_matrix.py <size>\n")
        sys.exit()

    size = int(sys.argv[1])
    fname = r"C:\Users\Z\source\repos\DSPC\DSPC\matrix.txt"

    matrix = gen_matrix(size)
    solution = get_random_solution(size)

    outfile = open(fname, 'w')

    for row in matrix:
        outfile.write(' '.join(map(str,row)))
        outfile.write('\n')
    
    #outfile.write("Solution\n")
    outfile.write(', '.join(map(str,solution)))
    outfile.write("\n")
    outfile.close()