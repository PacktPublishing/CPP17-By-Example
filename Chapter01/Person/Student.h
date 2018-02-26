class Student : public Person {
  public:
    Student(string name, string university);
    void print();

  private:
    string m_university;
};