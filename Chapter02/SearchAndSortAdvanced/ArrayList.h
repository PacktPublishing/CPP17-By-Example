class ArrayList {
  public:
    class Iterator {
      public:
        Iterator();

      private:
        Iterator(ArrayList* listPtr, int index);
        Iterator(const ArrayList* listPtrConst, int index);

      public:
        Iterator(const Iterator& position);
        Iterator& operator=(const Iterator& position);

        bool operator==(const Iterator& position);
        bool operator!=(const Iterator& position);

        const double value() const
              { return m_listPtrConst->operator[](m_index); }
        double& value() { return m_listPtr->operator[](m_index); }

        bool hasPrevious() const;
        Iterator& eraseAndPrevious();
        Iterator& previous();

        bool hasNext() const;
        Iterator& eraseAndNext();
        Iterator& next();

        friend class ArrayList;

      private:
        ArrayList* m_listPtr;
        const ArrayList* m_listPtrConst;
        int m_index;
  };

  public:
    ArrayList();
    ArrayList(const ArrayList& list);
    ArrayList& operator=(const ArrayList& list);

  private:
    static void copy(const ArrayList& list, ArrayList& result,
                     int startIndex, int size);

  public:
    ~ArrayList();

    int size() const {return m_size;}
    bool empty() const {return (m_size == 0);}

    double operator[](int index) const;
    double& operator[](int index);

    bool operator==(const ArrayList& list) const;
    bool operator!=(const ArrayList& list) const;
    bool operator<(const ArrayList& list) const;
    bool operator<=(const ArrayList& list) const;
    bool operator>(const ArrayList& list) const;
    bool operator>=(const ArrayList& list) const;

    void add(const double& value);
    void add(const ArrayList& list);

    void insert(const Iterator &position, const double& value)
         {insert(position.m_index, value);}
    void insert(int insertIndex, const double& value);

    void insert(const Iterator &position, const ArrayList& list)
         {insert(position.m_index, list);}
    void insert(int insertIndex, const ArrayList& list);

    void erase(const Iterator &position) {erase(position.m_index);}
    void erase(int eraseIndex);

    void remove(const Iterator &firstPosition,
                const Iterator &lastPosition = EndPosition)
        {remove(firstPosition.m_index, lastPosition.m_index);}
    void remove(int firstIndex, int lastIndex = -1);

    ArrayList slice(const Iterator &firstPosition,
                    const Iterator &lastPosition = EndPosition) const
             {return slice(firstPosition.m_index, lastPosition.m_index);}
    ArrayList slice(int firstIndex, int lastIndex = -1) const;

    void split(ArrayList& left, int index, ArrayList& right) const;

    Iterator begin() const { return Iterator(this, 0); }
    Iterator end() const { return Iterator(this, m_size - 1); }

    const Iterator const_begin() const { return Iterator(this, 0); }
    const Iterator const_end() const { return Iterator(this, m_size - 1); }

    friend ostream& operator<<(ostream& out, const ArrayList& list);
    static const Iterator EndPosition;

  private:
    int min(int a, int b) const { return (a < b) ? a : b; }
    int max(int a, int b) const { return (a > b) ? a : b; }

  private:
    int m_size;
    double* m_buffer;
};
