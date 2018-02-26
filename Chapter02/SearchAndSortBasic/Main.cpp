#include <IOStream>
#include <CStdLib>
#include <CAssert>
using namespace std;

#include "..\\ListBasic\\Cell.h"
#include "..\\ListBasic\\Iterator.h"
#include "..\\ListBasic\\List.h"

#include "Search.h"
#include "Sort.h"

void main() {
  cout << "LinkedList" << endl;

  LinkedList list;
  list.add(9);
  list.add(7);
  list.add(5);
  list.add(3);
  list.add(1);

  list.write(cout);
  cout << endl;

  Iterator iterator = list.first();
  while (iterator.hasNext()) {
    cout << "<" << iterator.getValue() << ","
         << linarySearch(iterator.getValue(), list) << "> ";
    iterator.next();
  }

  cout << "<0," << linarySearch(0, list) << "> ";
  cout << "<6," << linarySearch(6, list) << "> ";
  cout << "<10," << linarySearch(10, list) << ">"
       << endl;

  cout << "Bubble Sort ";
  bubbleSort(list);
  list.write(cout);
  cout << endl;

  cout << "Select Sort ";
  selectSort(list);
  list.write(cout);
  cout << endl;

  cout << "Insert Sort ";
  insertSort(list);
  list.write(cout);
  cout << endl;
}