/*list.cpp*/

//
// Author: Prof. Hummel, U. of I. Chicago, Spring 2021
// Updated by: Manav Gupta
// Assignment: Project 6
// Date: 30th April, 2021
// 
// Implements a one-way linked-list with optimized insertion at
// head and tail of list. The nodes contain 2 data values, a string
// and an integer.
//

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "list.h"

using namespace std;



//
// private member functions:
//

//
// inits this list then makes deep copy of other
//
// Time complexity: O(N)
//
void List::initAndDeepCopy(const List& other)
{
   //
   // TODO: init this list, then make copy of other
   //
    this->Head = nullptr; // set head to nullptr as list is empty
    this->Tail = nullptr; // set tail to nullptr as list is empty
    this->Count = 0; // set count to 0 as list is empty
    
    Node* cur = other.Head; // cur = head or first node of other list
     while (cur != nullptr) // while not cur is not nullptr
     {
         this->push_back(cur->Data.Value1, cur->Data.Value2); // push back function called (look at comments for push back for more information)
         cur = cur->Next; // keeps loop going and updating the cur values
     }
}


// 
// free the nodes in the list and resets to empty
//
// Time complexity: O(N)
//
void List::freeAndReset()
{
   //
   // TODO: free this list, then reset to empty
   //
    Node* cur = this->Head; // cur is first node of list
    Node* prev = nullptr;
    
    while (cur != nullptr) // while cur is not nullptr
    {
        prev = cur; // prev becomes cur
        cur = cur->Next; // cur traverses forward
        delete prev; // prev is deleted as it is not needed
        // the loop keeps going until cur points to nullptr and all nodes are deleted
    }
    this->Count = 0; // count is reset to 0
    this->Head = nullptr; // head is reset to point to nullptr
    this->Tail = nullptr; // tail is reset to point to nullptr
    
}


//
// public member functions:
//

//
// default constructor
//
// Initializes the list to empty.
// 
// Time complexity: O(1)
//
List::List()
{
   this->Head = nullptr;
   this->Tail = nullptr;
   this->Count = 0;
}

//
// copy constructor
//
// Makes a deep copy of the other list into this list.
// 
// Time complexity: O(N)
//
List::List(const List& other)
{
   this->initAndDeepCopy(other);
}

//
// destructor
//
// Frees all memory related to this list, and then resets to empty.
// 
// Time complexity: O(N)
//
List::~List()
{
   this->freeAndReset();
}

//
// assignment operator (e.g. L2 = L;)
//
// Makes a deep copy of the other list into this list; since this
// list already exists, the existing elements of this list are freed
// before the copy is made.
// 
// Time complexity: O(N)
//
List& List::operator=(const List& other)
{
   if (this == &other)  // special case: check for L = L;
      return *this;     // do nothing and just return THIS object back

   //
   // This is different from a copy constructor, because "this" list
   // exists and contains nodes.  So we have to free "this" list before
   // we copy the "other" list:
   //
   this->freeAndReset();
   this->initAndDeepCopy(other);

   return *this;  // done, return THIS object back
}

//
// size
//
// Returns the # of elements in the list.
//
// Time complexity: O(1)
//
int List::size()
{
   //
   // TODO:
   //
   return this->Count; // returns the count of this list
}

//
// empty
//
// Returns true if empty, false if not.
//
// Time complexity: O(1)
//
bool List::empty()
{
   //
   // TODO:
   if(this->Head == nullptr) // if head points to nullptr, then list is empty, hence...
       return true; // true is returned
    
   return false; // otherwise false is returned
}

//
// search
//
// Search the list for the first occurence of the string value.
// If found, its position in the list is returned. Positions are 
// 0-based, meaning the first node is position 0. If the value is
// not found, -1 is returned.
//
// Time complexity: on average O(N)
//
int List::search(string value)
{
   //
   // TODO:
   //
    Node* cur = this->Head; // cur points to this head
    int pos = 0; // 0 for current position
    while (cur != nullptr)
    {
        if (cur->Data.Value1 == value) // if the value given is found...
            return pos; // position is returned
        cur = cur->Next; // keeps loop going
        pos++; // position updates depending on the amount of loops made
    }
    return -1; // if value is not found in the list, then -1 is returned
}

//
// retrieve
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::retrieve: invalid position");
//
// Time complexity: on average O(N)
//
void List::retrieve(int pos, string& value1, int& value2)
{
   //
   // TODO:
   //
    Node* cur = this->Head;
    
    if (pos >= this->Count || pos < 0) // if given position is out of bounds...
        throw invalid_argument("List::retrieve: invalid position"); // throw invalid arguement
    
    else
    {
        int x = 0; // similar to above
        while (cur != nullptr)
        {
            if (x == pos) // this time if the position is found
            {
                value1 = cur->Data.Value1; // the values are updated to the values in the list at that position
                value2 = cur->Data.Value2;
            }
            cur = cur->Next;
            x++;
        }
    }
}

//
// insert
//
// Inserts the given data in the list such that after
// the insertion, the value is now at the given
// position.
//
// Positions are 0-based, which means a position of 0 
// denotes the data will end up at the head of the list,
// and a position of N (where N = the size of the list)
// denotes the data will end up at the tail of the list.
// If the position is invalid, throws an exception, i.e.
// throw invalid_argument("List::insert: invalid position");
//
// Time complexity: on average O(N)
//
void List::insert(int pos, string value1, int value2)
{
    if (pos < 0 || pos > this->size()) // same as above
        throw invalid_argument("List::insert: invalid position");
    
    else
    {
        if (pos == 0) // if position is zero
            push_front(value1, value2); // push front function called
        
        else if (pos == this->size()) // if position is after last node
            push_back(value1, value2); // push back function called
        
        else // else, if position is between zero and after last
        {
            Node* cur = this->Head;
            Node* prev = nullptr;
            
            for (int i = 0; i < pos; i++) // loops until cur is at the position for the new node to be added
            {
                prev = cur;
                cur = cur->Next;
            }
            Node* newNode = new Node(); // new node is created
            newNode->Data.Value1 = value1; // new node is given inputted values
            newNode->Data.Value2 = value2;
            newNode->Next = cur; // new node points to cur
            prev->Next = newNode; // while prpev points to new node
            // hence new node is added into the list at the give position
            this->Count++; // count is updated
        }
    }
}

//
// remove
//
// Removes and deletes the node at the given position; no data is
// returned. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::remove: invalid position");
//
// Time complexity: on average O(N)
//
void List::remove(int pos)
{
   //
   // TODO:

    Node* cur = this->Head; // cur = this head
    Node* prev = nullptr;
    
    if (pos >= this->size() || pos < 0) // same as above
        throw invalid_argument("List::remove: invalid position");\
    
    else
    {
        if (pos == 0) // if first node or head is to be removed
        {
            this->Head = this->Head->Next; // this head points to next node (2nd node) and...
            delete cur; // this head/cur is deleted
        }
        else
        {
            int n = 0;

            while (cur != nullptr)
            {
                if (n == pos) // when position found
                {
                    break; // break so that cur is on that position
                }

                prev = cur;
                cur = cur->Next;
                n++;
            }
            prev->Next = cur->Next; // prev points to cur next, therefore nothing points to cur
            delete cur; // cur is deleted
        }
    }
    this->Count -= 1; // count reduced as node removed
    
    if (this->size() > 0) // if the size after removing is greater than 0...
    {
        Node* last = this->Head;
        while (last->Next != nullptr) // loop that traverses so that it stops when cur is last node and cur next is nullptr
        {
            last = last->Next;
        }
        this->Tail = last; // tail is updated to the last node
    }
}

//
// front
//
// Returns the data from the first node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::front: empty list");
// 
// Time complexity: O(1)
//
void List::front(string& value1, int& value2)
{
   //
   // TODO:
   //
    if (List::empty() == true) // same as above
        throw runtime_error("List::front: empty list");
    
    else
    {
        value1 = this->Head->Data.Value1; // value1 of head assigned to parameter string variable
        value2 = this->Head->Data.Value2; // value2 of head assigned to parameter int variable
    }
}

//
// back
//
// Returns the data from the last node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::back: empty list");
// 
// Time complexity: O(1)
//
void List::back(string& value1, int& value2)
{
   //
   // TODO:
   //
    // same as above but for tail
    if (List::empty() == true)
        throw runtime_error("List::back: empty list");
    else
    {
        value1 = this->Tail->Data.Value1;
        value2 = this->Tail->Data.Value2;
    }
}

//
// push_front
//
// Inserts the given data at the front of the list.
// 
// Time complexity: O(1)
//
void List::push_front(string value1, int value2)
{
   //
   // TODO:
   //
    Node* New = new Node(); // new node created
    New->Data.Value1 = value1; // new node given inputted values
    New->Data.Value2 = value2;
    New->Next = this->Head; // new node points to the head/first node
    this->Head = New; // head updated to new node
    this->Count += 1; // count/size of list increased
    if (this->size() == 1)
        this->Tail = this->Head; // if this is the first node and the last node, tail and head are assigned to the same node
}

//
// push_back
//
// Inserts the given data at the back of the list.
// 
// Time complexity: O(1)
//
void List::push_back(string value1, int value2)
{
   //
   // TODO:
   //
    Node* cur = new Node(); // new node created
    cur->Data.Value1 = value1; // new node given parameter inputted values
    cur->Data.Value2 = value2;
    if (this->size() != 0) // if size is greate than 0
    {
        this->Tail->Next = cur; // tail of list points to new node
        cur->Next = nullptr; // new node points to nullptr
        this->Tail = cur; // tail is assigned to new node as it is at the end of the list now
    } 
    else // if this is the first node in the list
    {
        this->Head = cur;
        this->Tail = cur;
        cur->Next = nullptr;
    }
    this->Count++; // count/size of list is increased by 1
}
