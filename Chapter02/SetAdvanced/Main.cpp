#include <CAssert>
#include <IOStream>
using namespace std;

#include "..\\ListAdvanced\\List.h"
#include "Set.h"

void main() {
  Set<double> s, t;
  cin >> s >> t;

  cout << endl << "s: " << s << endl;
  cout << "t: " << t << endl;

  cout << endl << "s: ";
  for (double value : s) {
    cout << value << " ";
  }

  cout << endl << "t: ";
  for (Set<double>::Iterator iterator = t.begin();
    iterator != t.end(); ++iterator) {
    cout << *iterator << " ";
  }

  cout << endl << endl << "union: " << (s + t) << endl;
  cout << "intersection: " << (s *t) << endl;
  cout << "difference: " << (s - t) << endl << endl;
}