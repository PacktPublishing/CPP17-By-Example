template <class ListType, class ValueType>
void mergeSort(ListType& list) {
  int size = list.size();

  if (size > 1) {
    int middle = list.size() / 2;
    ListType::Iterator iterator = list.begin();

    ListType leftList;
    for (int count = 0; count < middle; ++count) {
      leftList.add(*iterator);
      ++iterator;
    }

    ListType rightList;
    for (; iterator != list.end(); ++iterator) {
      rightList.add(*iterator);
    }

    mergeSort<ListType, ValueType>(leftList);
    mergeSort<ListType, ValueType>(rightList);

    ListType resultList;
    merge<ListType, ValueType>(leftList, rightList, resultList);
    list = resultList;
  }
}

template <class ListType, class ValueType>
void merge(ListType& leftList, ListType& rightList,
           ListType& result) {
  ListType::Iterator leftPosition = leftList.begin();
  ListType::Iterator rightPosition = rightList.begin();

  while ((leftPosition != leftList.end()) &&
    (rightPosition != rightList.end())) {
    if (*leftPosition < *rightPosition) {
      result.add(*leftPosition);
      ++leftPosition;
    }
    else {
      result.add(*rightPosition);
      ++rightPosition;
    }
  }

  while (leftPosition != leftList.end()) {
    result.add(*leftPosition);
    ++leftPosition;
  }

  while (rightPosition != rightList.end()) {
    result.add(*rightPosition);
    ++rightPosition;
  }
}

template <class ListType, class ValueType>
void quickSort(ListType& list) {
  if (list.size() > 1) {
    ListType smaller, larger;
    ValueType pivotValue = *list.begin();

    ListType::Iterator position = list.begin();
    ++position;

    for (; position != list.end(); ++position) {
      if (*position < pivotValue) {
        smaller.add(*position);
      }
      else {
        larger.add(*position);
      }
    }

    quickSort<ListType, ValueType>(smaller);
    quickSort<ListType, ValueType>(larger);
    list = smaller;
    list.add(pivotValue);
    list.add(larger);
  }
}

//void heapSort(ListType& list);

/*template <class ListType, class ValueType>
void findMinValue(const ListType& list, ListType::Iterator& minPosition, ValueType& minValue) {
  ListType::Iterator minPosition = list.begin();
  minValue = minPosition.value();

  for (ListType::Iterator position = list.begin(); position.hasNext(); ++position) {
    if (position.value() < minValue) {
      minValue = position.value();
      minPosition = position;
    }
  }

  return minPosition;
}

template <class ListType, class ValueType>
void selectSort(ListType& list) {
  ListType result;

  while (!list.empty()) {
    ValueType minValue;
    ListType::Iterator minPosition;
    findMinValue(list, minPosition, minValue);
    result.add(minValue);
    list.erase(minPosition);
  }

  list = result;
}

template <class ListType, class ValueType>
int findMinValue(const ListType& list, ValueType& minValue) {
  minValue = list[0];
  int minIndex = 0;

  for (int index = 1; index < list.size(); ++index) {
    if (list[index] < minValue) {
      minValue = list[index];
      minIndex = index;
    }
  }

  return minIndex;
}

template <class ListType, class ValueType>
void insertSort(ListType& list) {
  ListType result;

  for (int index = 0; index < list.size(); ++index) {
    insert(list[index], result);
  }

  list = result;
}

template <class ListType, class ValueType>
void insert(const ValueType& value, ListType& list) {
  for (int index = 0; index < list.size(); ++index) {
    if (value < list[index]) {
      list.insert(index, value);
      return;
    }
  }

  list.add(value);
}

template <class ListType, class ValueType>
void bubbleSort(ListType& list) {
  int size = list.size();

  for (int count = 0; count < (size - 1); ++count) {
    if (!bubble<ListType,ValueType>(list, size - count)) {
      break;
    }
  }
}

template <class ListType, class ValueType>
bool bubble(ListType& list, int size) {
  bool changed = false;

  for (int index = 0; index < (size - 1); ++index) {
    if (list[index] > list[index + 1]) {
      swap<ListType,ValueType>(list[index], list[index + 1]);
      changed = true;
    }
  }

  return changed;
}

template <class ListType, class ValueType>
void mergeSort(ListType& list) {
  int size = list.size();

  if (size > 1) {
    ListType left = list.slice(0, (size / 2) - 1),
             right = list.slice(size / 2);

    mergeSort<ListType, ValueType>(left);
    mergeSort<ListType,ValueType>(right);

    ListType result;
    merge<ListType,ValueType>(left, right, result);
    list = result;
  }
}

template <class ListType, class ValueType>
void merge(const ListType& left, const ListType& right, ListType& result) {
  int leftIndex = 0, rightIndex = 0;

  while ((leftIndex < left.size()) && (rightIndex < right.size())) {
    if (left[leftIndex] < right[rightIndex]) {
      ListType::Iterator x = left[leftIndex];
      result.add(left[leftIndex]);
      ++leftIndex;
    }
    else {
      ListType::Iterator x = right[rightIndex];
      result.add(right[rightIndex]);
      ++rightIndex;
    }
  }

  if (leftIndex < left.size()) {
    result.add(left.slice(leftIndex));
  }

  if (rightIndex < right.size()) {
    result.add(right.slice(rightIndex));
  }
}

template <class ListType, class ValueType>
void quickSort(ListType& list) {
  if (list.size() > 1) {
    ListType smaller, larger;
    ValueType pivotValue = list[0];

    for (int index = 1; index < list.size(); ++index) {
      if (list[index] < pivotValue) {
        smaller.add(list[index]);
      }
      else {
        larger.add(list[index]);
      }
    }

    quickSort<ListType,ValueType>(smaller);
    quickSort<ListType,ValueType>(larger);
    list = smaller;
    list.add(pivotValue);
    list.add(larger);
  }
}
*/
