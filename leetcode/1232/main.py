import math

num1 = 30
num2 = -20
gcd_value = math.gcd(num1, num2)
print(f"The GCD of {num1} and {num2} is: {gcd_value}")

# Example usage for more than two numbers (Python 3.9+)
numbers_list = [12, 24, 27, 30, 36]
# Use the asterisk (*) to unpack the list into arguments
gcd_of_list = math.gcd(*numbers_list)
print(f"The GCD of {numbers_list} is: {gcd_of_list}")
