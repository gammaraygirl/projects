# Prompt user for input
answer = input("What is the answer to the Great Question of Life, the Universe and Everything? ")

match answer.lower():
    case "42" | "forty-two" | "forty two":
        print("Yes")
    case _:
        print("No")
