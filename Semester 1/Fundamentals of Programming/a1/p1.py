# 2. Given natural number `n`, determine the prime numbers `p1` and `p2` such that `n = p1 + p2` (check the Goldbach hypothesis).

# We make a function for finding out if a number is prime or not
def prime(p):
    for d in range(2, p // 2 + 1):
        if p % d == 0:
            return False
    return True


# Find the pair of prime numbers, and return 0,0 if there is none
def pairs(n):
    for p1 in range(2, n // 2 + 1):
        p2 = n - p1
        if prime(p1) and prime(p2):
            return p1, p2
    return 0, 0


def main():
    n = int(input("enter number for n: "))
    if n > 1:
        p1, p2 = pairs(n)
        if p1 != 0 and p2 != 0:
            print(f"p1={p1} p2={p2}")
        else:
            print("There are no such numbers")
    else:
        print("There are no such numbers")


main()
