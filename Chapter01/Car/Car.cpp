#include "Car.h"

Car::Car()
 :m_speed(0),
  m_direction(0) {
  // Empty.
}

Car::Car(int speed, int direction)
 :m_speed(speed),
  m_direction(direction) {
  // Empty.
}

Car::~Car() {
  // Empty.
}

int Car::getSpeed() const {
  return m_speed;
}

int Car::getDirection() const {
  return m_direction;
}

void Car::accelerate(int speed) {
  m_speed += speed;
}

void Car::decelerate(int speed) {
  m_speed -= speed;
}

void Car::turnLeft(int degrees) {
  m_direction -= degrees;
}

void Car::turnRight(int degrees) {
  m_direction += degrees;
}
