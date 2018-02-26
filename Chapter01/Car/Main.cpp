#include <IOStream>
using namespace std;
#include "Car.h"

void main() {
  Car redVolvo;
  cout << "Red Volvo Speed: " << redVolvo.getSpeed() << " miles/hour"
       << ", Direction: " << redVolvo.getDirection() << " degrees" << endl;

  redVolvo.accelerate(30);
  redVolvo.turnRight(30);
  cout << "Red Volvo Speed: " << redVolvo.getSpeed() << " miles/hour"
       << ", Direction: " << redVolvo.getDirection() << " degrees" << endl;

  redVolvo.decelerate(10);
  redVolvo.turnLeft(10);
  cout << "Red Volvo Speed: " << redVolvo.getSpeed() << " miles/hour"
       << ", Direction: " << redVolvo.getDirection() << " degrees" << endl;

  const Car blueFiat(100, 90);
  cout << "Blue Fiat Speed: " << blueFiat.getSpeed() << " miles/hour"
       << ", Direction: " << blueFiat.getDirection() << " degrees"
       << endl;
}
