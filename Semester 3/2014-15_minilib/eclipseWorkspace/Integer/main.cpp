#include <iostream>
#include <cstdlib>
#include <typeinfo>

#include "MLVector.h"
#include "MLString.h"
#include "Integer.h"

using namespace std;
using namespace ML;

int main() {
    cout << "------------------ Integer Tests ------------------" << endl << flush;

    Vector* vector = new Vector();
    for(int i = 0; i < 10; i++) {
        vector->Add(new Integer(rand() % 10));
    }

    cout << vector->AsString() << endl << flush;

    Iterator* it = vector->NewIterator();
    Object* o = it->Next();

    while(o != nullptr) {
        cout << o->AsString() << endl;
        o = it->Next();
    }

    delete it;
    vector->DeleteElements();
    delete vector;

    WriteMetaInfo();


    cout << "------------------ String Tests ------------------" << endl << flush;
    vector = new Vector();
    vector->Add(new String("test"));
    vector->Add(new String(" me"));
    vector->Add(new String(" please"));

    it = vector->NewIterator();
    o = it->Next();
    while(o != nullptr) {
        if(o->IsA("String*")) {
            cout << o->AsString();
            String* s = dynamic_cast<String*>(o);
            cout << "length: " << s->Length() << endl;
        }
        cout << o->AsString() << endl;
        o = it->Next();
    }

    delete it;
    vector->DeleteElements();
    delete vector;

    return 0;
}
