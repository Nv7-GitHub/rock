float target; // Input

const float Kp = 50; // Use 10 if mass is 560ish
const float Ki = 0;
const float Kd = 0;
const float START = 1.75;

// Prediction variables
const float h = 0.1; // Time step
const float p = 1.24; // Density of air
const float A = 0.003425; // Reference area
const float g = 9.81; // Gravity

// User-entered
const float m = 0.572; // Mass of rocket (kg)
const float goal = 259.08 + 1.524; // Altitude target (m), 259.08 for flight comp 1, 243.84 for flight comp 2
float Cd = 0.57;

float integral = 0;
float prevE = 0;
float angle = 0;
extern double dT;
void resetControl() {
  prevE = 0;
  integral = 0;
  angle = 0;
}

void loopControl() {
  // Get input
  float currTime = ((float)flightTime())/1000.0;
  float e = getApogee(currTime, getAlt(), getVel()) - goal;
  target = e;
  if (currTime < START) {
    e = 0; // ENABLE after 3 seconds
  }

  // Calculate PID
  float p = Kp * e;
  integral += Ki * e * dT;
  float d = (Kd * (e - prevE))/dT;
  float res = p + integral + d;
  angle += res * dT;
  if (angle < 0) {
    angle = 0;
  } else if (angle > 75) {
    angle = 75;
  }
  Cd = calcCd(angle);

  if (currTime < START) {
    angle = 5;
  }

  // Write servos
  writeS2((int)(90.0-angle));
  writeS3((int)(90.0-angle));

  // Store for next iter
  prevE = e;
}

// Runge-kutta 4th order method (see rock_predict for more)
struct IterResult {
  float x;
  float v;
};

float calcCd(float inp) {
  return (0.0000142*inp*inp*inp + 0.001512*inp*inp - 0.0075534*inp)*0.2 + 0.57;
}

float calcAccel(float t, float v) {
  return -(1.0/2.0)*p*A*Cd*v*v/m - g;
}

struct IterResult solveIter(float ti, float xi, float vi) {
  float k0 = h*vi;
  float l0 = h*calcAccel(ti, vi);

  float k1 = h*(vi+0.5*k0);
  float l1 = h*calcAccel(ti+0.5*h, vi+0.5*k0);

  float k2 = h*(vi+0.5*k1);
  float l2 = h*calcAccel(ti+0.5*h, vi+0.5*k1);

  float k3 = h*(vi+k2);
  float l3 = h*calcAccel(ti+h, vi+k2);

  struct IterResult result;
  result.x = xi + (1.0/6.0) * (k0 + 2*k1 + 2*k2 + k3);
  result.v = vi + (1.0/6.0) * (l0 + 2*l1 + 2*l2 + l3);
  return result;
}

float getApogee(float ti, float xi, float vi) {
  float t = ti;
  while (vi > 0 || t == 0) {
    IterResult res = solveIter(t, xi, vi);
    xi = res.x;
    vi = res.v;
    t += h;
  }
  return xi;
}