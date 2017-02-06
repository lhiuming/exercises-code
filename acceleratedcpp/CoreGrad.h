#ifndef GUARD_CoreGrad_h
#define GUARD_CoreGrad_h

#include <string>
#include <vector>
#include <iostream>
#include <exception>

class Core {
  // friend ship; not inherentable
  friend class Student_info; // allow access to all member functions
public:
  Core(): midterm(0), final(0) {
    std::cout << "Construct: Core()" << std::endl;
  }
  Core(std::istream& is) {
    std::cout << "Construct: Core(std::istream&)" << std::endl;
    read(is);
  }

  std::string name() const; // why not define here?

  virtual std::istream& read(std::istream&);
  virtual double grade() const;

protected: // accessible by derived class, and friend.
  std::istream& read_common(std::istream&);
  double midterm, final;
  std::vector<double> homework;
  virtual Core* clone() const { return new Core(*this); }

private: // accessible only to Core
  std::string n;
};

class Grad: public Core { // inherent elements and all public interfaces
public:
  Grad(): thesis(0) {
    std::cout << "Construct: Grad()" << std::endl;
  }
  Grad(std::istream& is) {
    std::cout << "Construct:Grad(istream&)" << std::endl;
    read(is);
  }

  double grade() const;
  std::istream& read(std::istream&);
protected:
  Grad* clone() const { return new Grad(*this); } // inherently virtual
private:
  double thesis;
};

bool compare(const Core&, const Core&);
bool compare_grades(const Core&, const Core&);

class Student_info {
public:
  // contruction and copy
  Student_info(): cp(0) {}
  Student_info(std::istream& is): cp(0) { read(is); }
  Student_info(const Student_info&); // copy op: not defined
  Student_info& operator=(const Student_info&); // assign op: not defined
  ~Student_info() { delete cp; }

  // operations
  std::istream& read(std::istream&);

  std::string name() const {
    if (cp) return cp->name();
    else throw std::runtime_error("uninitialized Student");
  }
  double grade() const {
    if (cp) return cp->grade();
    else throw std::runtime_error("uninitialized Student");
  }
  static bool compare(const Student_info& s1, const Student_info& s2) {
    return s1.name() < s2.name();
  }

private:
  Core* cp;
};

#endif
