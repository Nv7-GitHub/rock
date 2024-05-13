import csv

time = []
vel = []
alt = []
accel = []
angle = []
error = []

DATA = "flight.csv"
with open(DATA, "r") as f:
    r = csv.reader(f)
    for row in r:
        try:
            time.append(float(row[0])/1000)
            accel.append(float(row[2]))
            vel.append(float(row[3]))
            alt.append(float(row[4]))
            angle.append(90-float(row[7]))
            error.append(float(row[17]))
        except ValueError: # Headers
            continue
