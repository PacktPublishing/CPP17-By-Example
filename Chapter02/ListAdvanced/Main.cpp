#include <IOStream>
#include <Exception>
using namespace std;

#include "List.h"

void main() {
  LinkedList<double> list;
  cin >> list;
  cout << list << endl;

  for (double value : list) {
    cout << value << " ";
  }
  cout << endl;

  for (LinkedList<double>::Iterator iterator = list.begin();
       iterator != list.end(); ++iterator) {
    cout << *iterator << " ";
  }
  cout << endl;

  for (LinkedList<double>::ReverseIterator iterator =
       list.rbegin(); iterator != list.rend(); ++iterator) {
    cout << *iterator << " ";
  }
  cout << endl;
}