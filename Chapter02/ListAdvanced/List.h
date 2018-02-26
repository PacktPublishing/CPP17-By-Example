class OutOfMemoryException : public exception {
 // Empty.
};

template <class T>
class LinkedList {
  private:
    class Cell {
      private:
        Cell(const T& value, Cell* previous, Cell* next);

      public:
        const T value() const { return m_value; }
        T& value() { return m_value; }

        const Cell* previous() const { return m_previous; }
        Cell*& previous() { return m_previous; }

        const Cell* next() const { return m_next; }
        Cell*& next() { return m_next; }

        friend class LinkedList;

    private:
      T m_value;
      Cell *m_previous, *m_next;
  };

  public:
    class Iterator {
      public:
        Iterator();

      private:
        Iterator(Cell* cellPtr);

      public:
        Iterator(const Iterator& iterator);
        Iterator& operator=(const Iterator& iterator);

        bool operator==(const Iterator& iterator);
        bool operator!=(const Iterator& iterator);

        bool operator++();    // prefix: ++list
        bool operator++(int); // postfix: list++

        bool operator--();
        bool operator--(int);

        const T operator*() const;
        T& operator*();

        friend class LinkedList;

      private:
        Cell *m_cellPtr;
    };

    class ReverseIterator {
      public:
        ReverseIterator();

      private:
        ReverseIterator(Cell* cellPtr);

      public:
        ReverseIterator(const ReverseIterator& iterator);
        const ReverseIterator&
              operator=(const ReverseIterator& iterator);

        bool operator==(const ReverseIterator& iterator);
        bool operator!=(const ReverseIterator& iterator);

        bool operator++();    // prefix: ++list
        bool operator++(int); // postfix: list++

        bool operator--();
        bool operator--(int);

        const T operator*() const;
        T& operator*();

        friend class LinkedList;

      private:
        Cell *m_cellPtr;
  };

  public:
    LinkedList();
    LinkedList(const LinkedList& list);
    LinkedList& operator=(const LinkedList& list);
    ~LinkedList();
    void clear();

    int size() const {return m_size;}
    bool empty() const {return (m_size == 0);}

    bool operator==(const LinkedList& list) const;
    bool operator!=(const LinkedList& list) const;

    void add(const T& value);
    void add(const LinkedList& list);

    void insert(const Iterator& insertPosition, const T& value);
    void insert(const Iterator& insertPosition,
                const LinkedList& list);

    void erase(const Iterator& erasePosition);
    void remove(const Iterator& firstPosition,
                const Iterator& lastPosition = Iterator(nullptr));

    Iterator begin() const { return Iterator(m_firstCellPtr); }
    Iterator end() const { return Iterator(nullptr); }
    ReverseIterator rbegin() const
      {return ReverseIterator(m_lastCellPtr);}
    ReverseIterator rend() const
      { return ReverseIterator(nullptr); }

    template <class U>
    friend istream& operator>>(istream& outStream,
                               LinkedList<U>& list);

    template <class U>
    friend ostream& operator<<(ostream& outStream,
                               const LinkedList<U>& list);

  private:
    int m_size;
    Cell *m_firstCellPtr, *m_lastCellPtr;
};

template <class T>
LinkedList<T>::Cell::Cell(const T& value, Cell* previous,
                          Cell* next)
 :m_value(value),
  m_previous(previous),
  m_next(next) {
  // Empty.
}

template <class T>
LinkedList<T>::Iterator::Iterator()
 :m_cellPtr(nullptr) {
  // Empty.
} 

template <class T>
LinkedList<T>::Iterator::Iterator(Cell* cellPtr)
 :m_cellPtr(cellPtr) {
  // Empty.
} 

template <class T>
LinkedList<T>::Iterator::Iterator(const Iterator& position)
 :m_cellPtr(position.m_cellPtr) {
  // Empty.
}

template <class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator=(const Iterator& iterator) {
  m_cellPtr = iterator.m_cellPtr;
  return *this;
}

template <class T>
bool LinkedList<T>::Iterator::operator==(const Iterator& position) {
  return (m_cellPtr == position.m_cellPtr);
}

template <class T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& position) {
  return !(*this == position);
}

template <class T>
bool LinkedList<T>::Iterator::operator++() {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->next();
    return true;
  }

  return false;
}

template <class T>
bool LinkedList<T>::Iterator::operator++(int i) {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->next();
    return true;
  }

  return false;
}

template <class T>
bool LinkedList<T>::Iterator::operator--() {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->previous();
    return true;
  }

  return false;
}

template <class T>
bool LinkedList<T>::Iterator::operator--(int) {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->previous();
    return true;
  }

  return false;
}

template <class T>
const T LinkedList<T>::Iterator::operator*() const {
  return m_cellPtr->value();
}

template <class T>
T& LinkedList<T>::Iterator::operator*() {
  return m_cellPtr->value();
}

template <class T>
LinkedList<T>::ReverseIterator::ReverseIterator()
 :m_cellPtr(nullptr) {
  // Empty.
} 

template <class T>
LinkedList<T>::ReverseIterator::ReverseIterator(Cell* currCellPtr)
 :m_cellPtr(currCellPtr) {
  // Empty.
} 

template <class T>
LinkedList<T>::ReverseIterator::ReverseIterator(const ReverseIterator& position)
 :m_cellPtr(position.m_cellPtr) {
  // Empty.
}

template <class T>
const typename LinkedList<T>::ReverseIterator& LinkedList<T>::ReverseIterator::operator=(const ReverseIterator& position) {
  m_cellPtr = position.m_cellPtr;
  return *this;
}

template <class T>
bool LinkedList<T>::ReverseIterator::operator==
                           (const ReverseIterator& position) {
  return (m_cellPtr == position.m_cellPtr);
}

template <class T>
bool LinkedList<T>::ReverseIterator::operator!=
                           (const ReverseIterator& position) {
  return !(*this == position);
}

template <class T>
bool LinkedList<T>::ReverseIterator::operator++() {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->previous();
    return true;
  }

  return false;
}

template <class T>
bool LinkedList<T>::ReverseIterator::operator++(int) {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->previous();
    return true;
  }

  return false;
}

template <class T>
bool LinkedList<T>::ReverseIterator::operator--() {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->next();
    return true;
  }

  return false;
}

template <class T>
bool LinkedList<T>::ReverseIterator::operator--(int) {
  if (m_cellPtr != nullptr) {
    m_cellPtr = m_cellPtr->next();
    return true;
  }

  return false;
}

template <class T>
const T LinkedList<T>::ReverseIterator::operator*() const {
  return m_cellPtr->value();
}

template <class T>
T& LinkedList<T>::ReverseIterator::operator*() {
  return m_cellPtr->value();
}

template <class T>
LinkedList<T>::LinkedList()
 :m_size(0),
  m_firstCellPtr(nullptr),
  m_lastCellPtr(nullptr) {
  // Empty.
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
  *this = list;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
  m_size = 0;
  m_firstCellPtr = nullptr;
  m_lastCellPtr = nullptr;

  if (list.m_size > 0) {
    for (Cell *listCellPtr = list.m_firstCellPtr,
              *nextCellPtr = list.m_lastCellPtr->next();
         listCellPtr != nextCellPtr;
         listCellPtr = listCellPtr->next()) {
      Cell *newCellPtr = new Cell(listCellPtr->value(),
                                  m_lastCellPtr, nullptr);
      
      if (newCellPtr == nullptr) {
        throw OutOfMemoryException();
      }

      if (m_firstCellPtr == nullptr) {
        m_firstCellPtr = newCellPtr;
      }
      else {
        m_lastCellPtr->next() = newCellPtr;
      }

      m_lastCellPtr = newCellPtr;
      ++m_size;
    }
  }

  return *this;
}

template <class T>
LinkedList<T>::~LinkedList() {
  clear();
}

template <class T>
void LinkedList<T>::clear() {
  Cell* currCellPtr = m_firstCellPtr;

  while (currCellPtr != nullptr) {
    Cell* deleteCellPtr = currCellPtr;
    currCellPtr = currCellPtr->next();
    delete deleteCellPtr;
  }

  m_size = 0;
  m_firstCellPtr = nullptr;
  m_lastCellPtr = nullptr;
}

template <class T>
bool LinkedList<T>::operator==(const LinkedList<T>& list) const {
  if (m_size != list.m_size) {
    return false;
  }

  for (Iterator thisIterator = begin(), listIterator = list.begin();
       thisIterator != end(); ++thisIterator, ++listIterator) {
    if (*thisIterator != *listIterator) {
      return false;
    }
  }

  return true;
}

template <class T>
bool LinkedList<T>::operator!=(const LinkedList<T>& list) const {
  return !(*this == list);
}

template <class T>
void LinkedList<T>::add(const T& value) {
  Cell* newCellPtr = new Cell(value, m_lastCellPtr, nullptr);

  if (newCellPtr == nullptr) {
    throw OutOfMemoryException();
  }

  if (m_lastCellPtr == nullptr) {
    m_firstCellPtr = newCellPtr;
    m_lastCellPtr = newCellPtr;
  }
  else {
    m_lastCellPtr->next() = newCellPtr;
    m_lastCellPtr = newCellPtr;
  }

  ++m_size;
}

template <class T>
void LinkedList<T>::add(const LinkedList<T>& list) {
  for (Cell *listCellPtr = list.m_firstCellPtr;
       listCellPtr != nullptr; listCellPtr = listCellPtr->next()){
    const T& value = listCellPtr->value();
    Cell *newCellPtr = new Cell(value, m_lastCellPtr, nullptr);

    if (m_lastCellPtr == nullptr) {
      m_firstCellPtr = newCellPtr;
    }
    else {      
      m_lastCellPtr->next() = newCellPtr;
    }

    m_lastCellPtr = newCellPtr;
  }

  m_size += list.m_size;
}

template <class T>
void LinkedList<T>::insert(const Iterator& insertPosition,
                           const LinkedList<T>& list) {
  if (insertPosition.m_cellPtr == nullptr) {
    add(list);
  }
  else {
    Cell *insertCellPtr = insertPosition.m_cellPtr;

    Cell *firstInsertCellPtr = nullptr,
         lastInsertCellPtr = nullptr;
    for (Cell *listCellPtr = list.m_firstCellPtr;
         listCellPtr != nullptr;listCellPtr=listCellPtr->next()) {
      double value = listCellPtr->value();
      Cell *newCellPtr =
        new Cell(value, lastInsertCellPtr, nullptr);

      if (firstInsertCellPtr == nullptr) {
        firstInsertCellPtr = newCellPtr;
      }
      else {
        lastInsertCellPtr->next() = newCellPtr;
      }

      lastInsertCellPtr = newCellPtr;
    }

    if (firstInsertCellPtr != nullptr) {
      if (insertCellPtr->previous() != nullptr) {
        insertCellPtr->previous()->next() = firstInsertCellPtr;
        firstInsertCellPtr->previous() =
          insertCellPtr->previous();
      }
      else {
        m_firstCellPtr = firstInsertCellPtr;
      }
    }

    if (lastInsertCellPtr != nullptr) {
      lastInsertCellPtr->next() = insertCellPtr;
      insertCellPtr->previous() = lastInsertCellPtr;
    }

    m_size += list.m_size;
  }
}

/*
template <class T>
void LinkedList<T>::insert(const Iterator& insertPosition,
                        const LinkedList<T>& list) {
  if (insertPosition.m_cellPtr == nullptr) {
    add(list);
  }
  else {
    Cell* insertCellPtr = insertPosition.m_cellPtr;

    Cell* firstInsertCellPtr = nullptr, lastInsertCellPtr = nullptr;
    for (Cell* listCellPtr = list.m_firstCellPtr; listCellPtr != nullptr;
         listCellPtr = listCellPtr->next()) {
      double value = listCellPtr->value();
      Cell *newCellPtr = new Cell(value, lastInsertCellPtr, nullptr);

      if (firstInsertCellPtr == nullptr) {
        firstInsertCellPtr = newCellPtr;
      }
      else {
        lastInsertCellPtr->next() = newCellPtr;
      }

      lastInsertCellPtr = newCellPtr;
    }

    if (firstInsertCellPtr != nullptr) {
      if (insertCellPtr->previous() != nullptr) {
        insertCellPtr->previous()->next() = firstInsertCellPtr;
        firstInsertCellPtr->previous() = insertCellPtr->previous();
      }
      else {
        m_firstCellPtr = firstInsertCellPtr;
      }
    }

    if (lastInsertCellPtr != nullptr) {
      lastInsertCellPtr->next() = insertCellPtr;
      insertCellPtr->previous() = lastInsertCellPtr;
    }

    m_size += list.m_size;
  }
}
*/

template <class T>
void LinkedList<T>::erase(const Iterator& removePosition) {
  remove(removePosition, removePosition);
}

template <class T>
void LinkedList<T>::remove(const Iterator& firstPosition,
           const Iterator& lastPosition /*= Iterator(nullptr)*/) {
  Cell *firstCellPtr = firstPosition.m_cellPtr,
      *lastCellPtr = lastPosition.m_cellPtr;
  lastCellPtr = (lastCellPtr == nullptr)
                ? m_lastCellPtr : lastCellPtr;

  Cell *previousCellPtr = firstCellPtr->previous(),
      *nextCellPtr = lastCellPtr->next();

  Cell *currCellPtr = firstCellPtr;
  while (currCellPtr != nextCellPtr) {
    Cell *deleteCellPtr = currCellPtr;
    currCellPtr = currCellPtr->next();
    delete deleteCellPtr;
    --m_size;
  }

  if (previousCellPtr != nullptr) {
    previousCellPtr->next() = nextCellPtr;  
  }
  else {
    m_firstCellPtr = nextCellPtr;
  }

  if (nextCellPtr != nullptr) {
    nextCellPtr->previous() = previousCellPtr;
  }
  else {
    m_lastCellPtr = previousCellPtr;
  }
}

template <class T>
istream& operator>>(istream& inStream, LinkedList<T>& list) {
  int size;
  inStream >> size;

  for (int count = 0; count < size; ++count) {
    T value;
    inStream >> value;
    list.add(value);
  }

  return inStream;
}

template <class T>
ostream& operator<<(ostream& outStream, const LinkedList<T>& list){
  outStream << "[";

  bool first = true;
  for (const T& value : list) {
    outStream << (first ? "" : ",") << value;
    first = false;
  }

  outStream << "]";
  return outStream;
}