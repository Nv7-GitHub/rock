import csv

ASCENT = "AeroTech_G80T.csv"

thrustcurveAscent = []
thrustcurveDescent = []
with open(ASCENT, "r") as f:
    r = csv.reader(f)
    for row in r:
        try:
            thrustcurveAscent.append((float(row[0]), float(row[1])))
        except ValueError: # Headers
            continue

DESCENT = "AeroTech_F35W.csv"
with open(DESCENT, "r") as f:
    r = csv.reader(f)
    for row in r:
        try:
            thrustcurveDescent.append((float(row[0]), float(row[1])))
        except ValueError: # Headers
            continue

def thrustAscent(ti):
    for i in range(0, len(thrustcurveAscent)):
        if ti < thrustcurveAscent[i][0]:
            if i == 0:
                return thrustcurveAscent[i][1]
        
            return ((ti - thrustcurveAscent[i-1][0])/(thrustcurveAscent[i][0] - thrustcurveAscent[i-1][0])) * (thrustcurveAscent[i][1] - thrustcurveAscent[i-1][1]) + thrustcurveAscent[i-1][1]
        
    return 0

def thrustDescent(ti):
    if ti < 0:
        return 0
    for i in range(0, len(thrustcurveDescent)):
        if ti < thrustcurveDescent[i][0]:
            if i == 0:
                return thrustcurveDescent[i][1]
        
            return ((ti - thrustcurveDescent[i-1][0])/(thrustcurveDescent[i][0] - thrustcurveDescent[i-1][0])) * (thrustcurveDescent[i][1] - thrustcurveDescent[i-1][1]) + thrustcurveDescent[i-1][1]
        
    return 0