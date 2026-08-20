//========================================================
// Bach Nguyen
// List.cpp
// November 2023
// This file contains the class methods for the List class
//========================================================

#include <iostream>
#include <string>
#include "List.h"

using namespace std;

//========================================================
// default constructor
// Creates a new empty List object with type T
// Parameters:
//     None
// Return value: 
//     None
//========================================================
template <typename T>
              List<T>::List        (void) 
{
       capacity = DEFAULT_LIST_SIZE;
       size = 0;
       list = new T[capacity];
}

//========================================================
// copy constructor
// Creates a new List that is a copy of the existing list
// Parameters:
//     None
// Return value: 
//     None
//========================================================
template <typename T>
              List<T>::List        (const List<T> &l)
{
       capacity = l.capacity;
       size = l.size;
       list = new T[capacity];
       for (int i = 0; i < size; i++)
              *(list+i) = *(l.list+i);
}

//========================================================
// destructor
// Cleans up memory of the list
// Parameters:
//     None
// Return value: 
//     None
//========================================================
template <typename T>
              List<T>::~List       (void)
{      
       delete[] list;
}

//========================================================
// assignment operator
// Parameters:
//     Type T List reference to object
// Return value: 
//     Current object
//========================================================
template <typename T>
List<T>       List<T>::operator=   (const List<T> &l)
{
       delete[] list;

       capacity = l.capacity;
       size = l.size;
       list = new T[capacity];
       for (int i = 0; i < size; i++)
              list[i] = l.list[i];

       return *this;
}

//========================================================
// append
// Appends a new item onto the back of the list
// Parameters:
//     Type T item
// Return value: 
//     None
//========================================================
template <typename T>
void          List<T>::append      (T item)
{
       if (size == capacity)
              reallocate();

       list[size] = item;

       size++;
}

//========================================================
// insert
// Inserts a new value at the specified position. Valid 
// indices for the position are 0 ... length. Inserting 
// at position=length is like an append. Existing values 
// in the list are moved up one index location to make 
// room for the new item. A run-time error is generated 
// for an invalid index.
// Parameters:
//     Type T item, an integer for position
// Return value: 
//     None
//========================================================
template <typename T>
void          List<T>::insert      (T item, int position)
{
       if (position < 0 || position > size)
              cout << "Invalid index" << endl;
       else
       {
              if (size == capacity)
                     reallocate();

              if (position == size)
                     list[position] = item;
              else
              {
                     for(int i = size; i > position-1; i--)
                            list[i] = list[i-1];
              
                     list[position] = item;
              }   

              size++;
       }
}

//========================================================
// length
// Returns the number of items in the list
// Parameters:
//     None
// Return value: 
//     An integer for the number of items in the list
//========================================================
template <typename T>
int           List<T>::length      (void) const
{
       return size;
}

//========================================================
// operator[]
// Accesses (by reference) the item at the specified index
// A program-termination error is issued if the index is 
// invalid. Invalid indices are less than 0 or greater 
// than length-1.
// Parameters:
//     An integer for the position
// Return value: 
//     An integer for the number of items in the list
//========================================================
template <typename T>
T &           List<T>::operator[]  (int position)
{
       if (position < 0 || position > size-1)
              throw string("Invalid index");

       return list[position];
}

//========================================================
// remove
// Removes an item at the specified location. Valid 
// locations are 0...length-1. A run-time error is 
// generated for an invalid index
// Parameters:
//     An integer for the position
// Return value: 
//     None
//========================================================
template <typename T>
void          List<T>::remove      (int position)
{
       if (position < 0 || position > size-1)
              cout << "Invalid index" << endl;
       
       else
       {
              for(int i = position; i < size; i++)
                     list[i] = list[i+1];

              size--;
       }
}

//========================================================
// isEmpty
// Returns true if the list is empty, false otherwise
// Parameters:
//     None
// Return value: 
//     A boolean depending on if the list is empty or not
//========================================================
template <typename T>
bool          List<T>::isEmpty     (void) const
{
       return size == 0;
}

//========================================================
// operator+
// Concatenates two lists into a new list
// Does not change either existing list
// Parameters:
//     Type T List reference to object
// Return value: 
//     A type T List made from two lists
//========================================================
template <typename T>
List<T>       List<T>::operator+   (const List<T> &l) const
{
       List<T> result;
       result.capacity = capacity + l.capacity;
       result.size = size + l.size;
       delete [] result.list;
       result.list = new T[result.capacity];

       for (int i = 0; i < size; i++)
              result.list[i] = list[i];

       for (int i = 0; i < l.size; i++)
              result.list[size+i] = l.list[i];

       return result; 
}

//========================================================
// clear
// Removes all items from the list
// Parameters:
//     None
// Return value: 
//     None
//========================================================
template <typename T>
void          List<T>::clear       (void)
{
       for (int i = 0; i < size; i++)
              list[i].~T();
       size = 0;
}

//========================================================
// reallocate
// Create a new array that is twice the capacity of the 
// current array, copy the items from the current array 
// into the new array, delete the current array, and
// attach the new array to the list properly.
// Parameters:
//     None
// Return value: 
//     None
//========================================================
template <typename T>
void          List<T>::reallocate  (void)
{
       capacity = capacity * 2;
       T *new_list = new T[capacity];

       for (int i = 0; i < size; i++)
              *(new_list+i) = *(list+i);

       delete[] list;
       list = new_list;
}