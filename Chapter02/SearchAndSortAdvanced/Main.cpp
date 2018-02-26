#include <IOStream>
#include <CStdLib>
#include <CAssert>
using namespace std;

#include "ArrayList.h"
#include "..\\ListAdvanced\\List.h"

#include "Search.h"
#include "Sort.h"

void linkedList();

void main() {
  linkedList();
}

void linkedList() {
  LinkedList<double> list;
  cin >> list;

  for (LinkedList<double>::Iterator iterator = list.begin(); iterator != list.end(); ++iterator) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (LinkedList<double>::ReverseIterator iterator = list.rbegin(); iterator != list.rend(); ++iterator) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (LinkedList<double>::Iterator iterator = list.begin(); iterator != list.end(); iterator++) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (LinkedList<double>::ReverseIterator iterator = list.rbegin(); iterator != list.rend(); iterator++) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (const double value : list) {
    cout << value << " ";
  }
  cout << endl;

  for (const double& value : list) {
    cout << value << " ";
  }
  cout << endl;

  for (double value : list) {
    cout << value << " ";
  }
  cout << endl;

  for (double& value : list) {
    cout << value << " ";
  }
  cout << endl;

  mergeSort<LinkedList<double>, double>(list);
  cout << "Merge Sort " << list << endl;

  quickSort<LinkedList<double>, double>(list);
  cout << "Quick Sort " << list << endl;

  for (double value : list) {
    cout << "<" << value << "," <<
        binarySearch<LinkedList<double>, double>(value, list) << "> ";
  }

  cout << "<0," << binarySearch<LinkedList<double>, double>(0, list) << "> ";
  cout << "<6," << binarySearch<LinkedList<double>, double>(6, list) << "> ";
  cout << "<10," << binarySearch<LinkedList<double>, double>(10, list) << ">"
       << endl;

  const LinkedList<double> list2(list);

  for (LinkedList<double>::Iterator iterator = list2.begin(); iterator != list2.end(); ++iterator) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (LinkedList<double>::ReverseIterator iterator = list2.rbegin(); iterator != list2.rend(); ++iterator) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (LinkedList<double>::Iterator iterator = list2.begin(); iterator != list2.end(); iterator++) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (LinkedList<double>::ReverseIterator iterator = list2.rbegin(); iterator != list2.rend(); iterator++) {
    cout << *iterator << " ";
  }
  cout << endl;
 
  for (const double value : list2) {
    cout << value << " ";
  }
  cout << endl;

  for (const double& value : list2) {
    cout << value << " ";
  }
  cout << endl;

  for (double value : list2) {
    cout << value << " ";
  }
  cout << endl;

  for (double& value : list2) {
    cout << value << " ";
  }
  cout << endl;
}

#if 0
void arrayList() {
  cout << "ArrayList" << endl;

  ArrayList list;
  list.add(9);
  list.add(7);
  list.add(5);
  list.add(3);
  list.add(1);

  for (ArrayList::Iterator position = list.begin(); position.hasNext();
       position.next()) {
    cout << "<" << *position << "," <<
         linarySearch<ArrayList, double>(*position, list) << "> ";
  }

  cout << "<0," << linarySearch<ArrayList,double>(0, list) << "> ";
  cout << "<6," << linarySearch<ArrayList, double>(6, list) << "> ";
  cout << "<10," << linarySearch<ArrayList, double>(10, list) << ">"
       << endl;

  selectSort<ArrayList, double>(list);
  cout << "Select " << list << endl;

  for (ArrayList::Iterator position = list.begin(); position.hasNext();
       position.next()) {
    cout << "<" << *position << "," <<
         binarySearch<ArrayList, double>(*position, list) << "> ";
  }

  cout << "<0," << binarySearch<ArrayList, double>(0, list) << "> ";
  cout << "<6," << binarySearch<ArrayList, double>(6, list) << "> ";
  cout << "<10," << binarySearch<ArrayList, double>(10, list) << ">"
       << endl;

  insertSort<ArrayList,double>(list);
  cout << "Insert " << list << endl;
  bubbleSort<ArrayList, double>(list);
  cout << "Bubble " << list << endl;
  mergeSort<ArrayList, double>(list);
  cout << "Merge  " << list << endl;
  quickSort<ArrayList,double>(list);
  cout << "Quick  " << list << endl;
}
#endif

#if 0
#include <IOStream>
#include <CStdLib>
#include <CAssert>
using namespace std;

#include "..\\ArrayList\\ArrayList.h"
#include "..\\ListBasic\\List.h"
#include "Search.h"
#include "Sort.h"

void linkedList();
void arrayList();

void main() {
  linkedList();
  arrayList();
}

void linkedList() {
  cout << "LinkedList" << endl;

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);

    for (LinkedList::Iterator pos = list.begin(); pos.hasNext(); pos.next()) {
      cout << "<" << *pos << "," << linarySearch<LinkedList, double>(*pos, list) << "> ";
    }

/*    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << linarySearch<LinkedList,double>(list[index], list) << "> ";
    }*/

    cout << "<0," << linarySearch<LinkedList,double>(0, list) << "> ";
    cout << "<6," << linarySearch<LinkedList, double>(6, list) << "> ";
    cout << "<10," << linarySearch<LinkedList, double>(10, list) << ">" << endl;

    selectSort<LinkedList,double>(list);

    for (LinkedList::Iterator pos = list.begin(); pos.hasNext(); pos.next()) {
      cout << "<" << *pos << "," << linarySearch<LinkedList, double>(*pos, list) << "> ";
    }

/*    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << binarySearch<LinkedList,double>(list[index], list) << "> ";
    }*/
    
    cout << "<0," << binarySearch<LinkedList, double>(0, list) << "> ";
    cout << "<6," << binarySearch<LinkedList, double>(6, list) << "> ";
    cout << "<10," << binarySearch<LinkedList, double>(10, list) << ">" << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Select " << list;
    selectSort<LinkedList,double>(list);
    cout << " " << list << " ";
    selectSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Insert " << list;
    insertSort<LinkedList,double>(list);
    cout << " " << list << " ";
    insertSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Bubble " << list;
    bubbleSort<LinkedList, double>(list);
    cout << " " << list << " ";
    bubbleSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Merge " << list;
    mergeSort<LinkedList,double>(list);
    cout << " " << list << " ";
    mergeSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Quick " << list;
    quickSort<LinkedList,double>(list);
    cout << " " << list << " ";
    quickSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }
}

void arrayList() {
  cout << "ArrayList" << endl;

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);

    for (ArrayList::Iterator pos = list.begin(); pos.hasNext(); pos.next()) {
      cout << "<" << *pos << "," << linarySearch<ArrayList, double>(*pos, list) << "> ";
    }

/*    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << linarySearch<ArrayList,double>(list[index], list) << "> ";
    }*/

    cout << "<0," << linarySearch<ArrayList,double>(0, list) << "> ";
    cout << "<6," << linarySearch<ArrayList, double>(6, list) << "> ";
    cout << "<10," << linarySearch<ArrayList, double>(10, list) << ">" << endl;

    selectSort<ArrayList,double>(list);

    for (ArrayList::Iterator pos = list.begin(); pos.hasNext(); pos.next()) {
      cout << "<" << *pos << "," << linarySearch<ArrayList, double>(*pos, list) << "> ";
    }

/*    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << binarySearch<ArrayList,double>(list[index], list) << "> ";
    }*/
    
    cout << "<0," << binarySearch<ArrayList, double>(0, list) << "> ";
    cout << "<6," << binarySearch<ArrayList, double>(6, list) << "> ";
    cout << "<10," << binarySearch<ArrayList, double>(10, list) << ">" << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Select " << list;
    selectSort<ArrayList,double>(list);
    cout << " " << list << " ";
    selectSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Insert " << list;
    insertSort<ArrayList,double>(list);
    cout << " " << list << " ";
    insertSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Bubble " << list;
    bubbleSort<ArrayList, double>(list);
    cout << " " << list << " ";
    bubbleSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Merge " << list;
    mergeSort<ArrayList,double>(list);
    cout << " " << list << " ";
    mergeSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Quick " << list;
    quickSort<ArrayList,double>(list);
    cout << " " << list << " ";
    quickSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }
}

/*
void linkedList() {
  cout << "LinkedList" << endl;

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);

    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << linarySearch<LinkedList,double>(list[index], list) << "> ";
    }

    cout << "<0," << linarySearch<LinkedList,double>(0, list) << "> ";
    cout << "<6," << linarySearch<LinkedList, double>(6, list) << "> ";
    cout << "<10," << linarySearch<LinkedList, double>(10, list) << ">" << endl;

    selectSort<LinkedList,double>(list);

    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << binarySearch<LinkedList,double>(list[index], list) << "> ";
    }
    
    cout << "<0," << binarySearch<LinkedList, double>(0, list) << "> ";
    cout << "<6," << binarySearch<LinkedList, double>(6, list) << "> ";
    cout << "<10," << binarySearch<LinkedList, double>(10, list) << ">" << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Select " << list;
    selectSort<LinkedList,double>(list);
    cout << " " << list << " ";
    selectSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Insert " << list;
    insertSort<LinkedList,double>(list);
    cout << " " << list << " ";
    insertSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Bubble " << list;
    bubbleSort<LinkedList, double>(list);
    cout << " " << list << " ";
    bubbleSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Merge " << list;
    mergeSort<LinkedList,double>(list);
    cout << " " << list << " ";
    mergeSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }

  { LinkedList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Quick " << list;
    quickSort<LinkedList,double>(list);
    cout << " " << list << " ";
    quickSort<LinkedList, double>(list);
    cout << " " << list << endl;
  }
}

void arrayList() {
  cout << "ArrayList" << endl;

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);

    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << linarySearch<ArrayList,double>(list[index], list) << "> ";
    }

    cout << "<0," << linarySearch<ArrayList,double>(0, list) << "> ";
    cout << "<6," << linarySearch<ArrayList, double>(6, list) << "> ";
    cout << "<10," << linarySearch<ArrayList, double>(10, list) << ">" << endl;

    selectSort<ArrayList,double>(list);

    for (int index = 0; index < list.size(); ++index) {
      cout << "<" << list[index] << "," << binarySearch<ArrayList,double>(list[index], list) << "> ";
    }
    
    cout << "<0," << binarySearch<ArrayList, double>(0, list) << "> ";
    cout << "<6," << binarySearch<ArrayList, double>(6, list) << "> ";
    cout << "<10," << binarySearch<ArrayList, double>(10, list) << ">" << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Select " << list;
    selectSort<ArrayList,double>(list);
    cout << " " << list << " ";
    selectSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Insert " << list;
    insertSort<ArrayList,double>(list);
    cout << " " << list << " ";
    insertSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Bubble " << list;
    bubbleSort<ArrayList, double>(list);
    cout << " " << list << " ";
    bubbleSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Merge " << list;
    mergeSort<ArrayList,double>(list);
    cout << " " << list << " ";
    mergeSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }

  { ArrayList list;
    list.add(9);
    list.add(7);
    list.add(5);
    list.add(3);
    list.add(1);
    cout << "Quick " << list;
    quickSort<ArrayList,double>(list);
    cout << " " << list << " ";
    quickSort<ArrayList, double>(list);
    cout << " " << list << endl;
  }
}
*/
#endif