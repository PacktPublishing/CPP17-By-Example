class Cell {
  public:
    Cell(int value, Cell* next);
    int getValue() const {return m_value;}
    Cell* getNext() const {return m_next;}

  private:
    int m_value;
    Cell* m_next;
};