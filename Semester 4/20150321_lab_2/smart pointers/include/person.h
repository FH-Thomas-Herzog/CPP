#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class person {
  friend std::ostream& operator << (std::ostream &os, const person &p);
  friend std::istream& operator >> (std::istream &os, person &p);

  public:
    std::string first_name, last_name;

    person();
    person(std::string first_name, std::string last_name);
    person(const person &p);
    virtual ~person();

    bool operator < (const person &p) const;

  protected:
    virtual void print(std::ostream &os) const;
    virtual void read(std::istream &os);
};

#endif // PERSON_H
