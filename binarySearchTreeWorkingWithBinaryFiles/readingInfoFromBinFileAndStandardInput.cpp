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
#include<cstdint>
#include<exception>
#include<cassert>
#include "binarySearchTree.h"
#include "integerKeyAndCharPointer.h"

using namespace fmi::sdp;
using namespace std;

bool extractInformationFromBinaryFileAndPutItInBinarySearchTree
(const char* binaryFileName, BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree);

static void quickSortElements
(IntegerKeyAndCharPointer *listOfElements, int indexOfLeftMostElement, int indexOfRightMostElement);

static void addElementsFromListToTreeToMakeItPerfectlyBallanced
(
IntegerKeyAndCharPointer *sortedListOfElements, int leftMostIndex, int rightMostIndex
, BinarySearchTree<IntegerKeyAndCharPointer> &tree
);

//appends the content of buffer to str, including a null terminating character
static void  addContentOfBufferToStr
(char *&str, const char *buffer, int &sizeOfDinamicallyAllocatedMemoryForStr);


static void enterStringFromStandardInput
(char *&str, int &sizeOfDinamicallyAllocatedMemoryForStr);


void enterCommandsFromStandartInputAndChangeTreeIfNeccesary
(BinarySearchTree<IntegerKeyAndCharPointer> &binarySearchTree);

void enterElementAndAddItToTheTree
(IntegerKeyAndCharPointer& bufferElement
, BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree, int& sizeOfDynamicMemoryForString);

void enterElementAndRemoveItFromTheTree
(IntegerKeyAndCharPointer& bufferElement
, BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree, int& sizeOfDynamicMemoryForString);

void enterKeyAndRemoveAllElementsWithThisKeyFromTheTree
(BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree);

void enterElementAndSearchForItInTheTree
(IntegerKeyAndCharPointer& bufferElement
, const BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree, int& sizeOfDynamicMemoryForString);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function definitions



//appends the content of buffer to str, including a null terminating character
static void  addContentOfBufferToStr
(char *&str, const char *buffer, int &sizeOfDinamicallyAllocatedMemoryForStr)
{
	int lengthOfBuffer = strlen(buffer);

	int lengthOfStr = ((str == NULL) ? 0 : strlen(str));

	if (sizeOfDinamicallyAllocatedMemoryForStr < lengthOfStr + lengthOfBuffer + 1)
	{
		char* newBuffer = new char[lengthOfBuffer + lengthOfStr + 1];

		sizeOfDinamicallyAllocatedMemoryForStr = lengthOfBuffer + lengthOfStr + 1;

		//str could be NULL, so we can't use strcpy()
		strncpy(newBuffer, str, lengthOfStr);

		delete[] str;
		str = newBuffer;
	}

	//this function automanically apppends '\0' at the end of str
	strcpy(&str[lengthOfStr], buffer);
}

static void enterStringFromStandardInput
(char *&str, int &sizeOfDinamicallyAllocatedMemoryForStr)
{
	assert(
		sizeOfDinamicallyAllocatedMemoryForStr >= 0 &&
		!(str == NULL && sizeOfDinamicallyAllocatedMemoryForStr != 0)
		);

	static const int sizeOfBuffer = 100;

	static char buffer[sizeOfBuffer];

	//we'll make the length of str zero
	if (str != NULL)
		str[0] = '\0';

	while (cin.good())
	{
		cin.getline(buffer, sizeOfBuffer);

		addContentOfBufferToStr(str, buffer, sizeOfDinamicallyAllocatedMemoryForStr);

		if (cin.good() || cin.eof())
			break;

		//the failbit of cin is on because the content to read is too big.
		//So we must read the remaining part of the content.
		cin.clear();
	}
}


void enterElementAndAddItToTheTree
(IntegerKeyAndCharPointer& bufferElement
, BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree, int& sizeOfDynamicMemoryForString)
{
	cin >> bufferElement.key;
	
	//extract ' '
	cin.ignore();

	if (cin)
	{
		enterStringFromStandardInput(bufferElement.data, sizeOfDynamicMemoryForString);
	}

	binarySearchTree.add(bufferElement);
}

void enterElementAndRemoveItFromTheTree
(IntegerKeyAndCharPointer& bufferElement
, BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree, int& sizeOfDynamicMemoryForString)
{
	cin >> bufferElement.key;

	//extract ' '
	cin.ignore();

	if (cin)
	{
		enterStringFromStandardInput(bufferElement.data, sizeOfDynamicMemoryForString);
	}

	cout << boolalpha<<binarySearchTree.remove(bufferElement) << noboolalpha << endl;
}


void enterKeyAndRemoveAllElementsWithThisKeyFromTheTree
(BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree)
{
	int32_t key;
	cin >> key;
	
	if (cin)
	{
		IntegerKeyAndCharPointer element;
		element.key = key;
		
		int numberOfElementsRemovedFromTree = 0;

		while (binarySearchTree.removeElementWithTheSameKey(element))
			++numberOfElementsRemovedFromTree;

		cout << numberOfElementsRemovedFromTree<<endl;
	}

	//extract '\n'
	cin.ignore();
}

void enterElementAndSearchForItInTheTree
(IntegerKeyAndCharPointer& bufferElement
, const BinarySearchTree<IntegerKeyAndCharPointer>& binarySearchTree, int& sizeOfDynamicMemoryForString)
{
	cin >> bufferElement.key;

	//extract ' '
	cin.ignore();

	if (cin)
	{
		enterStringFromStandardInput(bufferElement.data, sizeOfDynamicMemoryForString);
	}

	cout << boolalpha << binarySearchTree.search(bufferElement) << noboolalpha << endl;
}

static void addElementsFromListToTreeToMakeItPerfectlyBallanced
(
IntegerKeyAndCharPointer *sortedListOfElements,int leftMostIndex, int rightMostIndex
, BinarySearchTree<IntegerKeyAndCharPointer> &tree
)
{
	if (leftMostIndex <= rightMostIndex)
	{
		int middleIndex = (leftMostIndex + rightMostIndex) / 2;

		tree.add(sortedListOfElements[middleIndex]);

		addElementsFromListToTreeToMakeItPerfectlyBallanced
			(sortedListOfElements, leftMostIndex, middleIndex - 1, tree);

		addElementsFromListToTreeToMakeItPerfectlyBallanced
			(sortedListOfElements, middleIndex + 1, rightMostIndex, tree);
	}
}


static void quickSortElements
(IntegerKeyAndCharPointer *listOfElements, int indexOfLeftMostElement, int indexOfRightMostElement)
{
	if (indexOfLeftMostElement < indexOfRightMostElement)
	{
		int indexOfLastElement = indexOfLeftMostElement;
		
		for (int i = indexOfLeftMostElement + 1; i <= indexOfRightMostElement; ++i)
		{
			if (listOfElements[i] < listOfElements[indexOfLeftMostElement])
				listOfElements[i].swap(listOfElements[++indexOfLastElement]);
		}
		
		listOfElements[indexOfLeftMostElement].swap(listOfElements[indexOfLastElement]);

		quickSortElements(listOfElements, indexOfLeftMostElement, indexOfLastElement - 1);
		quickSortElements(listOfElements, indexOfLastElement + 1, indexOfRightMostElement);

	}
}



bool extractInformationFromBinaryFileAndPutItInBinarySearchTree
(const char *binaryFileName, BinarySearchTree<IntegerKeyAndCharPointer> &binarySearchTree)
{
	ifstream binaryFile(binaryFileName, ios::in | ios::binary);
	if (!binaryFile)
	{
		cerr << "could not open " << binaryFileName << " for reading\n";
		return false;
	}

	/*
	We can't just add the elements from the file in the binary search tree.
	We want the tree to be perfectly ballanced. That's why we firstly have
	to put the elements in a list and sort them.
	*/

	//this list will store all elements from the file
	IntegerKeyAndCharPointer *listOfElements = NULL;

	try
	{
		int numberOfElementsInBinaryFile = 0;

		//buffer in which we'll store the data of a single element
		//read from the file
		IntegerKeyAndCharPointer element;

		uint32_t sizeOfDinamicMemoryForStringInElement = 100;

		//!!!We must not delete this memory. The dtor of the class will do it for us!!!
		element.data = new char[sizeOfDinamicMemoryForStringInElement];

		//firstly, we want to find the number of elements in the binary file
		do
		{
			//extracting information for a single element from the file
			readDataFromBinaryFile(binaryFile, element, sizeOfDinamicMemoryForStringInElement);
			
			//if the operation was successfull
			if (binaryFile)
				++numberOfElementsInBinaryFile;

		} 
		while (binaryFile);

		if (numberOfElementsInBinaryFile <= 0)
		{
			cerr << "the file is empty\n";
			binaryFile.close();
			return false;
		}

		listOfElements = new IntegerKeyAndCharPointer[numberOfElementsInBinaryFile];

		binaryFile.clear();
		binaryFile.seekg(0, ios::beg);


		//we know the number of lements in the file, so now
		//we will read them.
		for (int i = 0; i < numberOfElementsInBinaryFile; ++i)
		{
			sizeOfDinamicMemoryForStringInElement = 0;
			readDataFromBinaryFile(binaryFile, listOfElements[i], sizeOfDinamicMemoryForStringInElement);
		}

		//we' ll sort the elements in the list
		quickSortElements(listOfElements, 0, numberOfElementsInBinaryFile - 1);

		addElementsFromListToTreeToMakeItPerfectlyBallanced
			(listOfElements, 0, numberOfElementsInBinaryFile - 1, binarySearchTree);
	}
	catch (exception& except)
	{
		cerr << except.what() << '\n';
		delete[] listOfElements;
		binaryFile.close();
		return false;
	}

	delete[] listOfElements;
	binaryFile.close();
	return true;
}



void enterCommandsFromStandartInputAndChangeTreeIfNeccesary
(BinarySearchTree<IntegerKeyAndCharPointer> &binarySearchTree)
{
	static const char* addElement = "add";
	static const char* removeElement = "remove";
	static const char* removeAllElementsWhitThisKey = "removeall";
	static const char* searchElement = "search";

	const int sizeOfCommandBuffer = 30;

	char commandBuffer[sizeOfCommandBuffer];

	IntegerKeyAndCharPointer bufferElement;

	int sizeOfDynamicMemoryForString = 100;

	//this memory must not be deleted. The dtor of the class
	//will do it for us!!!
	bufferElement.data = new char[sizeOfDynamicMemoryForString] {};

	while (cin.good())
	{

		//read the command and remove ' '
		cin.getline(commandBuffer, sizeOfCommandBuffer, ' ');
		
		if (cin.eof())
			return;

		//if the user has entered too many characters, the failbit will be switched on
		if (cin.fail())
		{
			cerr << "command is too long and therefore invalid\n";
			return;
		}

		if (strcmp(commandBuffer, addElement) == 0)
			enterElementAndAddItToTheTree
			(bufferElement, binarySearchTree, sizeOfDynamicMemoryForString);

		else if (strcmp(commandBuffer, removeElement) == 0)
			enterElementAndRemoveItFromTheTree
			(bufferElement, binarySearchTree, sizeOfDynamicMemoryForString);

		else if (strcmp(commandBuffer, removeAllElementsWhitThisKey) == 0)
			enterKeyAndRemoveAllElementsWithThisKeyFromTheTree(binarySearchTree);

		else if (strcmp(commandBuffer, searchElement) == 0)
			enterElementAndSearchForItInTheTree
			(bufferElement, binarySearchTree, sizeOfDynamicMemoryForString);

		else
		{
			cerr << "invalid command\n";
			return;
		}
	}
}