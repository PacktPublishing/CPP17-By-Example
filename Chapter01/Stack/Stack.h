class Stack {
  public:
    Stack();
    void push(int value);
    int top();
    void pop();
    int size() const;
    bool empty() const;

  private:
    Cell* m_firstCellPtr;
    int m_size;
};
