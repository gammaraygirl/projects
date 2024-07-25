# Define convert function
def convert(input):
    if ":)" in input:
        input = input.replace(":)", "🙂")
    if ":(" in input:
        input = input.replace(":(", "🙁")
    print(input)

def main():
    phrase = input("")
    convert(phrase)
main()
