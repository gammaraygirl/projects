# E = mc^2 E is joules, m is mass in kg, and c is 299,792,458 m/s
def einstein():
    # Define variables
    E = None
    c = 300000000 

    # Prompt for input
    mass = float(input("m: "))

    E = int(mass * ((c)**2))
    print(f"E: {E}")

einstein()
