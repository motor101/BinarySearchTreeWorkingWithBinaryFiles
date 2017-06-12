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
#include<cstdint>	//uint32_t, int32_t
#include<cstddef>	//NULL
#include<cstring>
#include<exception>
#include "integerKeyAndCharPointer.h"

using namespace std;

namespace fmi
{
namespace sdp
{
	IntegerKeyAndCharPointer::IntegerKeyAndCharPointer(int32_t key) 
		: key(key)
		, data(NULL)
	{}

	IntegerKeyAndCharPointer::IntegerKeyAndCharPointer(const IntegerKeyAndCharPointer& other)
		: key(other.key)
		, data(NULL)
	{
		if (other.data!=NULL)
		{
			data=new char[strlen(other.data) + 1];
			strcpy(data, other.data);
		}
	}

	IntegerKeyAndCharPointer& IntegerKeyAndCharPointer::operator=(const IntegerKeyAndCharPointer& other)
	{
		if (this != &other)
		{
			char *newData = NULL;

			if (other.data != NULL)
			{
				newData = new char[strlen(other.data) + 1];
				strcpy(newData, other.data);
			}

			delete[] data;

			data = newData;
			key = other.key;
		}
		return *this;
	}

	IntegerKeyAndCharPointer::~IntegerKeyAndCharPointer()
	{
		delete[] data;
	}


	void IntegerKeyAndCharPointer::swap(IntegerKeyAndCharPointer& other)
	{
		int32_t tempKey = this->key;
		this->key = other.key;
		other.key = tempKey;

		char *tempData = this->data;
		this->data = other.data;
		other.data = tempData;
	}

	//compares the two elements firstly by their keys;
	//if the keys are equal, compares the elements by their strings;
	//The two strings must be non NULL!!!
	bool operator<(const IntegerKeyAndCharPointer& elem1, const IntegerKeyAndCharPointer& elem2)
	{
		if (elem1.key < elem2.key)
			return true;

		if (elem2.key < elem1.key)
			return false;

		//elem1.key and elem2.key are equal

		if(strcmp(elem1.data, elem2.data) < 0)
			return true;

		return false;
	}

	//The two elements are equal if their keys and strings are equal;
	//The two strings must be non NULL!!!
	bool operator==(const IntegerKeyAndCharPointer& elem1, const IntegerKeyAndCharPointer& elem2)
	{
		return (elem1.key == elem2.key) && (strcmp(elem1.data, elem2.data) == 0);
	}

	//reads information from a binary file. And stores it in element
	//The value of sizeOfDinamicMemory will increase if the new string, 
	//read from the file is bigger than the current!!!
	//The data format in the binary file is as follows:
	//&int32_t for key,
	//&uint32_t for sizeOfData,
	//char* for data
	void readDataFromBinaryFile(std::istream& binaryInputFile
		, IntegerKeyAndCharPointer& element, uint32_t &sizeOfDinamicMemoryForTheDataStringInElement)
	{
		binaryInputFile.read ((char*)&element.key, sizeof(element.key));
		if (!binaryInputFile)
			return;

		uint32_t sizeOfCurrentStringInFile;

		binaryInputFile.read((char*)&sizeOfCurrentStringInFile, sizeof(sizeOfCurrentStringInFile));
		if (!binaryInputFile)
			throw std::exception("the file is incorrect");

		//if the memory, needed for the new string,
		//is larger than the current allocated dynamic memory,
		//we have to reallocate it
		if (element.data == NULL
			||
			sizeOfDinamicMemoryForTheDataStringInElement < sizeOfCurrentStringInFile + 1)
		{
			delete[] element.data;

			//if the request for dynamic memory beneeth fails, the dtor will
			//delete an invalid pointer. Thus, we have to make it NULL
			element.data = NULL;

			sizeOfDinamicMemoryForTheDataStringInElement = sizeOfCurrentStringInFile + 1;

			element.data = new char[sizeOfDinamicMemoryForTheDataStringInElement];
		}

		binaryInputFile.read(element.data, sizeOfCurrentStringInFile);
		if (!binaryInputFile)
			throw std::exception("the file is incorrect");

		element.data[sizeOfCurrentStringInFile] = '\0';

	}

} //sdp
} //fmi