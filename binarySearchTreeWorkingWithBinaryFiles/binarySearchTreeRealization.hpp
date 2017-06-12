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

#ifndef BINARY_SEARCH_TREE_REALIZATION
#define BINARY_SEARCH_TREE_REALIZATION

#include<new>
#include<cstddef>	//NULL
#include<cassert>
#include<stdexcept>
#include "integerKeyAndCharPointer.h"

namespace fmi
{
namespace sdp
{
	//creates an empty tree
	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree()
		:root(NULL)
	{}

	template<typename T>
	inline BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other)
		: root(NULL)
	{
		copy(root, other.root);
	}

	template<typename T>
	inline BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& other)
	{
		if (this != &other)
		{
			Node *newTreeRoot = NULL;
			try
			{
				copy(newTreeRoot, other.root);
			}
			catch (std::bad_alloc &except)
			{
				clear(newTreeRoot);
				throw;
			}

			clear(root);
		
			root = newTreeRoot;
		}
		return *this;
	}

	template<typename T>
	inline BinarySearchTree<T>::~BinarySearchTree()
	{
		clear(root);
	}


	//adds a new value to the tree
	template<typename T>
	inline void BinarySearchTree<T>::add(const T& newValue)
	{
		add(root, newValue);
	}

	//removes the value from the tree, if found, and returns true;
	//else returns false;
	template<typename T>
	inline bool  BinarySearchTree<T>::remove(const T& value)
	{
		return remove(root, value);
	}

	// the function is equivalent to bool remove(const T& value);
	template<typename T>
	inline bool BinarySearchTree<T>::removeElementWithTheSameKey(const T& value)
	{
		return remove(value);
	}

	template<>
	inline bool BinarySearchTree<IntegerKeyAndCharPointer>
		::removeElementWithTheSameKey(const IntegerKeyAndCharPointer& value)
	{
			return removeElementWithTheSameKey(root, value);
	}

	//returns true if value is in the tree;
	//else returns false
	template<typename T>
	inline bool  BinarySearchTree<T>::search(const T& value) const
	{
		return search(root, value);
	}

	//adds a new value to the binary search tree, 
	//starting from root
	template<typename T>
	inline void  BinarySearchTree<T>::add(Node *&root, const T& newValue)
	{
		if (root == NULL)
		{
			root = new Node(newValue, NULL, NULL);
		}
		else
		{
			if (root->value < newValue)
			{
				add(root->right, newValue);
			}
			else //newValue <= root->value
			{
				add(root->left, newValue);
			}
		}
	}

	//removes value, if found in the binary search tree,
	//starting from root, and returns true;
	//else returns false;
	template<typename T>
	inline bool  BinarySearchTree<T>::remove(Node *&root, const T& value)
	{
		//if there is no such value in the tree, we can't remove it
		if (root == NULL)
		{
			return false;
		}

		if (root->value < value)
		{
			return remove(root->right, value);
		}

		if(value < root->value)
		{
			return remove(root->left, value);
		}

		assert(value == root->value);

		Node *tempNodeThatMustBeDeleted = NULL;

		//if root has no left son
		if (root->left == NULL)
		{
			tempNodeThatMustBeDeleted = root;
			root = root->right;
		}
		else
		{
			//if root has no right son
			if (root->right == NULL)
			{
				tempNodeThatMustBeDeleted = root;
				root = root->left;
			}
			else //the root has two sons
			{
				/*
				We will find the miminal value in the right subtree and place it
				in the Node which is pointed by root. That way the tree will 
				remain a binary search tree.
				*/

				Node*& pointerToMinElementInTheRightSubtree 
					= getPointerToMinElementInTree(root->right);

				root->value = pointerToMinElementInTheRightSubtree->value;

				//Now we have to remove the minimal Node which we found from the tree.
				tempNodeThatMustBeDeleted = pointerToMinElementInTheRightSubtree;

				pointerToMinElementInTheRightSubtree = pointerToMinElementInTheRightSubtree->right;
			}
		}
		delete tempNodeThatMustBeDeleted;

		//we have found the value and removed it successfully
		return true;
	}

	template<typename T>
	inline bool BinarySearchTree<T>::removeElementWithTheSameKey
		(Node *&root, const IntegerKeyAndCharPointer& value)
	{
		if (root == NULL)
		{
			return false;
		}

		if (root->value.key == value.key)
		{
			//we will use the ordinary function remove(Node *&root, const T&value)
			//from this point on
			IntegerKeyAndCharPointer valueForRemoval(root->value);
			return remove(root, valueForRemoval);
		}

		if (root->value.key < value.key)
		{
			return removeElementWithTheSameKey(root->right, value);
		}
		
		//value.key < root->value.key 
		return removeElementWithTheSameKey(root->left, value);
	}
	
	//returns a pointer to the minimal element in the tree, starting from root
	//!!!root must not be equal to NULL
	template <typename T>
	inline typename BinarySearchTree<T>::Node*& 
		BinarySearchTree<T>::getPointerToMinElementInTree(Node *&root)
	{
		if (root->left == NULL)
		{
			return root;
		}
		else
		{
			return getPointerToMinElementInTree(root->left);
		}
	}

	//searches for value in the binary search tree,
	//starting from root
	template<typename T>
	inline bool  BinarySearchTree<T>::search(const Node *root, const T& value)
	{
		if (root == NULL)
		{
			return false;
		}

		if (root->value < value)
		{
			return search(root->right, value);
		}

		if (value < root->value)
		{
			return search(root->left, value);
		}
		
		assert(root->value == value);

		return true;
	}

	//copies the content from one tree to another
	template<typename T>
	inline void BinarySearchTree<T>::copy(Node *&rootOfDestinationTree, const Node *rootOfSourceTree)
	{
		if (rootOfSourceTree != NULL)
		{
			rootOfDestinationTree = new Node(rootOfSourceTree->value, NULL, NULL);
			copy(rootOfDestinationTree->left, rootOfSourceTree->left);
			copy(rootOfDestinationTree->right, rootOfSourceTree->right);
		}
		else
		{
			rootOfDestinationTree = NULL;
		}
	}

	//Deletes the dinamically allocated data for the
	//binary search tree, starting from root
	template<typename T>
	inline void  BinarySearchTree<T>::clear(Node *root)
	{
		if (root != NULL)
		{
			clear(root->left);
			clear(root->right);
			delete root;
		}
	}

} //sdp
} //fmi

#endif //BINARY_SEARCH_TREE_REALIZATION