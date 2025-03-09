# 14. Determine the `n-th` element of the sequence `1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,...` obtained from the sequence of natural numbers by replacing composed numbers with their prime divisors, each divisor `d` being written `d` times, without memorizing the elements of the sequence.

def prime(p):
    for d in range(2, p // 2 + 1):
        if p % d == 0:
            return False
    return True


# increase the index for every prime divisor and return the last divisor, or 0 if the number is prime
def get_prime_divisors(nb, i, n):
    last_divisor = 0
    for d in range(2, nb // 2 + 1):
        if nb % d == 0 and prime(d):
            i += d
            last_divisor = d
        if i >= n:
            break
    return i, last_divisor


def main():
    n = int(input("enter number for n:"))
    if n < 1:
        print("n is not a valid number")
        return
    i = 0
    number = 0
    result = 0
    while i < n:
        number += 1
        # j is the increased i and result becomes the last divisor
        j, result = get_prime_divisors(number, i, n)
        # if the number is prime
        if result == 0:
            result = number
            i += 1
        else:
            i = j
    print(result)


main()
