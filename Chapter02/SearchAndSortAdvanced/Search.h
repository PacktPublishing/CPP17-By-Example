template <class ListType, class ValueType>
int linarySearch(const ValueType& value, const ListType& list) {
  int index = 0;

  for (double listValue : list) {
    if (listValue == value) {
      return index;
    }

    ++index;
  }

  return -1;
}

template <class ListType, class ValueType>
int binarySearch(const ValueType& value, const ListType& list) {
  ListType::Iterator* positionBuffer =
    new ListType::Iterator[list.size()];

  int index = 0;
  for (ListType::Iterator position = list.begin();
       position != list.end(); ++position) {
    positionBuffer[index++] = position;
  }

  int minIndex = 0, maxIndex = list.size() - 1;

  while (minIndex <= maxIndex) {
    int middleIndex = (maxIndex + minIndex) / 2;
    ListType::Iterator iterator = positionBuffer[middleIndex];
    const ValueType& middleValue = *iterator;

    if (value == middleValue) {
      return middleIndex;
    }
    else if (value < middleValue) {
      maxIndex = middleIndex - 1;
    }
    else {
      minIndex = middleIndex + 1;
    }
  }

  return -1;
}

/*template <class ListType, class ValueType>
int linarySearch(const ValueType& value, const ListType& list) {
  for (int index = 0; index < list.size(); ++index) {
    if (list[index] == value) {
      return index;
    }
  }

  return -1;
}

template <class ListType, class ValueType>
int binarySearch(const ValueType& value, const ListType& list) {
  int minIndex = 0, maxIndex = list.size() - 1;

  while (minIndex <= maxIndex) {
    int middleIndex = (maxIndex + minIndex) / 2;
    const ValueType& middleValue = list[middleIndex];

    if (value == middleValue) {
      return middleIndex;
    }
    else if (value < middleValue) {
      maxIndex = middleIndex - 1;
    }
    else {
      minIndex = middleIndex + 1;
    }
  }

  return -1;
}*/