#include <IOStream>
using namespace std;

#include "Cell.h"
#include "Iterator.h"
#include "List.h"

void main() {
  LinkedList list;
  list.add(1);
  list.add(2);
  list.add(3);
  list.add(4);
  list.add(5);
  list.write(cout);
  cout << endl;

  { Iterator iterator = list.first();
    while (iterator.hasNext()) {
      cout << iterator.getValue() << " ";
      iterator.next();
    }
    cout << endl;
  }

  { Iterator iterator = list.last();
    while (iterator.hasPrevious()) {
      cout << iterator.getValue() << " ";
      iterator.previous();
    }
    cout << endl;
  }
}