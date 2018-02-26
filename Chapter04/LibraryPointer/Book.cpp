#include <Set>
#include <Map>
#include <List>
#include <String>
#include <FStream>
#include <Algorithm>
using namespace std;

#include "Book.h"
#include "Customer.h"
#include "Library.h"

Book::Book() {
  // Empty.
}

Book::Book(const string& author, const string& title)
 :m_author(author),
  m_title(title) {
  // Empty.
}

/*Book::Book(const Book& book)
 :m_author(book.m_author),
  m_title(book.m_title),
  m_borrowerPtr(book.m_borrowerPtr),
  m_reservationPtrList(book.m_reservationPtrList) {
  // Empty.
}

Book& Book::operator=(const Book& book) {
  m_author = book.m_author;
  m_title = book.m_title;
  m_borrowerPtr = book.m_borrowerPtr;
  m_reservationPtrList = book.m_reservationPtrList;
  return *this;
}*/

void Book::read(ifstream& inStream) {
  getline(inStream, m_author);
  getline(inStream, m_title);
}

void Book::write(ofstream& outStream) const {
  outStream << m_author << endl;
  outStream << m_title << endl;
}

void Book::borrowBook(Customer* borrowerPtr) {
  m_borrowerPtr = borrowerPtr;
}

int Book::reserveBook(Customer* borrowerPtr) {
  m_reservationPtrList.push_back(borrowerPtr);
  return m_reservationPtrList.size();
}

void Book::returnBook() {
  m_borrowerPtr = nullptr;
}

void Book::removeReservation(Customer* customerPtr) {
  m_reservationPtrList.remove(customerPtr);
}

ostream& operator<<(ostream& outStream, const Book& book) {
  outStream << "\"" << book.m_title << "\" by " << book.m_author;

  if (book.m_borrowerPtr != nullptr) {
    outStream << endl << "  Borrowed by: "
              << book.m_borrowerPtr->name() << ".";
  }

  if (!book.m_reservationPtrList.empty()) {
    outStream << endl << "  Reserved by: ";
    
    bool first = true;
    for (Customer* customerPtr : book.m_reservationPtrList) {
      outStream << (first ? "" : ",") << customerPtr->name();
      first = false;
    }

    outStream << ".";
  }

  return outStream;
}