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

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include<cstddef>	//NULL
#include "integerKeyAndCharPointer.h"

namespace fmi
{
namespace sdp
{
	//This is a binary search tree in which the left son is less than
	//or equal to the father. The father is less than the right son.
	//
	//The data type T must have operator< and operator== defined
	//For every two variables T a; and T b; only one of the tree
	//relations must be true a<b, a==b or b<a
	template<typename T>
	class BinarySearchTree
	{
	public:

		//creates an empty tree
		BinarySearchTree();

		BinarySearchTree(const BinarySearchTree<T>& other);

		BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);

		~BinarySearchTree();

	public:
		//adds a new value to the tree
		void add(const T& newValue);
		
		//removes the value from the tree, if found, and returns true;
		//else returns false;
		bool remove(const T& value);

		//If T is IntegerKeyAndCharPointer, this function
		//removes an element in the tree with key equal to
		//value.key, if such element is found.
		//Else: the function is equivalent to bool remove(const T& value);
		bool removeElementWithTheSameKey(const T& value);

		//returns true if value is in the tree;
		//else returns false
		bool search(const T& value) const;

	private:
		struct Node
		{
			Node(const T& value, Node *left = NULL, Node *right = NULL)
			: value(value)
			, left(left)
			, right(right)
			{}

			T value;
			Node *left;
			Node *right;
		};
	
	private:
		Node *root;

	private:

		//adds a new value to the binary search tree, 
		//starting from root
		static void add(Node *&root, const T& newValue);

		//removes value, if found in the binary search tree,
		//starting from root, and returns true;
		//else returns false;
		static bool remove(Node *&root, const T& value);

		static bool removeElementWithTheSameKey(Node *&root, const IntegerKeyAndCharPointer& value);

		//returns a pointer to the minimal element in the tree, starting from root
		//!!!root must not be equal to NULL
		static Node*& getPointerToMinElementInTree(Node *&root);

		//searches for value in the binary search tree,
		//starting from root
		static bool search(const Node *root,  const T& value);

		//copies the content from one tree to another
		static void copy(Node *&rootOfDestinationTree, const Node *rootOfSourceTree);

		//Deletes the dinamically allocated data for the
		//binary search tree, starting from root
		static void clear(Node *root);
	};

} //sdp
} //fmi

#include "binarySearchTreeRealization.hpp"

#endif //BINARY_SEARCH_TREE