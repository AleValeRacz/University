import math

#The function converts a complex number written in string into its real and imaginary parts, and returns them
def transform_complex_number(z):
    numbers = z.replace(" ", "")
    nr_plus = numbers.count('+')
    nr_minus = numbers.count('-')
    if nr_plus == 1:
        numbers = numbers.split('+')
    elif nr_minus == 2:
        numbers = numbers.split('-',2)
        numbers[0] = '-' + numbers[1]
        numbers[1] = '-' + numbers[2]
    elif nr_minus == 1:
         numbers = numbers.split('-')
         if not numbers[0]:
             if 'i' in numbers[1]:
                 numbers[0] = '0'
                 numbers[1] = '-' + numbers[1]
             else:
                 numbers[0] = '-' + numbers[1]
                 numbers[1] = '0'
         else:
            numbers[1] = '-' + numbers[1]
    elif 'i' in numbers:
        if numbers == 'i':
            numbers = ['0', '1']
        elif numbers == '-i':
            numbers = ['0', '-1']
        else:
            numbers = ['0', numbers]
    else:
        numbers = [numbers, '0']
    real = float(numbers[0])
    imaginary = float(numbers[1].rstrip('i'))
    return real, imaginary

#The function puts the real and imaginary parts of a given number into a list, and returns the list
def create_complex_number_list(z):
    return list(transform_complex_number(z))

#The function puts the real and imaginary parts of a given number into a dictionary, and returns the dictionary
def create_complex_number_dictionary(z):
    real, imag = transform_complex_number(z)
    return {'real': real, 'imaginary':imag}


def get_real_part(z):
    number = create_complex_number_dictionary(z)
    return number['real']


def get_imag_part(z):
    number = create_complex_number_dictionary(z)
    return number['imaginary']

def get_real_part(z):
    number = create_complex_number_list(z)
    return number[0]

def get_imag_part(z):
    number = create_complex_number_list(z)
    return number[1]



def transform_to_string(z):
    real = get_real_part(z)
    imaginary = get_imag_part(z)
    if imaginary >= 0:
        return str(real) + " + " + str(imaginary) + "i"
    else:
        return str(real) + " - " + str(abs(imaginary)) +'i'

def is_prime(n):
    if int(n) != n or n <= 1:
        return False
    n = int(n)
    for d in range(2, n//2+1):
        if n % d == 0:
            return False
    return True

def modulus(a,b):
    return math.sqrt(a*a + b*b)

def set_A(array):
    """
    Specifications:
    Parameter: a given list of complex numbers
    The function returns the length and a list with the elements of a subarray of numbers where
    the difference between the modulus of consecutive elements is a prime number
    """
    current_subarray = []
    current_subarray.append(array[0])
    current_len = 1
    max_len = 0
    max_subarray = []
    for i in range(1, len(array)):
        if is_prime(abs(modulus(get_real_part(array[i]), get_imag_part(array[i])) - modulus(get_real_part(array[i - 1]), get_imag_part(array[i - 1])))):
                current_len += 1
                current_subarray.append(array[i])
        else:
            current_len = 1
            current_subarray = []
            current_subarray.append(array[i])

        if current_len >= max_len:
            max_len = current_len
            max_subarray = current_subarray
    return max_len, max_subarray

def set_B(array):
    """
    Specifications:
    Parameter: a given list of complex numbers
    The function returns the length of a subarray that has a maximum sum, and the subarray itself
    """
    current_sum = get_real_part(array[0])
    max_sum = current_sum
    current_subarray = [array[0]]
    max_subarray = [array[0]]
    for i in range(1,len(array)):
        if get_real_part(array[i]) > current_sum + get_real_part(array[i]):
            current_sum = get_real_part(array[i])
            current_subarray = [array[i]]
        else:
            current_sum = current_sum + get_real_part(array[i])
            current_subarray.append(array[i])
        if current_sum > max_sum:
            max_sum = current_sum
            max_subarray = current_subarray.copy()

    return len(max_subarray), max_subarray

def enter_complex_numbers():
    array = input("Enter a list of complex numbers separated by commas: ").split(',')
    return [z.strip() for z in array]

def display_list(list):
    new_list = [transform_to_string(z) for z in list]
    print(new_list)

def display_set_A(list):
    a, b = set_A(list)
    print(a,b)

def display_set_B(list):
    a, b = set_B(list)
    print (a,b)

def print_menu():
    print("1.Read a list of complex numbers (in `z = a + bi` form) from the console")
    print("2.Display the entire list of numbers on the console.")
    print("3a.Display the length and elements of a longest subarray of numbers where the difference between the modulus of consecutive numbers is a prime number.")
    print("3b. Display the length and elements of a maximum subarray sum, when considering each number's real part.")
    print("4.Exit the application")


def main():
    list_of_numbers = []
    hardwired_list = ["i", "4 - 3i", "-3", "-8 + 15i", "8 - 6i", "-4 - 3i", "12 + 5i", "4", "20i", "-15 -8i"]
    menu_options = {
        '1': enter_complex_numbers,
        '2': display_list,
        '3a': display_set_A,
        '3b': display_set_B,
        }
    while True:
        print_menu()
        print()
        choice = input("Enter an option based on what you want to do (1, 2, 3a, 3b, 4):")
        print()
        if choice in menu_options:
            if choice == '1':
                choice_2 = input("Do you want to use predefined list (chose 1) or enter a new one (chose 2)?")
                if choice_2 == '1':
                        list_of_numbers = hardwired_list.copy()
                elif choice_2 == '2':
                        list_of_numbers = menu_options[choice]()
                else:
                        print("Invalid choice.Please chose a valid option.")
            else:
                if not list_of_numbers:
                    print("Please enter a list of complex numbers first.")
                    print()
                else:
                    menu_options[choice](list_of_numbers)
        elif choice == '4':
            print("Exiting application.")
            return
        else:
            print("Invalid choice.Please try again  by entering one of the valid options (1, 2, 3a, 3b, 4)")

main()
