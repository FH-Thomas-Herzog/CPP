#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include <set>
#include <ostream>

class Entry {
  protected:
    std::string word;
    std::set<int> lineNrs;
  public:
    Entry(std::string word);
    virtual ~Entry();
    void addLineNr(int lnr);
    bool operator < (const Entry &e) const;
    friend std::ostream & operator <<  (std::ostream &os, const Entry &e);
};

#endif // ENTRY_H
