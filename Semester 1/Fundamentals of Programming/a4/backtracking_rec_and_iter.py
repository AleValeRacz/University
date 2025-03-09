#Two natural numbers m and n are given. Display in all possible modalities the numbers from 1 to n,
# such that between any two numbers on consecutive positions,
# the difference in absolute value is at least m. If there is no solution, display a message.


def backtracking_recursive(array,n,m,ok):
    if len(array) == n:
        ok = 1
        print(array)

    for i in range(1,n+1):
        if i not in array and (len(array) == 0 or abs(array[-1] - i) >= m):
            array.append(i)
            ok = backtracking_recursive(array,n, m,ok)
            array.pop()
    return ok
def main():
    n = int(input("Give value for n:"))
    m = int(input("give value for m:"))
    ok = 0
    if backtracking_recursive([],n,m,ok) == 0:
        print("no solution")
    return
main()

def backtracking_iterative(n, m):
    stack = [([], 1)]
    ok = 0
    while stack:
        array, number = stack.pop()
        if len(array) == n:
            ok = 1
            print(array)
            continue
        for new_number in range(1,n+1):
            if new_number not in array and (not array or abs(new_number - array[-1])>= m):
                new_array = array + [new_number]
                stack.append((new_array,new_number))
    if ok == 0:
        print("no solution")

def main2():
    n = int(input("Give value for n:"))
    m = int(input("give value for m:"))
    backtracking_iterative(n, m)
    return
main2()
