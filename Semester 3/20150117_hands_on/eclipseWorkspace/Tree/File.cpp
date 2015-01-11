/*
 * File.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: cchet
 */

#include <string>
#include <sstream>
#include "File.h"

using namespace std;
using namespace ML;

////////////////////////////////////////////////////////////
// Constructor and Destructor                             //
////////////////////////////////////////////////////////////
File::File(const string filename) :
		FsNode::FsNode(filename) {
	Register(FILE_CLASS, FS_NODE_CLASS);
}

File::File(const File & other) :
		FsNode::FsNode(other) {
	Register(FILE_CLASS, FS_NODE_CLASS);
}

File::~File() {
}

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
Node* File::getFirstChild() {
	return nullptr;
}

void File::setFirstChild(Node* node) {
	// Do nothing here
	cout << "File does not allow setting of a first child" << endl;
}

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
string File::AsString() const{
	stringstream ss;
	ss << "File('" << name << "')";
	return ss.str();
}

File* File::clone() const {
	return new File(*this);
}

void File::print(ostream & os) const {
	os << AsString();
}
