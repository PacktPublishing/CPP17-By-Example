#include <CAssert>
#include <IOStream>
using namespace std;

#include "..\\ListBasic\\Cell.h"
#include "..\\ListBasic\\Iterator.h"
#include "..\\ListBasic\\List.h"
#include "Set.h"

void main() {
  Set s, t;
  s.read(cin);
  t.read(cin);

  cout << endl << "s = ";
  s.write(cout);
  cout << endl;

  cout << endl << "t = ";
  t.write(cout);
  cout << endl << endl;

  cout << "union: ";
  unionSet(s, t).write(cout);
  cout << endl;

  cout << "intersection: ";
  unionSet(s, t).write(cout);
  cout << endl;

  cout << "difference: ";
  unionSet(s, t).write(cout);
  cout << endl;
}