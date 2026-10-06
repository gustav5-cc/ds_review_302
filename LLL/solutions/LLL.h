// lll.h
// Linear Linked List (LLL) of strings -- all list operations are recursive.

#ifndef LLL_H
#define LLL_H

#include <string>
using std::string;

// ---------------------------------------------------------------
// Node class
// ---------------------------------------------------------------
class LLL_node
{
public:
    LLL_node();                                  // default constructor
    LLL_node(const string & new_data);           // constructor with data
    LLL_node(const LLL_node & to_copy);          // copy constructor (copies data only, next = nullptr)

    bool matches(const string & name) const;     // true if data == name
    void display() const;                        // print this node's data
    LLL_node *& get_next();                      // returns a REFERENCE to the next pointer
    void set_next(LLL_node * new_next);

private:
    string data;
    LLL_node * next;
};

// ---------------------------------------------------------------
// List class
// ---------------------------------------------------------------
class LLL
{
public:
    LLL();                                       // default constructor
    LLL(const LLL & source);                     // copy constructor
    ~LLL();                                      // destructor
    LLL & operator=(const LLL & source);         // assignment operator

    void insert(const string & new_data);        // insert at the end of the list
    int  display_all() const;                    // returns # of nodes displayed
    int  display_by_name(const string & name) const;  // returns # of matches displayed
    int  remove_by_name(const string & name);    // removes every match; returns # removed
    int  remove_all();                           // returns # of nodes removed
    int  count() const;                          // number of nodes
    bool is_empty() const;

private:
    LLL_node * head;

    void insert(LLL_node *& current, const string & new_data);
    int  display_all(LLL_node * current) const;
    int  display_by_name(LLL_node * current, const string & name) const;
    int  remove_by_name(LLL_node *& current, const string & name);
    int  remove_all(LLL_node *& current);
    int  count(LLL_node * current) const;
    void copy(const LLL & source);                           // wrapper
    void copy(LLL_node *& dest, LLL_node * source);          // recursive
};

#endif
