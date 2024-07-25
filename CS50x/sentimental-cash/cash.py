# see how many quarters will fit, subtract value of quarters from cents
from cs50 import get_float

def calculate_quarters(cents):
    quarters = cents//25
    return quarters

def calculate_dimes(cents):
    dimes = cents//10
    return dimes

def calculate_nickels(cents):
    nickels = cents//5
    return nickels

def calculate_pennies(cents):
    pennies = cents
    return pennies

#define an integer to store the dollar amount
cents = 0
while cents <= 0 :
    #ask for the amount of change in dollars, check if change is greater than or equal to zero
    cents = int((get_float("Change, in dollars:")) * 100)

#calculate quarters
quarters = calculate_quarters(cents)

cents = cents % 25

#calculate dimes
dimes = calculate_dimes(cents)

cents = cents % 10

#calculate nickels
nickels = calculate_nickels(cents)

cents = cents % 5

#calculate pennies
pennies = calculate_pennies(cents)

#sum up number of coins
coins = quarters + dimes + nickels + pennies

#print results
print(f"Coins: {coins}")
