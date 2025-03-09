import random
def printMenu():
    print("1.Generate a list of n random natural numbers. Generated numbers must be between 0 and 100.")
    print("2.Sort the list using bogo sort")
    print("3.Sort the list using comb sort")
    print("4.Exit the program")

def generate_list(n):
    rand_list = []
    for i in range(n):
        rand_list.append(random.randint(0, 100))
    return rand_list

def is_sorted(a):
    n = len(a)
    for i in range(0, n-1):
        if (a[i] > a[i+1]):
            return False
    return True

def shuffle(a):
    n = len(a)
    for i in range(0, n):
        r = random.randint(0, n-1)
        a[i], a[r] = a[r], a[i]

def bogoSort(a, step):
    n = len(a)
    pass_number = 0
    while (is_sorted(a) == False):
        shuffle(a)
        pass_number += 1
        if pass_number % step == 0:
            print(f"Pass {pass_number}: {a}")


def getNextGap(gap):
    gap = int(gap * 10 / 13)
    if gap < 1:
        return 1
    return gap

def combSort(a, step):
    n = len(a)
    gap = n
    swapped = True
    pass_number = 0
    while gap != 1 or swapped:
        gap = getNextGap(gap)
        swapped = False
        for i in range(0, n - gap):
            if a[i] > a[i + gap]:
                a[i], a[i + gap] = a[i + gap], a[i]
                swapped = True
        pass_number += 1
        if pass_number % step == 0:
            print(f"Pass {pass_number}: {a}")

def main():
    rand_list = []
    while True:
        printMenu()
        choice = int(input("chose option:"))
        if choice == 1:
            n = int(input("Enter n: "))
            rand_list = generate_list(n)
            print(rand_list)
        elif choice == 2:
            if not rand_list:
                print("Generate a list first")
            else:
                step = int(input("Enter the step: "))
                bogoSort(rand_list.copy(), step)
        elif choice == 3:
            if not rand_list:
                print("Generate a list first")
            else:
                step = int(input("Enter the step:  "))
                combSort(rand_list.copy(), step)
        elif choice == 4:
            print("You have exited")
            return
        else:
            print("Invalid choice")

main()
