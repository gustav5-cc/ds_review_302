// cll.cpp
// Circular Linked List (CLL) of strings.
//
// Key idea for recursion on a circular list: there is no nullptr to stop at.
// The base case is "current == rear" (we have reached the last node).
// Anything that can be done in O(1) with the rear pointer (insert) is NOT recursive.

#include "cll.h"
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
//   - Source is empty:       copy is empty
//   - Source has 1 node:     copy has 1 node pointing to itself
//   - Source has many nodes: deep copy in order, then close the circle
CLL::CLL(const CLL & source) : rear(nullptr)
{
    copy(source);
}

// copy function
void CLL::copy(const CLL & source)
{
    if (!source.rear)
    {
        rear = nullptr;
        return;
    }

    CLL_node * first = nullptr;
    copy(first, source.rear->get_next(), source.rear);   // sets our rear when it reaches the end
    rear->set_next(first);                               // close the circle
}

// RECURSIVE: copies source..source_rear as a linear chain, and sets rear
// to the last node created.
//   - Base case (source == source_rear): copy the last node, set rear
//   - Otherwise: copy one node, then recurse on the rest
void CLL::copy(CLL_node *& dest, CLL_node * source, CLL_node * source_rear)
{
    dest = new CLL_node(*source);

    if (source == source_rear)
    {
        rear = dest;
        return;
    }
    copy(dest->get_next(), source->get_next(), source_rear);
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

// insert (at the end of the list) -- O(1), NOT recursive
// Scenarios:
//   - Empty list:    new node becomes rear and points to itself
//   - One node:      new node goes after rear, points back to the old node
//   - Many nodes:    same as one node: new node goes after rear,
//                    points to the first node (rear->next)
void CLL::insert(const string & new_data)
{
    CLL_node * temp = new CLL_node(new_data);

    if (!rear)
    {
        temp->set_next(temp);                    // a single node points to itself
    }
    else
    {
        temp->set_next(rear->get_next());        // new node points to the first node
        rear->set_next(temp);                    // old last points to new node
    }
    rear = temp;                                 // new node is now the last
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
//   - Empty list:                       return 0
//   - One node, match:                  delete it, rear = nullptr
//   - One node, no match:               return 0, list unchanged
//   - Many nodes, match at the front:   rear->next skips the old first node
//   - Many nodes, match in the middle:  relink prev around the node
//   - Many nodes, match at the rear:    prev becomes the new rear
//   - Consecutive/multiple matches:     keep checking after each removal;
//                                       list may shrink to one node, or to empty
//   - No match:                         return 0, list unchanged
int CLL::remove_by_name(const string & name)
{
    if (!rear)
        return 0;
    return remove_by_name(rear, rear->get_next(), name);   // prev = rear, current = first
}

// Invariant: prev->next == current, and the list is not empty.
int CLL::remove_by_name(CLL_node * prev, CLL_node * current, const string & name)
{
    bool at_end = (current == rear);             // decide BEFORE we might delete current

    if (current->matches(name))
    {
        if (current == prev)                     // the only node left in the list
        {
            delete current;
            rear = nullptr;
            return 1;
        }

        prev->set_next(current->get_next());     // bypass current
        if (current == rear)
            rear = prev;                         // removed the last node: prev is the new last
        delete current;

        if (at_end)
            return 1;
        return 1 + remove_by_name(prev, prev->get_next(), name);   // prev stays; new current
    }

    if (at_end)
        return 0;
    return remove_by_name(current, current->get_next(), name);
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
