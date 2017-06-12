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

#include<iostream>
#include<fstream>
#include "integerKeyAndCharPointer.h"
#include "binarySearchTree.h"

using namespace std;
using namespace fmi::sdp;


/*
namespace fmi
{
	namespace sdp
	{
		class SimpleClass
		{
		public:
			SimpleClass(int value=0) :value(value)
			{}

			void setValue(int value)
			{
				this->value = value;
			}

			bool operator<(const SimpleClass& other)const
			{
				return value < other.value;
			}

			bool operator==(const SimpleClass& other)const
			{
				return value == other.value;
			}

			friend ostream& operator<<(ostream& out, const SimpleClass& simpleClass)
			{
				out << simpleClass.value;
				return out;
			}
		private:
			int value;
		};
	} //sdp
} //fmi



void binarySearchTreeTests()
{
	cout << "testing default ctor...\n";
	BinarySearchTree<SimpleClass> tree1;

	cout << "tree1: ";
	tree1.inorderPrint();


	cout << "testing add()...\n";
	tree1.add(5);
	tree1.add(3);
	tree1.add(4);
	tree1.add(2);
	tree1.add(5);
	tree1.add(7);
	tree1.add(6);
	tree1.add(8);

	cout << "tree1: ";
	tree1.inorderPrint();

	cout << "testing copy ctor()...\n";
	cout << "tree2=tree1\n";
	const BinarySearchTree<SimpleClass> tree2(tree1);
	
	cout << "tree2: ";
	tree2.inorderPrint();

	SimpleClass elementForSearching;

	cout << "testing search() in tree2 ctor...\n";
	elementForSearching.setValue(5);
	cout << elementForSearching << " is " << (tree2.search(elementForSearching) ? "found" : "not found") << endl;;

	elementForSearching.setValue(-1);
	cout << elementForSearching << " is " << (tree2.search(elementForSearching) ? "found" : "not found") << endl;;

	elementForSearching.setValue(8);
	cout << elementForSearching << " is " << (tree2.search(elementForSearching) ? "found" : "not found") << endl;;

	elementForSearching.setValue(4);
	cout << elementForSearching << " is " << (tree2.search(elementForSearching) ? "found" : "not found") << endl;;


	cout << "testing remove()...\n";

	elementForSearching.setValue(-1);
	cout << elementForSearching << " is " << (tree1.remove(elementForSearching)
		? "successfully removed" : "not found") << endl;;
	cout << "tree1: ";
	tree1.inorderPrint();

	elementForSearching.setValue(5);
	cout << elementForSearching << " is " << (tree1.remove(elementForSearching)
		? "successfully removed" : "not found") << endl;;
	cout << "tree1: ";
	tree1.inorderPrint();

	elementForSearching.setValue(3);
	cout << elementForSearching << " is " << (tree1.remove(elementForSearching)
		? "successfully removed" : "not found") << endl;;
	cout << "tree1: ";
	tree1.inorderPrint();

	elementForSearching.setValue(8);
	cout << elementForSearching << " is " << (tree1.remove(elementForSearching)
		? "successfully removed" : "not found") << endl;;
	cout << "tree1: ";
	tree1.inorderPrint();

	cout << "testing operator=()...\n";
	tree1 = tree2;

	cout << "tree1: ";
	tree1.inorderPrint();


}

void integerKeyAndCharPointerTest(const char* nameOfBinaryFile)
{
	IntegerKeyAndCharPointer element;

	uint32_t sizeOfDynamicMemory=0;

	ifstream binaryFile(nameOfBinaryFile, ios::in | ios::binary);
	if (!binaryFile)
	{
		cerr << "could not open " << nameOfBinaryFile << " for reading\n";
		return;
	}

	do
	{
		readDataFromBinaryFile(binaryFile, element, sizeOfDynamicMemory);
		if (binaryFile)
		{
			cout << "key = " << element.key << endl
				<< "data = " << element.data << endl;
		}
	} while (binaryFile);

}

*/