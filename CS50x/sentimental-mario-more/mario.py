from cs50 import get_string

height = 0
while height <1 or height>8:
    height = int(get_string("Height:"))

for i in range(height):
    print((" " * (height - i)) + ("#" * i) + " " + ("#" * i) + " " * (height - i) )

