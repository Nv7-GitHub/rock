import matplotlib.pyplot as plt
from thrust import thrust

# https://math.stackexchange.com/questions/721076/help-with-using-the-runge-kutta-4th-order-method-on-a-system-of-2-first-order-od

# Constants
p = 1.24
A = 0.003425
Cd = 0.57
m = 0.552
g = 9.81
h = 1/100

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

def a(t, v):
    return -(1/2)*p*A*Cd*v*v/m - g + thrust(t)/m

# Solve using Runge-Kutta 4th order method
def solve_iter(ti, xi, vi):
    k0 = h*v(vi)
    l0 = h*a(ti, vi)

    k1 = h*v(vi+0.5*k0)
    l1 = h*a(ti+0.5*h, vi+0.5*k0)

    k2 = h*v(vi+0.5*k1)
    l2 = h*a(ti+0.5*h, vi+0.5*k1)

    k3 = h*v(vi+k2)
    l3 = h*a(ti+h, vi+k2)

    return (
        xi + (1/6) * (k0 + 2*k1 + 2*k2 + k3),
        vi + (1/6) * (l0 + 2*l1 + 2*l2 + l3)
    )

t = ti
t_plt = []
x_plt = []
v_plt = []
a_plt = []
while vi > 0 or t == 0:
   res = solve_iter(t, xi, vi)
   xi = res[0]
   vi = res[1]
   t += h

   t_plt.append(t)
   x_plt.append(xi)
   v_plt.append(vi)
   a_plt.append(a(t, vi))

   print(t, xi, vi)

fig, (ax1, ax2, ax3) = plt.subplots(3)
ax1.plot(t_plt, x_plt)
ax1.set_xlabel("Time (s)")
ax1.set_ylabel("Altitude (m)")

ax2.plot(t_plt, v_plt)
ax2.set_xlabel("Time (s)")
ax2.set_ylabel("Velocity (m/s)")

ax3.plot(t_plt, a_plt)
ax3.plot([0, t_plt[-1]], [0, 0], "-.")
ax3.set_xlabel("Time (s)")
ax3.set_ylabel("Acceleration (m/s^2)")

fig.canvas.manager.set_window_title("Rock Predict")

plt.show()