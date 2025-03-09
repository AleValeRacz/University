# Given an n * n square matrix with integer values, find the maximum length of a snake sequence.
# A snake sequence begins on the matrix's top row (coordinate (0, i), 0 <= i < n).
# Each element of the sequence, except the first one, must have a value ±1 from the previous one and be located directly below,
# or directly to the right of the previous element. For example, element (i, j) can be succeded by one of the (i, j + 1) or (i + 1, j) elements.
# Display the length as well as the sequence of coordinates for one sequence of maximum length.

def find_max_snake(matrix, n):
    def next_move(i, j, prev_value, sequence):
        if 0 <= i < n and 0 <= j < n and (prev_value is None or abs(matrix[i][j] - prev_value) == 1) :
            right = next_move(i, j+1, matrix[i][j], sequence + [(i,j)])
            down = next_move(i+1,j,matrix[i][j], sequence + [(i,j)])
            return max(right, down, key=len)
        return sequence
    max_l = 0
    max_seq = []
    i = 0
    for j in range (0,n):
        sequence = next_move(0, j, None, [])
        if len(sequence) > max_l:
            max_l = len(sequence)
            max_seq = sequence
    return max_l, max_seq

def main():
    n = 4
    matrix = [[1, 0, 3, 4],
              [2, 1, 4, 3],
              [1, 1, 2, 2],
              [3, 0, 1, 1]]
    max_l, max_seq = find_max_snake(matrix, n)
    print("maximum length:", max_l)
    print("coordinate sequence:", max_seq)
    return
main()
