class Library {
  public:
    Library();

  private:
    static string s_binaryPath;

    bool lookupBook(const string& author, const string& title,
                    Book* bookPtr = nullptr);
    bool lookupCustomer(const string& name, const string& address,
                        Customer* customerPtr = nullptr);

    void addBook(void);
    void deleteBook(void);
    void listBooks(void);
    void addCustomer(void);
    void deleteCustomer(void);
    void listCustomers(void);
    void borrowBook(void);
    void reserveBook(void);
    void returnBook(void);

    void load();
    void save();

  public:
    static map<int,Book> s_bookMap;
    static map<int,Customer> s_customerMap;

    static map<int,int> bookLoanMap;
    static map<int,set<int>> bookReservationSetMap;

    static map<int,set<int>> customerLoanSetMap;
    static map<int,set<int>> customerReservationSetMap;
};