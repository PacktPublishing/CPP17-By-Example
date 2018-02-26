class Car {
  public:
    Car();
    Car(int speed, int direction);

    int getSpeed() const;
    int getDirection() const;

    void accelerate(int speed);
    void decelerate(int speed);

    void turnLeft(int degrees);
    void turnRight(int degrees);

    ~Car();

  private:
    int m_speed, m_direction;
};