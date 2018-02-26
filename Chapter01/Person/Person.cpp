#include <string>
#include <IOStream>
using namespace std;

#include "Person.h"

Person::Person(string name)
 :m_name(name) {
  // Empty.
}

void Person::print() {
  cout << "Person " << m_name << endl;
}