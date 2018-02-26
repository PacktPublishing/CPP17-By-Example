template <class T>
class Set : private LinkedList<T> {
  public:
    typedef LinkedList<T>::Iterator Iterator;

    Set();
    Set(const T& value);
    Set(const Set& set);
    Set& operator=(const Set& set);
    ~Set();

    bool operator==(const Set& set) const;
    bool operator!=(const Set& set) const;

    int size() const { return LinkedList<T>::size(); }
    bool empty() const { return LinkedList<T>::empty(); }

    Iterator begin() const { return LinkedList<T>::begin(); }
    Iterator end() const { return LinkedList<T>::end(); }

    Set operator+(const Set& set) const;
    Set operator*(const Set& set) const;
    Set operator-(const Set& set) const;

    template <class U>
    friend Set<U>
      merge(const Set<U>& leftSet, const Set<U>& rightSet,
            bool addLeft, bool addEqual, bool addRight);

    Set& operator+=(const Set& set);
    Set& operator*=(const Set& set);
    Set& operator-=(const Set& set);

    template <class U>
    friend istream& operator>>(istream& inStream, Set<U>& set);

    template <class U>
    friend ostream& operator<<(ostream& outStream,
                               const Set<U>& set);
};

template <class T>
Set<T>::Set() {
  // Empty.
}

template <class T>
Set<T>::Set(const T& value) {
  add(value);
}

template <class T>
Set<T>::Set(const Set& set)
 :LinkedList(set) {
  // Empty.
}

template <class T>
Set<T>::~Set() {
  // Empty.
}

template <class T>
Set<T>& Set<T>::operator=(const Set& set) {
  clear();
  add(set);
  return *this;
}

template <class T>
bool Set<T>::operator==(const Set& set) const {
  return LinkedList::operator==(set);
}

template <class T>
bool Set<T>::operator!=(const Set& set) const {
  return !(*this == set);
}

template <class T>
Set<T> Set<T>::operator+(const Set& set) const {
  return merge(*this, set, true, true, true);
}

template <class T>
Set<T> Set<T>::operator*(const Set& set) const {
  return merge(*this, set, false, true, false);
}

template <class T>
Set<T> Set<T>::operator-(const Set& set) const {
  return merge(*this, set, true, false, false);
}

template <class T>
Set<T> merge(const Set<T>& leftSet, const Set<T>& rightSet,
             bool addLeft, bool addEqual, bool addRight) {
  Set<T> result;
  Set<T>::Iterator leftIterator = leftSet.begin(),
                   rightIterator = rightSet.begin();
  
  while ((leftIterator != leftSet.end()) &&
         (rightIterator != rightSet.end())) {
    if (*leftIterator < *rightIterator) {
      if (addLeft) {
        result.add(*leftIterator);
      }

      ++leftIterator;
    }
    else if (*leftIterator > *rightIterator) {
      if (addRight) {
        result.add(*rightIterator);
      }

      ++rightIterator;
    }
    else {
      if (addEqual) {
        result.add(*leftIterator);
      }

      ++leftIterator;
      ++rightIterator;
    }
  }

  if (addLeft) {
    while (leftIterator != leftSet.end()) {
      result.add(*leftIterator);
      ++leftIterator;
    }
  }

  if (addRight) {
    while (rightIterator != rightSet.end()) {
      result.add(*rightIterator);
      ++rightIterator;
    }
  }

  return result;
}

template <class T>
Set<T>& Set<T>::operator+=(const Set& set) {
  *this = *this + set;
  return *this;
}

template <class T>
Set<T>& Set<T>::operator*=(const Set& set) {
  *this = *this * set;
  return *this;
}

template <class T>
Set<T>& Set<T>::operator-=(const Set& set) {
  *this = *this - set;
  return *this;
}

template <class T>
istream& operator>>(istream& inStream, Set<T>& set) {
  int size;
  inStream >> size;

  for (int count = 0; count < size; ++count) {
    T value;
    inStream >> value;
    set += value;
  }

  return inStream;
}

template <class T>
ostream& operator<<(ostream& outStream, const Set<T>& set) {
  outStream << "{";
  bool first = true;

  for (const T& value : set) {
    outStream << (first ? "" : ",") << value;
    first = false;
  }

  outStream << "}";
  return outStream;
}