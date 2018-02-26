#include <IOStream>
using namespace std;

#include "..\\ListBasic\\Cell.h"
#include "..\\ListBasic\\Iterator.h"
#include "..\\ListBasic\\List.h"
#include "Search.h"

int linarySearch(double value, const LinkedList& list) {
  int index = 0;
  Iterator iterator = list.first();

  while (iterator.hasNext()) {
    if (iterator.getValue() == value) {
      return index;
    }

    ++index;
    iterator.next();
  }

  return -1;
}