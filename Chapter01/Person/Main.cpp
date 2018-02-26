#include <string>
#include <IOStream>
using namespace std;

#include "Person.h"
#include "Student.h"
#include "Employee.h"

void main() {
  Person person("Monica");
  person.print();
  cout << endl;

  Student student("Demi", "Harvard");
  student.print();
  cout << endl;

  Employee employee("Charles", "Microsoft");
  employee.print();
  cout << endl;

  Person* personPtr;
  personPtr = &person;
  personPtr->print();
  cout << endl;

  personPtr = &student;
  personPtr->print();
  cout << endl;

  personPtr = &employee;
  personPtr->print();
}