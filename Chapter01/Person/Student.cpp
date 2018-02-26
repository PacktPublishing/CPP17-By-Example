#include <string>
#include <IOStream>
using namespace std;

#include "Person.h"
#include "Student.h"

Student::Student(string name, string university)
 :Person(name),
   m_university(university) {
  // Empty.
}

void Student::print() {
  Person::print();
  cout << "University " << m_university << endl;
}