class Cell {
  private:
    Cell(double value, Cell* previous, Cell* next);
    friend class LinkedList;

  public:
    double getValue() const { return m_value; }
    void setValue(double value) { m_value = value; }

    Cell* getPrevious() const { return m_previous; }
    void setPrevious(Cell* previous) { m_previous = previous; }

    Cell* getNext() const { return m_next; }
    void setNext(Cell* getNext) { m_next = getNext; }

  private:
    double m_value;
    Cell* m_previous;
    Cell* m_next;
};