class Customer {
  public:
    Customer();
    Customer(const string& name, const string& address);

//    Customer(const Customer& customer);
//    Customer& operator=(const Customer& customer);

    const string& name() const { return m_name; }
    const string& address() const { return m_address; }

    void read(ifstream& inStream);
    void write(ofstream& outStream) const;

    void borrowBook(Book* bookPtr);
    void returnBook(Book* bookPtr);
    void reserveBook(Book* bookPtr);
    void unreserveBook(Book* bookPtr);

    set<Book*>& loanPtrSet() { return m_loanPtrSet; }
    const set<Book*> loanPtrSet() const { return m_loanPtrSet; }

    set<Book*>& reservationPtrSet() { return m_reservationPtrSet; }
    const set<Book*> reservationPtrSet() const { return m_reservationPtrSet; }

    friend ostream& operator<<(ostream& outStream,
                               const Customer& customer);

  private:
    string m_name, m_address;
    set<Book*> m_loanPtrSet, m_reservationPtrSet;
};
