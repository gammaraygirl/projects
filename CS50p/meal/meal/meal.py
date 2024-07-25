def main():
    time = input("What time is it? ")
    converted_time = None
    converted_time = convert(time)
      # Check against conditions
    if converted_time >= 7 and converted_time <= 8:
        print("breakfast time")
    elif converted_time >= 12 and converted_time <= 13:
        print("lunch time")
    elif converted_time >= 18 and converted_time <= 19:
        print("dinner time")

def convert(time):
    hours = None
    minutes = None
    time = time.lower()
    time = time.strip()

    # Check if string contains a.m. or p.m.
    if time.endswith("p.m."):
        # Remove "p.m"
        time = time.replace("p.m.","")
        # Split into hours and minutes
        hours, minutes = time.split(":")
        minutes = float(minutes)
        hours = float(hours)

        # Check for noon case, add 12 if not true
        if hours != 12:
            hours = hours + 12

        # Convert minutes to hours
        minutes = minutes/60

        # Add minutes and hours
        converted_time = hours + minutes

    elif time.endswith("a.m."):
        # Remove "a.m"
        time = time.replace("a.m.","")
        # Split into hours and minutes
        hours, minutes = time.split(":")
        minutes = float(minutes)
        hours = float(hours)

        # Check for midnight case
        if hours == 12:
              hours = 0

        # Convert minutes to hours
        minutes = minutes/60

        # Add minutes and hours
        converted_time = hours + minutes
    else:
        hours, minutes = time.split(":")
        minutes = float(minutes)
        hours = float(hours)

        # Convert minutes to hours
        minutes = minutes/60

        # Add minutes and hours
        converted_time = hours + minutes

    return converted_time

if __name__ == "__main__":

    main()
