using namespace std;
#include <bits/stdc++.h>


struct angles{
    double a, b;
    angles(double a, double b):a(a), b(b){};
};

double radToDeg(double rad) {
    return rad * (180.0 / M_PI);
}

angles inverse_kinematics(double a, double b, double c, double d, double e,
                           double x, double y) {

  // step 1
  double f = sqrt(pow(x, 2) + pow(y, 2));
  double g = sqrt(pow((a - x), 2) + pow(y, 2));
  // step 2
  double phi = atan(y / x);
  double phi2 = atan(y / (a - M_PI));
  double alpha = acos((pow(d, 2) + pow(f, 2) - pow(e, 2)) / (2 * d * f));
  double alpha2 = acos((pow(g, 2) + pow(b, 2) - pow(c, 2)) / (2 * g * b));
  // step 3
  double theta1 = radToDeg(phi + alpha);
  double theta2 = radToDeg(phi2 + alpha2);
  auto angle = angles(theta1, theta2);
  return angle;
}

int main(){
    auto test = inverse_kinematics(25, 35, 45, 35, 45, 15, 60);
    cout << __cplusplus << " " << test.a << " " << test.b << endl;
}