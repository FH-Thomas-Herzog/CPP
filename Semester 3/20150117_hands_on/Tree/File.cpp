/*
 * File.cpp
 * This is the implementation of the File specification
 *
 *  Created on: Jan 11, 2015
 *      Author: Thomas Herzog
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
} /* File::File */

File::File(const File & other) :
		FsNode::FsNode(other) {
	Register(FILE_CLASS, FS_NODE_CLASS);
} /* File::File */

File::~File() {
} /* File::~File */

////////////////////////////////////////////////////////////
// Getter and Setter                                      //
////////////////////////////////////////////////////////////
FsNode* File::getFirstChild() const {
	return nullptr;
} /* File::getFirstChild */

void File::setFirstChild(FsNode* node) {
	// Do nothing here
	cout << "File does not allow setting of a first child" << endl;
} /* File::setFirstChild */

////////////////////////////////////////////////////////////
// Utils                                                  //
////////////////////////////////////////////////////////////
string File::AsString() const {
	stringstream ss;
	ss << "File('" << name << "')";
	return ss.str();
} /* File::AsString */

File* File::clone() const {
	return new File(*this);
} /* File::clone */

void File::print(ostream & os) const {
	os << AsString();
} /* File::print */
