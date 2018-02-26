class Library {
  public:
    Library();
    ~Library();

  private:
    static string s_binaryPath;

    Book* lookupBook(const string& author, const string& title);
    Customer* lookupCustomer(const string& name,
                             const string& address);

    void addBook();
    void deleteBook();
    void listBooks();
    void addCustomer();
    void deleteCustomer();
    void listCustomers();
    void borrowBook();
    void reserveBook();
    void returnBook();

    int lookupBookIndex(const Book* bookPtr);
    int lookupCustomerIndex(const Customer* customerPtr);

    Book* lookupBookPtr(int bookIndex);
    Customer* lookupCustomerPtr(int customerIndex);

    void save();
    void load();

    list<Book*> m_bookPtrList;
    list<Customer*> m_customerPtrList;
};