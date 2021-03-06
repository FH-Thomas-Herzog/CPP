/*
 * Directory.cpp
 * This is the implementation of the Directory specification
 *
 *  Created on: Jan 11, 2015
 *      Author: Thomas Herzog
 */
#include <sstream>
#include "Directory.h"

using namespace std;
using namespace ML;

////////////////////////////////////////////////////////////
// Constructor and Destructor                             //
////////////////////////////////////////////////////////////
Directory::Directory(const string & name) :
		FsNode(name) {
	Register(DIRECTORY_CLASS, FS_NODE_CLASS);
} /* Directory::Directory */

Directory::Directory(const Directory & other) :
		FsNode::FsNode(other) {
	/* avoid multiple registration */
	Register(DIRECTORY_CLASS, FS_NODE_CLASS);
} /* Directory::Directory */

Directory::~Directory() {
} /* Directory::~Directory */

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
Directory* Directory::clone() const {
	return new Directory(*this);
} /* Directory::clone */

string Directory::AsString() const {
	stringstream ss;
	ss << "Directory('" << name << "')";
	return ss.str();
} /* Directory::AsString */

void Directory::print(ostream & os) const {
	os << AsString();
} /* Directory::print */
