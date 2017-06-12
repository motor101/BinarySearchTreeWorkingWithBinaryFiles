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

#ifndef INTEGER_AND_CHAR_POINTER_H
#define INTEGER_AND_CHAR_POINTER_H

#include<iostream>
#include <cstdint>	//int32_t, uint32_t

namespace fmi
{
namespace sdp
{
	//This is a very simple data type. It doesn't fit all of the
	//object oriented requirements. However it is suitable for the
	//current task: we will use this data type to read data from 
	//the binary file and store it in a binary search tree. 	
	class IntegerKeyAndCharPointer
	{
	public:
		IntegerKeyAndCharPointer(int32_t key = 0);

		IntegerKeyAndCharPointer(const IntegerKeyAndCharPointer& other);

		IntegerKeyAndCharPointer& operator=(const IntegerKeyAndCharPointer& other);

		~IntegerKeyAndCharPointer();
	
	public:
		void swap(IntegerKeyAndCharPointer& other);

	public:
		int32_t key;

		char* data;
	};

	//compares the two elements firstly by their keys;
	//if the keys are equal, compares the elements by their strings;
	//The two strings must be non NULL!!!
	bool operator< (const IntegerKeyAndCharPointer& elem1, const IntegerKeyAndCharPointer& elem2);

	//The two elements are equal if their keys and strings are equal;
	//The two strings must be non NULL!!!
	bool operator==(const IntegerKeyAndCharPointer& elem1, const IntegerKeyAndCharPointer& elem2);

	//reads information from a binary file. And stores it in element
	//The data format in the binary file is as follows:
	//&int32_t for key,
	//&uint32_t for sizeOfData,
	//char* for data
	void readDataFromBinaryFile(std::istream& binaryInputFile
		, IntegerKeyAndCharPointer& element, uint32_t &sizeOfDinamicMemoryForTheDataStringInElement);

} //sdp
} //fmi

#endif	//INTEGER_AND_CHAR_POINTER_H