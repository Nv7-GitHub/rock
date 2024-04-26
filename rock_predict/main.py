import matplotlib.pyplot as plt
from thrust import thrust

# https://math.stackexchange.com/questions/721076/help-with-using-the-runge-kutta-4th-order-method-on-a-system-of-2-first-order-od

# Constants
p = 1.24
A = 0.003425
Cd = 0.57
m = 0.552
g = 9.81
h = 0.1
P = 50
I = 0
D = 0

# Initial conditions
"""
ti = 1
xi = 66.559
vi = 98.072
"""

#"""
ti = 0
xi = 0
vi = 0
#"""

# Rocket Equations
# v(x) is dx/dt = v
# a(x) is dv/dt = 1/2*p*A*Cd*v^2/m - g + T/m

def v(v):
    return v

def a(t, v, real):
    #if (real):
        #return -(1/2)*p*A*Cd*(v)*(v)/m - g + thrust(t)*0.9/m
    return -(1/2)*p*A*Cd*v*v/m - g + thrust(t)/m

# Calculates Cd from fin angle
def cd(angle):
    if angle > 90:
        angle = 90
    if angle < 0:
        angle = 0
    global Cd
    Cd = (0.0000142*angle*angle*angle + 0.001512*angle*angle - 0.0075534*angle)*0 + 0.57

# Solve using Runge-Kutta 4th order method
def solve_iter(ti, xi, vi, real):
    k0 = h*v(vi)
    l0 = h*a(ti, vi, real)

    k1 = h*v(vi+0.5*k0)
    l1 = h*a(ti+0.5*h, vi+0.5*k0, real)

    k2 = h*v(vi+0.5*k1)
    l2 = h*a(ti+0.5*h, vi+0.5*k1, real)

    k3 = h*v(vi+k2)
    l3 = h*a(ti+h, vi+k2, real)

    return (
        xi + (1/6) * (k0 + 2*k1 + 2*k2 + k3),
        vi + (1/6) * (l0 + 2*l1 + 2*l2 + l3)
    )

def get_apogee(ti, vi, xi):
    t = ti
    #vi = vi - 3
    #xi = xi + uniform(-2, 2)
    while vi > 0 or t == 0:
        res = solve_iter(t, xi, vi, False)
        xi = res[0]
        vi = res[1]
        t += h
    #print(xi)
    return xi


t = ti
t_plt = []
x_plt = []
v_plt = []
a_plt = []
pre_plt = []
ang_plt = []
control = 0
err_i = 0
err_d = 0
while vi > 0 or t == 0:
    res = solve_iter(t, xi, vi, True)
    xi = res[0]
    vi = res[1]
    t += h

    t_plt.append(t)
    x_plt.append(xi)
    v_plt.append(vi)
    a_plt.append(a(t, vi, True))
   
    # Run controller
    if t >= 1.75:
        err = get_apogee(t, vi, xi) - 243 # 259 for 850, 243 for 800, 250 for 820
        pre_plt.append(err)

        # PID
        output = P*err + I*err_i - D*(err - err_d)/h
        err_i += err * h
        err_d = err
        control += output*h
        if control > 75:
            control = 75
        if control < 0:
            control = 0
        cd(control)
        #print(err, control)
        ang_plt.append(control)
    else:
       pre_plt.append(0)
       ang_plt.append(0)
    if (t >= 1):
       print(t, xi)
   #print(t, xi, vi)

fig, ax = plt.subplots(2, 2)
ax2 = ax[0, 0].twinx()
ax2.plot(t_plt, x_plt)
ax2.set_xlabel("Time (s)")
ax2.set_ylabel("Altitude (m)")
ax[0, 0].plot(t_plt, pre_plt, "-.", color="red")
ax[0, 0].set_ylabel("Predicted Apogee Error (m)")

ax[0, 1].plot(t_plt, v_plt)
ax[0, 1].set_xlabel("Time (s)")
ax[0, 1].set_ylabel("Velocity (m/s)")

ax[1, 0].plot(t_plt, a_plt)
ax[1, 0].plot([0, t_plt[-1]], [0, 0], "-.")
ax[1, 0].set_xlabel("Time (s)")
ax[1, 0].set_ylabel("Acceleration (m/s^2)")

ax[1, 1].plot(t_plt, ang_plt)
ax[1, 1].set_xlabel("Time (s)")
ax[1, 1].set_ylabel("Canard Angle (deg)")

fig.canvas.manager.set_window_title("Rock Predict")

plt.show()