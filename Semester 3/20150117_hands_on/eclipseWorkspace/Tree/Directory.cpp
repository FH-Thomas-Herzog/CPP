/*
 * Directory.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: cchet
 */
#include <sstream>
#include "Directory.h"

using namespace std;
using namespace ML;

Directory::Directory(const string & name) :
		FsNode(name) {
	/* avoid multiple registration */
	Register(DIRECTORY_CLASS, FS_NODE_CLASS);
}

Directory::Directory(const Directory & other) :
		FsNode::FsNode(other) {
	/* avoid multiple registration */
	if (other.Class().compare(DIRECTORY_CLASS) == 0) {
		Register(DIRECTORY_CLASS, FS_NODE_CLASS);
	}
}

Directory::~Directory() {
}

Directory* Directory::clone() const {
	return new Directory(*this);
}

string Directory::AsString() const {
	stringstream ss;
	ss << "Directory('" << name << "')";
	return ss.str();
}

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
void Directory::print(ostream & os) const {
	os << AsString();
}
