import csv

FILE = "AeroTech_F67W.csv"

thrustcurve = []
with open(FILE, "r") as f:
    r = csv.reader(f)
    for row in r:
        try:
            thrustcurve.append((float(row[0]), float(row[1])))
        except ValueError: # Headers
            continue

def thrust(ti):
    for i in range(0, len(thrustcurve)):
        if ti < thrustcurve[i][0]:
            if i == 0:
                return thrustcurve[i][1]
        
            return ((ti - thrustcurve[i-1][0])/(thrustcurve[i][0] - thrustcurve[i-1][0])) * (thrustcurve[i][1] - thrustcurve[i-1][1]) + thrustcurve[i-1][1]
        
    return 0