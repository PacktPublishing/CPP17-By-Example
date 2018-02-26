class Employee : public Person {
  public:
    Employee(string name, string company);
    void print();

  private:
    string m_company;
};