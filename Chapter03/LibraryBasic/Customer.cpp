#include <Set>
#include <Map>
#include <List>
#include <String>
#include <FStream>
using namespace std;

#include "Book.h"
#include "Customer.h"
#include "Library.h"

int Customer::MaxCustomerId;

Customer::Customer(void) {
  // Empty.
}

Customer::Customer(const string& name, const string& address)
 :m_customerId(++MaxCustomerId),
  m_name(name),
  m_address(address) {
  // Empty.
}

/*Customer::Customer(const Customer& customer)
 :m_customerId(customer.m_customerId),
  m_name(customer.m_name),
  m_address(customer.m_address),
  m_loanSet(customer.m_loanSet),
  m_reservationSet(customer.m_reservationSet) {
  // Empty.
}

Customer& Customer::operator=(const Customer& customer) {
  m_customerId = customer.m_customerId;
  m_name = customer.m_name;
  m_address = customer.m_address;
  m_loanSet = customer.m_loanSet;
  m_reservationSet = customer.m_reservationSet;
  return *this;
}*/

void Customer::read(ifstream& inStream) {
  inStream.read((char*) &m_customerId, sizeof m_customerId);
  getline(inStream, m_name);
  getline(inStream, m_address);

  { int borrowSetSize;
    inStream.read((char*) &borrowSetSize, sizeof borrowSetSize);

    for (int count = 0; count < borrowSetSize; ++count) {
      int bookId;
      inStream.read((char*)&bookId, sizeof bookId);
      m_loanSet.insert(bookId);
    }
  }

  { int reserveListSize;
    inStream.read((char*) &reserveListSize,
                  sizeof reserveListSize);

    for (int count = 0; count < reserveListSize; ++count) {
      int bookId;
      inStream.read((char*) &bookId, sizeof bookId);
      m_loanSet.insert(bookId);
    }
  }
}

void Customer::write(ofstream& outStream) const {
  outStream.write((char*) &m_customerId, sizeof m_customerId);
  outStream << m_name << endl;
  outStream << m_address << endl;

  { int borrowSetSize = m_loanSet.size();
    outStream.write((char*) &borrowSetSize, sizeof borrowSetSize);

    for (int bookId : m_loanSet) {
      outStream.write((char*) &bookId, sizeof bookId);
    }
  }

  { int reserveListSize = m_reservationSet.size();
    outStream.write((char*) &reserveListSize,
                    sizeof reserveListSize);

    for (int bookId : m_reservationSet) {
      outStream.write((char*) &bookId, sizeof bookId);
    }
  }
}

void Customer::borrowBook(int bookId) {
  m_loanSet.insert(bookId);
}

void Customer::reserveBook(int bookId) {
  m_reservationSet.insert(bookId);
}

void Customer::returnBook(int bookId) {
  m_loanSet.erase(bookId);
}

void Customer::unreserveBook(int bookId) {
  m_reservationSet.erase(bookId);
}

ostream& operator<<(ostream& outStream, const Customer& customer) {
  outStream << customer.m_customerId << ". " << customer.m_name
            << ", " << customer.m_address << ".";

  if (!customer.m_loanSet.empty()) {
    outStream << endl << "  Borrowed books: ";

    bool first = true;
    for (int bookId : customer.m_loanSet) {
      outStream << (first ? "" : ",")
                << Library::s_bookMap[bookId].author();
      first = false;
    }
  }

  if (!customer.m_reservationSet.empty()) {
    outStream << endl << "  Reserved books: ";

    bool first = true;
    for (int bookId : customer.m_reservationSet) {
      outStream << (first ? "" : ",")
                << Library::s_bookMap[bookId].title();
      first = false;
    }
  }

  return outStream;
}