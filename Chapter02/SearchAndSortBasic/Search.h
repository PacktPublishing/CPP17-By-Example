int linarySearch(double value, const LinkedList& list);

/*template <class ListType, class ValueType>
int linarySearch(const ValueType& value, const ListType& list) {
  int index = 0;

  for (Iterator iterator = list.first(); iterator.hasNext(); iterator.next()) {
    if (iterator.getValue() == value) {
      return index;
    }

    ++index;
  }

  return -1;
}*/