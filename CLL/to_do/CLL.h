// CLL.h
// Circular Linked List (CLL) of strings -- all list operations are recursive.
// The list keeps a single REAR pointer; rear->next is the first node.

#ifndef CLL_H
#define CLL_H

#include <string>
using std::string;

// ---------------------------------------------------------------
// Node class
// ---------------------------------------------------------------
class CLL_node
{
public:
    CLL_node();                                  // default constructor
    CLL_node(const string & new_data);           // constructor with data
    CLL_node(const CLL_node & to_copy);          // copy constructor (copies data only, next = nullptr)

    bool matches(const string & name) const;     // true if data == name
    void display() const;                        // print this node's data
    CLL_node *& get_next();                      // returns a REFERENCE to the next pointer
    void set_next(CLL_node * new_next);

private:
    string data;
    CLL_node * next;
};

// ---------------------------------------------------------------
// List class
// ---------------------------------------------------------------
class CLL
{
public:
    CLL();                                       // default constructor
    CLL(const CLL & source);                     // copy constructor
    ~CLL();                                      // destructor
    CLL & operator=(const CLL & source);         // assignment operator

    void insert(const string & new_data);        // insert at the end of the list (O(1), not recursive)
    int  display_all() const;                    // returns # of nodes displayed
    int  display_by_name(const string & name) const;  // returns # of matches displayed
    int  remove_by_name(const string & name);    // removes every match; returns # removed
    int  remove_all();                           // returns # of nodes removed
    int  count() const;                          // number of nodes
    bool is_empty() const;

private:
    CLL_node * rear;                             // last node; rear->next is the first node

    // Recursive helpers (the public functions above are the "wrappers")
    int  display_all(CLL_node * current) const;
    int  display_by_name(CLL_node * current, const string & name) const;
    int  remove_by_name(CLL_node * prev, CLL_node * current, const string & name);
    int  remove_all(CLL_node *& current);        // works on a temporarily-linear chain
    int  count(CLL_node * current) const;
    void copy(const CLL & source);                                            // wrapper
    void copy(CLL_node *& dest, CLL_node * source, CLL_node * source_rear);   // recursive
};

#endif
