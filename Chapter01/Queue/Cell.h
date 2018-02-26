class Cell {
  public:
    Cell(int value, Cell* next);
    int value() const {return m_value;}
    Cell* getNext() const { return m_next; }
    void setNext(Cell* next) { m_next = next; }

  private:
    int m_value;
    Cell* m_next;
};
