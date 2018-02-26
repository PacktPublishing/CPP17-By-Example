#include <Set>
#include <Map>
#include <List>
#include <String>
#include <FStream>
#include <IOStream>
#include <CAssert>
using namespace std;

#include "Book.h"
#include "Customer.h"
#include "Library.h"

string Library::s_binaryPath("C:\\Users\\Stefan\\Library.binary");

Library::Library() {
  load();

  bool quit = false;
  while (!quit) {
    cout << "1. Add Book" << endl
         << "2. Delete Book" << endl
         << "3. List Books" << endl
         << "4. Add Customer" << endl
         << "5. Delete Customer" << endl
         << "6. List Customers" << endl
         << "7. Borrow Book" << endl
         << "8. Reserve Book" << endl
         << "9. Return Book" << endl
         << "0. Quit" << endl
         << ": ";

    int choice;
    cin >> choice;
    cout << endl;

    switch (choice) {
      case 1:
        addBook();
        break;

      case 2:
        deleteBook();
        break;

      case 3:
        listBooks();
        break;

      case 4:
        addCustomer();
        break;

      case 5:
        deleteCustomer();
        break;

      case 6:
        listCustomers();
        break;

      case 7:
        borrowBook();
        break;

      case 8:
        reserveBook();
        break;

      case 9:
        returnBook();
        break;

      case 0:
        quit = true;
        break;
    }

    cout << endl;
  }

  save();
}

Book* Library::lookupBook(const string& author,
                            const string& title) {
  for (Book* bookPtr : m_bookPtrList) {
    if ((bookPtr->author() == author) &&
        (bookPtr->title() == title)) {
      return bookPtr;
    }
  }

  return nullptr;
}

Customer* Library::lookupCustomer(const string& name,
                                  const string& address) {
  for (Customer* customerPtr : m_customerPtrList) {
    if ((customerPtr->name() == name) &&
        (customerPtr->address() == address)) {
      return customerPtr;
    }
  }

  return nullptr;
}

void Library::addBook() {
  string author;
  cout << "Author: ";
  cin >> author;

  string title;
  cout << "Title: ";
  cin >> title;

  if (lookupBook(author, title) != nullptr) {
    cout << endl << "The book \"" <<  title << "\" by "
         << author << " already exists." << endl;
    return;
  }
  
  Book* bookPtr = new Book(author, title);
  assert(bookPtr != nullptr);
  m_bookPtrList.push_back(bookPtr);
  cout << endl << "Added." << endl;
}

void Library::deleteBook() {
  string author;
  cout << "Author: ";
  cin >> author;

  string title;
  cout << "Title: ";
  cin >> title;

  Book* bookPtr = lookupBook(author, title);

  if (bookPtr == nullptr) {
    cout << endl << "Author " << author
         << " does not exists." << endl;
    return;
  }

  Customer* borrowerPtr = bookPtr->borrowerPtr();

  if (borrowerPtr != nullptr) {
    borrowerPtr->returnBook(bookPtr);
  }

  list<Customer*> reservationPtrList =
    bookPtr->reservationPtrList();

  for (Customer* reserverPtr : reservationPtrList) {
    reserverPtr->unreserveBook(bookPtr);
  }

  m_bookPtrList.remove(bookPtr);
  cout << endl << "Deleted:" << bookPtr << endl;
  delete bookPtr;
}

void Library::listBooks() {
  if (m_bookPtrList.empty()) {
    cout << "No books." << endl;
    return;
  }

  for (const Book* bookPtr : m_bookPtrList) {
    cout << (*bookPtr) << endl;
  }
}

void Library::addCustomer() {
  string name;
  cout << "Name: ";
  cin >> name;

  string address;
  cout << "Address: ";
  cin >> address;

  if (lookupCustomer(name, address) != nullptr) {
    cout << endl << "A customer with name " << name
         << " and address " << address << " already exists."
         << endl;
    return;
  }
  
  Customer* customerPtr = new Customer(name, address);
  assert(customerPtr != nullptr);
  m_customerPtrList.push_back(customerPtr);
  cout << endl << "Added." << endl;
}

void Library::deleteCustomer() {
  string name;
  cout << "Customer name: ";
  cin >> name;

  string address;
  cout << "Address: ";
  cin >> address;

  Customer* customerPtr = lookupCustomer(name, address);

  if (customerPtr == nullptr) {
    cout << endl << "Customer " << name
         << " does not exists." << endl;
    return;
  }

  if (!customerPtr->loanPtrSet().empty()) {
    cout << "The customer " << customerPtr->name()
         << " has borrowed books and connot be deleted." << endl;
    return;
  }

  for (Book* bookPtr : m_bookPtrList) {
    bookPtr->removeReservation(customerPtr);
  }

  m_customerPtrList.remove(customerPtr);
  cout << endl << "Deleted." << (*customerPtr) << endl;
  delete customerPtr;
}

void Library::listCustomers() {
  if (m_customerPtrList.empty()) {
    cout << "No customers." << endl;
    return;
  }
      
  for (const Customer* customerPtr: m_customerPtrList) {
    cout << (*customerPtr) << endl;
  }
}

void Library::borrowBook() {
  string author;
  cout << "Author: ";
  cin >> author;

  string title;
  cout << "Title: ";
  cin >> title;

  Book* bookPtr = lookupBook(author, title);

  if (bookPtr == nullptr) {
    cout << endl << "There is no book \"" << title
         << "\" by " << author << "." << endl;
    return;
  }

  if (bookPtr->borrowerPtr() != nullptr) {
    cout << endl << "The book \"" << title << "\" by " << author 
         << " has already been borrowed." << endl;
    return;
  }

  string name;
  cout << "Customer name: ";
  cin >> name;

  string address;
  cout << "Address: ";
  cin >> address;

  Customer* customerPtr = lookupCustomer(name, address);

  if (customerPtr == nullptr) {
    cout << endl << "No customer with name " << name
         << " and address " << address << " exists."  << endl;
    return;
  }

  bookPtr->borrowBook(customerPtr);
  customerPtr->borrowBook(bookPtr);
  cout << endl << "Borrowed." << endl;
}

void Library::reserveBook() {
  string author;
  cout << "Author: ";
  cin >> author;

  string title;
  cout << "Title: ";
  cin >> title;

  Book* bookPtr = lookupBook(author, title);

  if (bookPtr == nullptr) {
    cout << endl << "There is no book \"" << title
         << "\" by " << author << "." << endl;
    return;
  }

  if (bookPtr->borrowerPtr() == nullptr) {
    cout << endl << "The book \"" << title << "\" by "
         << author << " has not been not borrowed. "
         << "Please borrow the book instead of reserving it."
         << endl;
    return;
  }

  string name;
  cout << "Customer name: ";
  cin >> name;

  string address;
  cout << "Address: ";
  cin >> address;

  Customer* customerPtr = lookupCustomer(name, address);

  if (customerPtr == nullptr) {
    cout << endl << "There is no customer with name " << name
         << " and address " << address << "." << endl;
    return;
  }

  if (bookPtr->borrowerPtr() == customerPtr) {
    cout << endl << "The book has already been borrowed by "
         << name << "." << endl;
    return;
  }

  int position = bookPtr->reserveBook(customerPtr);
  customerPtr->reserveBook(bookPtr);
  cout << endl << position << "nd reserve." << endl;
}

void Library::returnBook() {
  string author;
  cout << "Author: ";
  cin >> author;

  string title;
  cout << "Title: ";
  cin >> title;

  Book* bookPtr = lookupBook(author, title);

  if (bookPtr == nullptr) {
    cout << endl << "There is no book \"" << title << "\" by "
         << author << "." << endl;
    return;
  }

  Customer* customerPtr = bookPtr->borrowerPtr();

  if (customerPtr == nullptr) {
    cout << endl << "The book \"" << title << "\" by "
         << author << " has not been borrowed." << endl;
    return;
  }

  bookPtr->returnBook();
  customerPtr->returnBook(bookPtr);
  cout << endl << "Returned." << endl;

  list<Customer*>& reservationPtrList =
    bookPtr->reservationPtrList();

  if (!reservationPtrList.empty()) {
    Customer* newCustomerPtr = reservationPtrList.front();
    reservationPtrList.erase(reservationPtrList.begin());

    bookPtr->borrowBook(newCustomerPtr);
    newCustomerPtr->borrowBook(bookPtr);
    cout << endl << "Borrowed by "
         << newCustomerPtr->name() << endl;
  }
}

int Library::lookupBookIndex(const Book* bookPtr) {
  int index = 0;

  for (Book* testPtr : m_bookPtrList) {
    if (bookPtr == testPtr) {
      return index;
    }

    ++index;
  }

  assert(false);
  return -1;
}

Book* Library::lookupBookPtr(int bookIndex) {
  assert((bookIndex >= 0) &&
         (bookIndex < ((int) m_bookPtrList.size())));

  auto iterator = m_bookPtrList.begin();
  for (int count = 0; count < bookIndex; ++count) {
    ++iterator;
  }

  return *iterator;
}

int Library::lookupCustomerIndex(const Customer* customerPtr) {
  int index = 0;

  for (Customer* testPtr : m_customerPtrList) {
    if (customerPtr == testPtr) {
      return index;
    }

    ++index;
  }

  assert(false);
  return -1;
}

Customer* Library::lookupCustomerPtr(int customerIndex) {
  assert((customerIndex >= 0) &&
         (customerIndex < ((int) m_customerPtrList.size())));

  auto iterator = m_customerPtrList.begin();
  for (int count = 0; count < customerIndex; ++count) {
    ++iterator;
  }

  return *iterator;
}

void Library::save() {
  ofstream outStream(s_binaryPath);

  if (outStream) {
    { int bookPtrListSize = m_bookPtrList.size();
      outStream.write((char*) &bookPtrListSize,
                      sizeof bookPtrListSize);

      for (const Book* bookPtr : m_bookPtrList) {
        bookPtr->write(outStream);
      }
    }

    { int customerPtrListSize = m_customerPtrList.size();
      outStream.write((char*) &customerPtrListSize,
                      sizeof customerPtrListSize);

      for (const Customer* customerPtr : m_customerPtrList) {
        customerPtr->write(outStream);
      }
    }

    for (const Book* bookPtr : m_bookPtrList) {
      { const Customer* borrowerPtr = bookPtr->borrowerPtr();

        if (borrowerPtr != nullptr) {
          bool borrowed = true;
          outStream.write((char*) &borrowed, sizeof borrowed);
          int loanIndex = lookupCustomerIndex(borrowerPtr);
          outStream.write((char*) &loanIndex, sizeof loanIndex);
        }
        else {
          bool borrowed = false;
          outStream.write((char*) &borrowed, sizeof borrowed);
        }
      }

      { const list<Customer*>& reservationPtrList =
          bookPtr->reservationPtrList();
        int reserveSetSize = reservationPtrList.size();
        outStream.write((char*) &reserveSetSize,
                        sizeof reserveSetSize);

        for (const Customer* customerPtr : reservationPtrList) {
          int customerIndex = lookupCustomerIndex(customerPtr);
          outStream.write((char*) &customerIndex,
                          sizeof customerIndex);
        }
      }
    }

    for (const Customer* customerPtr : m_customerPtrList) {
      { const set<Book*>& loanPtrSet = customerPtr->loanPtrSet();
        int loanPtrSetSize = loanPtrSet.size();
        outStream.write((char*) &loanPtrSetSize,
                        sizeof loanPtrSetSize);

        for (const Book* customerPtr : loanPtrSet) {
          int customerIndex = lookupBookIndex(customerPtr);
          outStream.write((char*) &customerIndex,
                          sizeof customerIndex);
        }
      }

      { const set<Book*>& reservationPtrSet =
          customerPtr->reservationPtrSet();
        int reservationPtrSetSize = reservationPtrSet.size();
        outStream.write((char*) &reservationPtrSetSize,
                        sizeof reservationPtrSetSize);

        for (const Book* reservedPtr : reservationPtrSet) {
          int customerIndex = lookupBookIndex(reservedPtr);
          outStream.write((char*) &customerIndex,
                          sizeof customerIndex);
        }
      }
    }
  }
}

void Library::load() {
  ifstream inStream(s_binaryPath);

  if (inStream) {
    { int bookPtrListSize;
      inStream.read((char*) &bookPtrListSize,
                    sizeof bookPtrListSize);

      for (int count = 0; count < bookPtrListSize; ++count) {
        Book *bookPtr = new Book();
        assert(bookPtr != nullptr);
        bookPtr->read(inStream);
        m_bookPtrList.push_back(bookPtr);
      }
    }

    { int customerPtrListSize;
      inStream.read((char*) &customerPtrListSize,
                    sizeof customerPtrListSize);

      for (int count = 0; count < customerPtrListSize; ++count) {
        Customer *customerPtr = new Customer();
        assert(customerPtr != nullptr);
        customerPtr->read(inStream);
        m_customerPtrList.push_back(customerPtr);
      }
    }

    for (Book* bookPtr : m_bookPtrList) {
      { bool borrowed;
        inStream.read((char*) &borrowed, sizeof borrowed);

        if (borrowed) {
          int loanIndex;
          inStream.read((char*) &loanIndex, sizeof loanIndex);
          bookPtr->borrowerPtr() = lookupCustomerPtr(loanIndex);
        }
        else {
          bookPtr->borrowerPtr() = nullptr;
        }
      }

      { list<Customer*>& reservationPtrList =
          bookPtr->reservationPtrList();
        int reservationPtrListSize;
        inStream.read((char*) &reservationPtrListSize,
                      sizeof reservationPtrListSize);

        for (int count = 0; count < reservationPtrListSize;
             ++count) {
          int customerIndex;
          inStream.read((char*) &customerIndex,
                        sizeof customerIndex);
          Customer* customerPtr =
            lookupCustomerPtr(customerIndex);
          reservationPtrList.push_back(customerPtr);
        }
      }
    }

    for (Customer* customerPtr : m_customerPtrList) {
      { set<Book*>& loanPtrSet = customerPtr->loanPtrSet();
        int loanPtrSetSize = loanPtrSet.size();
        inStream.read((char*) &loanPtrSetSize,
          sizeof loanPtrSetSize);

        for (int count = 0; count < loanPtrSetSize; ++count) {
          int bookIndex;
          inStream.read((char*) &bookIndex, sizeof bookIndex);
          Book* bookPtr = lookupBookPtr(bookIndex);
          loanPtrSet.insert(bookPtr);
        }
      }

      { set<Book*>& reservationPtrSet =
          customerPtr->reservationPtrSet();
        int reservationPtrSetSize = reservationPtrSet.size();
        inStream.read((char*) &reservationPtrSetSize,
                      sizeof reservationPtrSetSize);

        for (int count = 0; count < reservationPtrSetSize;
             ++count) {
          int bookIndex;
          inStream.read((char*) &bookIndex, sizeof bookIndex);
          Book* bookPtr = lookupBookPtr(bookIndex);
          reservationPtrSet.insert(bookPtr);
        }
      }
    }
  }
}

Library::~Library() {
  for (const Book* bookPtr : m_bookPtrList) {
    delete bookPtr;
  }

  for (const Customer* customerPtr : m_customerPtrList) {
    delete customerPtr;
  }
}