#include <string>
#include <IOStream>
using namespace std;

#include "Person.h"
#include "Employee.h"

Employee::Employee(string name, string company)
 :Person(name),
  m_company(company) {
  // Empty.
}

void Employee::print() {
  Person::print();
  cout << "Company " << m_company << endl;
}