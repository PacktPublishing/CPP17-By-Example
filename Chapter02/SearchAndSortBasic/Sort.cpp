#include <IOStream>
using namespace std;

#include "..\\ListBasic\\Cell.h"
#include "..\\ListBasic\\Iterator.h"
#include "..\\ListBasic\\List.h"
#include "Sort.h"

void insert(double value, LinkedList& list);
void swap(Iterator iterator1, Iterator iterator2);

void selectSort(LinkedList& list) {
  LinkedList result;

  while (!list.empty()) {
    Iterator minIterator = list.first();
    double minValue = minIterator.getValue();

    Iterator iterator = list.first();

    while (iterator.hasNext()) {
      if (iterator.getValue() < minValue) {
        minIterator = iterator;
        minValue = iterator.getValue();
      }

      iterator.next();
    }

    list.erase(minIterator);
    result.add(minValue);
  }

  list.assign(result);
}

void insertSort(LinkedList& list) {
  LinkedList result;
  Iterator iterator = list.first();

  while (iterator.hasNext()) {
    insert(iterator.getValue(), result);
    iterator.next();
  }

  list.assign(result);
}

void insert(double value, LinkedList& list) {
  Iterator iterator = list.first();

  while (iterator.hasNext()) {
    if (value < iterator.getValue()) {
      list.insert(iterator, value);
      return;
    }

    iterator.next();
  }

  list.add(value);
}

void bubbleSort(LinkedList& list) {
  int listSize = list.size();

  if (listSize > 1) {
    int currSize = listSize - 1;
    int outerCount = 0;
    while (outerCount < (listSize - 1)) {
      Iterator currIterator = list.first();
      Iterator nextIterator = currIterator;
      nextIterator.next();
      bool changed = false;

      int innerCount = 0;
      while (innerCount < currSize) {
        if (currIterator.getValue() > nextIterator.getValue()) {
          swap(currIterator, nextIterator);
          changed = true;
        }

        ++innerCount;
        currIterator.next();
        nextIterator.next();
      }

      if (!changed) {
        break;
      }

      --currSize;
      ++outerCount;
    }
  }
}

void swap(Iterator iterator1, Iterator iterator2) {
  double tempValue = iterator1.getValue();
  iterator1.setValue(iterator2.getValue());
  iterator2.setValue(tempValue);
}