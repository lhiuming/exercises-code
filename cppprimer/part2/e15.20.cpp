// Exercise 15.20 (p616)
// Testing about inheritences.

class Base { };

class Pub_Derv : public Base {
  void memfcn(Base &b) { b = *this; } // conversion by member function }
};
class Priv_Derv : private Base {
  void memfcn(Base &b) { b = *this; } // conversion by member function }
};
class Prot_Derv : protected Base {
  void memfcn(Base &b) { b = *this; } // conversion by member function }
};

class Derived_from_Public : public Pub_Derv {
  void memfcn(Base &b) { b = *this; } // conversion by member function }
};
class Derived_from_Privated : public Priv_Derv {
  /* this would be illegal because the conversion is private in Priv_Derv,
   * not accessible by it's derived class */
  // void memfcn(Base &b) { b = *this; } // conversion by member function }
};
class Derived_from_Protected : public Prot_Derv {
  void memfcn(Base &b) { b = *this; } // conversion by member function }
};

int main() {
  // declare objects
  Pub_Derv d1;
  Priv_Derv d2;
  Prot_Derv d3;
  Derived_from_Public dd1;
  Derived_from_Privated dd2;
  Derived_from_Protected dd3;

  Base *p = &d1;
  //p = &d2; // illegal; conversion is private in d2
  //p = &d3; // illegal; conversion is protected in d3
  p = &dd1; // legal; conversion is public
  //p = &dd2; // illegal; conversion is private in d2, not accessible to dd2
  //p = &dd3; // illegal; conversion is proteced in d3, so accessible to dd3,
              // but it can not be publized by dd3 ; conversion is public ONLY
              // when the direct-inheritenace publicly inherits the base class.
  return 0;
}
