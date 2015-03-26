#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "person.h"


class student : public person {
  public:
    std::string registration_nr;

    student();
    student(std::string first_name, std::string last_name, std::string registration_nr);
    student(const student &s);
    virtual ~student();

  protected:
    virtual void print(std::ostream &os) const override;
    virtual void read(std::istream &is) override;
};

#endif // STUDENT_H
