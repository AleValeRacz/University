# 6. Determine a calendar date (as year, month, day) starting from two integer numbers representing the year and the day number inside that year (e.g. day number 32 is February 1st). Take into account leap years. Do not use Python's inbuilt date/time functions.

# We create a list with the months of the year in order
MONTH_NAMES = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October",
               "November", "December"]


# We get the name of "i"th month
def calc_month(i):
    if i < 0 or i > len(MONTH_NAMES):
        return "error"
    return MONTH_NAMES[i]


# Check if the year is leap or not
def leap_year(year):
    if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
        return True
    return False


def main():
    year = int(input("enter year:"))
    day = int(input("enter day:"))
    is_leap_year = leap_year(year)
    if not is_leap_year and day > 365 or day > 366 or day < 1:
        print("Day outside of range")
        return
    # Construct a list with the number of days in each month, taking into account if it's a leap year
    if is_leap_year:
        month_days = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    else:
        month_days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    # For each month, subbtract the number of days until it is less than 0
    for i in range(0, len(month_days)):
        day -= month_days[i]
        if day <= 0:
            # Print the results, adding back the month_days
            print(year, calc_month(i), day + month_days[i])
            break


main()
