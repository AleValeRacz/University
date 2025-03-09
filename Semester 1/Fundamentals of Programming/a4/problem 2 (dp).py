#Given an n * n square matrix with integer values, find the maximum length of a snake sequence.
#A snake sequence begins on the matrix's top row (coordinate (0, i), 0 <= i < n).
# Each element of the sequence, except the first one, must have a value ±1 from the previous one and be located directly below,
# or directly to the right of the previous element. For example, element (i, j) can be succeded by one of the (i, j + 1) or (i + 1, j) elements.
# Display the length as well as the sequence of coordinates for one sequence of maximum length.

def find_max_snake(matrix, n):
    dp = [[1 for i in range(n)] for i in range(n)]
    max_l, max_i, max_j = 1, 0, 0
    for i in range(n):
        for j in range(n):
            if i > 0 and abs(matrix[i][j] - matrix[i-1][j]) == 1:
                dp[i][j] = max(dp[i][j], dp[i-1][j]+1)
            if j >= 0 and abs(matrix[i][j] - matrix[i][j-1]) == 1:
                dp[i][j] = max(dp[i][j], dp[i][j-1]+1)
            if dp[i][j] > max_l:
                max_l = dp[i][j]
                max_i, max_j = i, j
    sequence = [(max_i, max_j)]
    while max_l > 1:
        if max_i > 0 and dp[max_i][max_j] == dp[max_i - 1][max_j] + 1:
            max_i -= 1
        else:
            max_j -= 1
        sequence.append((max_i, max_j))
        max_l -= 1
    sequence.reverse()
    return len(sequence), sequence
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
