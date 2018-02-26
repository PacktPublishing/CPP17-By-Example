class Iterator {
  private:
    Iterator(Cell* cellPtr);

  public:
    Iterator();
    Iterator(const Iterator& iterator);

    double getValue() { return m_cellPtr->getValue(); }
    void setValue(double value) { m_cellPtr->setValue(value); }

    bool hasNext() const { return (m_cellPtr != nullptr); }
    void next() { m_cellPtr = m_cellPtr->getNext(); }

    bool hasPrevious() const { return (m_cellPtr != nullptr); }
    void previous() { m_cellPtr = m_cellPtr->getPrevious(); }

    friend class LinkedList;

  private:
    Cell* m_cellPtr;
};
