class Set : private LinkedList {
  public:
    Set();
    Set(double value);
    Set(const Set& set);
    void assign(const Set& set);
    ~Set();

    bool equal(const Set& set) const;
    bool notEqual(const Set& set) const;

    bool exists(double value) const;
    bool exists(const Set& set) const;

    bool insert(double value);
    bool insert(const Set& set);

    bool remove(double value);
    bool remove(const Set& set);

    int size() const { return LinkedList::size(); }
    bool empty() const { return LinkedList::empty(); }
    Iterator first() const { return LinkedList::first(); }

    friend Set unionSet(const Set& leftSet, const Set& rightSet);
    friend Set intersection(const Set& leftSet,
                            const Set& rightSet);
    friend Set difference(const Set& leftSet,
                          const Set& rightSet);

    void read(istream& inStream);
    void write(ostream& outStream);
};
