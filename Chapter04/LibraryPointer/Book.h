class Customer;

class Book {
  public:
    Book();
    Book(const string& author, const string& title);

//    Book(const Book& book);
//    Book& operator=(const Book& book);

    const string& author() const { return m_author; }
    const string& title() const { return m_title; }

    void read(ifstream& inStream);
    void write(ofstream& outStream) const;

    void borrowBook(Customer* customerPtr);
    int reserveBook(Customer* customerPtr);
    void returnBook();
    void removeReservation(Customer* customerPtr);

    Customer*& borrowerPtr() { return m_borrowerPtr; }
    const Customer* borrowerPtr() const { return m_borrowerPtr; }

    list<Customer*>& reservationPtrList()
                     { return m_reservationPtrList; }
    const list<Customer*> reservationPtrList() const
                          { return m_reservationPtrList; }

    friend ostream& operator<<(ostream& outStream,
                               const Book& book);

  private:
    string m_author, m_title;
    Customer* m_borrowerPtr = nullptr;
    list<Customer*> m_reservationPtrList;
};