/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kamen Ivanov
* @idnumber 61894
* @task 4
* @compiler VC
*
*/

#include <iostream>
#include "binarySearchTree.h"
#include "integerKeyAndCharPointer.h"

using namespace fmi::sdp;

bool extractInformationFromBinaryFileAndPutItInBinarySearchTree
(const char *binaryFileName, BinarySearchTree<IntegerKeyAndCharPointer> &binarySearchTree);

void enterCommandsFromStandartInputAndChangeTreeIfNeccesary
(BinarySearchTree<IntegerKeyAndCharPointer> &binarySearchTree);

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		std::cerr << "the name of the binary file must be passed as command argument\n";
		return 1;
	}

	BinarySearchTree <IntegerKeyAndCharPointer> binarySearchTree;

	bool result 
	= extractInformationFromBinaryFileAndPutItInBinarySearchTree(argv[1], binarySearchTree);

	if (result)
	{
		enterCommandsFromStandartInputAndChangeTreeIfNeccesary(binarySearchTree);
	}

	return 0;
}