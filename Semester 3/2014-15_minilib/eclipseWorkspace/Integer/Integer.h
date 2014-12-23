#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <string>
#include <iostream>
#include "MLObject.h"

using namespace std;
using namespace ML;

class Integer : public Object {
private:
    int value;
public:
    Integer(int value = 0);
    virtual ~Integer();
    virtual string asString() const;
    virtual bool IsEqualTo(const Object* o) const;
    virtual bool IsLessThen(const Object* o) const;
    virtual int getVal();
    virtual int setVal();
    operator int() const;

    friend istream& operator>> (istream& is, Integer& input);
};
#endif // INTEGER_H_INCLUDED
