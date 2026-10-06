// CLL.cpp
// Circular Linked List (CLL) of strings.
//
// Key idea for recursion on a circular list: there is no nullptr to stop at.
// The base case is "current == rear" (we have reached the last node).
// Anything that can be done in O(1) with the rear pointer (insert) is NOT recursive.

#include "CLL.h"
#include <iostream>
using std::cout;
using std::endl;

// ===============================================================
// CLL_node
// ===============================================================
CLL_node::CLL_node() : next(nullptr)
{
}

CLL_node::CLL_node(const string & new_data) : data(new_data), next(nullptr)
{
}

CLL_node::CLL_node(const CLL_node & to_copy) : data(to_copy.data), next(nullptr)
{
}

bool CLL_node::matches(const string & name) const
{
    return data == name;
}

void CLL_node::display() const
{
    cout << data << endl;
}

CLL_node *& CLL_node::get_next()
{
    return next;
}

void CLL_node::set_next(CLL_node * new_next)
{
    next = new_next;
}


// ===============================================================
// CLL
// ===============================================================

// CLL -- default constructor
// Scenarios: new list starts empty (rear = nullptr)
CLL::CLL() : rear(nullptr)
{
}

// CLL -- copy constructor
// Scenarios:
//   - 
//   - 
//   - 
CLL::CLL(const CLL & source) : rear(nullptr)
{
    copy(source);
}

// copy function
void CLL::copy(const CLL & source)
{
    return;
}

void CLL::copy(CLL_node *& dest, CLL_node * source, CLL_node * source_rear)
{
    return;
}

// CLL -- assignment operator
// Scenarios:
//   - Self-assignment (list = list):  do nothing
//   - Source is empty:                destination becomes empty
//   - Source has 1+ nodes:            destination's old nodes freed,
//                                     then deep copy of source
CLL & CLL::operator=(const CLL & source)
{
    if (this == &source)
        return *this;

    remove_all();                   // free what we currently own
    copy(source);                   // then deep copy
    return *this;
}

// CLL -- destructor
// Scenarios: empty list (nothing to do) or 1+ nodes (all freed)
CLL::~CLL()
{
    remove_all();
}

// Scenarios:
//   - 
//   - 
//   - 
void CLL::insert(const string & new_data)
{
    return;
}

// display_all
// Scenarios:
//   - Empty list:        print a message, return 0
//   - One node:          print it, stop (it is also rear)
//   - Many nodes:        print first..rear, stop at rear
int CLL::display_all() const
{
    if (!rear)
    {
        cout << "The list is empty." << endl;
        return 0;
    }
    return display_all(rear->get_next());        // start at the first node
}

int CLL::display_all(CLL_node * current) const
{
    current->display();
    if (current == rear)
        return 1;
    return 1 + display_all(current->get_next());
}

// display_by_name
// Scenarios:
//   - Empty list:            return 0
//   - One node:              match or no match
//   - Many nodes:            zero, one, or several matches; stop at rear
int CLL::display_by_name(const string & name) const
{
    if (!rear)
        return 0;
    return display_by_name(rear->get_next(), name);
}

int CLL::display_by_name(CLL_node * current, const string & name) const
{
    int found = 0;
    if (current->matches(name))
    {
        current->display();
        found = 1;
    }
    if (current == rear)
        return found;
    return found + display_by_name(current->get_next(), name);
}

// remove_by_name (removes every node whose data matches)
// Scenarios:
//   - 
//   - 
//   - 
//   - 
//   - 
//   - 
//   - No match:                         return 0, list unchanged
int CLL::remove_by_name(const string & name)
{
    return -1;
}

int CLL::remove_by_name(CLL_node * prev, CLL_node * current, const string & name)
{
    return -1;
}

// remove_all
// Scenarios:
//   - Empty list:         return 0
//   - One or many nodes:  break the circle, delete every node, rear = nullptr
int CLL::remove_all()
{
    if (!rear)
        return 0;

    CLL_node * first = rear->get_next();
    rear->set_next(nullptr);                     // break the circle so recursion can stop at nullptr
    rear = nullptr;
    return remove_all(first);
}

int CLL::remove_all(CLL_node *& current)
{
    if (!current)
        return 0;

    CLL_node * temp = current->get_next();
    delete current;
    current = temp;
    return 1 + remove_all(current);
}

// count
// Scenarios:
//   - Empty list:   return 0
//   - One node:     return 1 (it is also rear)
//   - Many nodes:   count first..rear
int CLL::count() const
{
    if (!rear)
        return 0;
    return count(rear->get_next());
}

int CLL::count(CLL_node * current) const
{
    if (current == rear)
        return 1;
    return 1 + count(current->get_next());
}

// is_empty (O(1), no recursion needed)
bool CLL::is_empty() const
{
    return rear == nullptr;
}
