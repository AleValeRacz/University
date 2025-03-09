import random
import time


def printMenu():
    print("1.Generate a list of n random natural numbers. Generated numbers must be between 0 and 100.")
    print("2.Sort the list using bogo sort")
    print("3.Sort the list using comb sort")
    print("4.Best case")
    print("5.Average case")
    print("6.Worst case")
    print("7.Exit the program")

def generate_list(n):
    rand_list = []
    for i in range(n):
        rand_list.append(random.randint(0, 101))
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
        if step != -1:
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
        if step != -1:
            if pass_number % step == 0:
                print(f"Pass {pass_number}: {a}")

def generate_5_lists(n):
    five_lists = []
    i = 0
    for i in range(5):
        five_lists.append(generate_list(n))
        n = n * 2
    return five_lists
def timer_bogo(five_lists, n):
    step = -1
    for i in range(5):
        start = time.time()
        bogoSort(five_lists[i],step)
        end = time.time()
        print(f"Time taken for list {i + 1}: {end-start} seconds")
def timer_comb(five_lists, n):
    step = -1
    for i in range(5):
        start = time.time()
        combSort(five_lists[i],step)
        end = time.time()
        print(f"Time taken for list {i + 1}: {end-start} seconds")

def main():
    rand_list = []
    while True:
        printMenu()
        i = 0
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
            n = int(input("Enter n: "))
            five_lists = generate_5_lists(n)
            for i in range(5):
                five_lists[i] = sorted(five_lists[i])
            option = int(input("Choose the sorting algorithm (1 is bogo sort, 2 is comb sort): "))
            if option == 1:
                timer_bogo(five_lists, n)
            elif option == 2:
                timer_comb(five_lists, n)
            else:
                print("Invalid choice")
        elif choice == 5:
            n = int(input("Enter n: "))
            five_lists = generate_5_lists(n)
            option = int(input("Choose the sorting algorithm (1 is bogo sort, 2 is comb sort): "))
            if option == 1:
                timer_bogo(five_lists, n)
            elif option == 2:
                timer_comb(five_lists, n)
            else:
                print("Invalid choice")
        elif choice == 6:
            n = int(input("Enter n: "))
            five_lists = generate_5_lists(n)
            option = int(input("Choose the sorting algorithm (1 is bogo sort, 2 is comb sort): "))
            if option == 1:
                timer_bogo(five_lists, n)
            elif option == 2:
                for i in range(5):
                    five_lists[i] = sorted(five_lists[i],reverse = True)
                timer_comb(five_lists, n)
            else:
                print("Invalid choice")
        elif choice == 7:
            print("You have exited")
            return
        else:
            print("Invalid choice")

main()
