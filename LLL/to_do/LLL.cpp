// LLL.cpp

#include "LLL.h"
#include <iostream>
using std::cout;
using std::endl;

// ===============================================================
// LLL_node
// ===============================================================
LLL_node::LLL_node() : next(nullptr)
{
}

LLL_node::LLL_node(const string & new_data) : data(new_data), next(nullptr)
{
}

LLL_node::LLL_node(const LLL_node & to_copy) : data(to_copy.data), next(nullptr)
{
}

bool LLL_node::matches(const string & name) const
{
    return data == name;
}

void LLL_node::display() const
{
    cout << data << endl;
}

LLL_node *& LLL_node::get_next()
{
    return next;
}

void LLL_node::set_next(LLL_node * new_next)
{
    next = new_next;
}


// ===============================================================
// LLL_node
// ===============================================================

// LLL -- default constructor
LLL::LLL() : head(nullptr)
{
}

// ===============================================================
// LLL -- copy constructor
//   - 
//   - 
// ===============================================================
LLL::LLL(const LLL & source) : head(nullptr)
{
    copy(source);
}

void LLL::copy(const LLL & source)
{
    return;
}

//   - Base case? : 
//   - Else:      :
void LLL::copy(LLL_node *& dest, LLL_node * source)
{
    return;
}

// LLL -- assignment operator
// Scenarios:
//   - Self-assignment (list = list):  do nothing
//   - Source is empty:                destination becomes empty
//   - Source has 1+ nodes:            destination's old nodes freed,
//                                     then deep copy of source
LLL & LLL::operator=(const LLL & source)
{
    if (this == &source)
        return *this;

    remove_all();                   // free what we currently own
    copy(source);                   // then deep copy
    return *this;
}

// LLL -- destructor
// Scenarios: empty list (nothing to do) or 1+ nodes (all freed)
LLL::~LLL()
{
    remove_all();
}

// insert (at the end of the list)
// Scenarios:
//   - 
//   - 
//   - 
// Base Case?
void LLL::insert(const string & new_data)
{
    return;
}

void LLL::insert(LLL_node *& current, const string & new_data)
{
    return;
}

// display_all
// Scenarios:
//   - Empty list:        print a message, return 0
//   - One or many nodes: print each node, return how many
int LLL::display_all() const
{
    if (!head)
    {
        cout << "The list is empty." << endl;
        return 0;
    }
    return display_all(head);
}

int LLL::display_all(LLL_node * current) const
{
    if (!current)
        return 0;
    current->display();
    return 1 + display_all(current->get_next());
}

// display_by_name
// Scenarios:
//   - Empty list:            nothing to display, return 0
//   - No matches:            return 0
//   - One or more matches:   display each match, return how many
int LLL::display_by_name(const string & name) const
{
    return display_by_name(head, name);
}

int LLL::display_by_name(LLL_node * current, const string & name) const
{
    if (!current)
        return 0;

    int found = 0;
    if (current->matches(name))
    {
        current->display();
        found = 1;
    }
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
//   - 
// hint: the reference parameter lets one code path cover multiple scenarios
int LLL::remove_by_name(const string & name)
{
    return -1;
}

int LLL::remove_by_name(LLL_node *& current, const string & name)
{
    return -1;
}

// remove_all
// Scenarios:
//   - Empty list:         return 0
//   - One or many nodes:  delete every node, head ends as nullptr
int LLL::remove_all()
{
    return remove_all(head);
}

int LLL::remove_all(LLL_node *& current)
{
    if (!current)
        return 0;

    LLL_node * temp = current->get_next();
    delete current;
    current = temp;
    return 1 + remove_all(current);
}

// count
// Scenarios: empty list returns 0; otherwise number of nodes
int LLL::count() const
{
    return count(head);
}

int LLL::count(LLL_node * current) const
{
    if (!current)
        return 0;
    return 1 + count(current->get_next());
}

// is_empty (O(1), no recursion needed)
bool LLL::is_empty() const
{
    return head == nullptr;
}
