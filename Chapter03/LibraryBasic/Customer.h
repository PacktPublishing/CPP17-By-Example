class Customer {
  public:
    Customer(void);
    Customer(const string& name, const string& address);

    //Customer(const Customer& customer);
    //Customer& operator=(const Customer& customer);

    void read(ifstream& inStream);
    void write(ofstream& outStream) const;

    void borrowBook(int bookId);
    void returnBook(int bookId);
    void reserveBook(int bookId);
    void unreserveBook(int bookId);

    bool hasBorrowed(void) const { return !m_loanSet.empty(); }

    const string& name(void) const {return m_name;}
    const string& address(void) const { return m_address; }
    int id(void) const { return m_customerId; }

    static int MaxCustomerId;
    friend ostream& operator<<(ostream& outStream,
                               const Customer& customer);

  private:
    int m_customerId;
    string m_name, m_address;
    set<int> m_loanSet, m_reservationSet;
};