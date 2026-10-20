#include "DLL.h"
#include <iostream>

// ==========================================
// Node Class Implementation
// ==========================================

Node::Node(int val) : data(val), prev(nullptr), next(nullptr) 
{}

int Node::get_data() const 
{ 
    return data; 
}

void Node::set_data(int val) 
{ 
    data = val; 
}

Node*& Node::get_next()
{ 
    return next; 
}

void Node::set_next(Node* next_ptr) 
{ 
    next = next_ptr; 
}

Node*& Node::get_prev()
{ 
    return prev; 
}

void Node::set_prev(Node* prev_ptr) 
{ 
    prev = prev_ptr; 
}

// ==========================================
// DLL Class Implementation
// ==========================================

DLL::DLL() : head(nullptr), rear(nullptr)
{}

DLL::~DLL() 
{
    remove_all();
}

DLL::DLL(const DLL& source) : head(nullptr), rear(nullptr)
{
    copy(head, source.head, nullptr);
}

DLL& DLL::operator=(const DLL& source) 
{
    if (this == &source) 
        return *this;

    remove_all();
    copy(head, source.head, nullptr);
    return *this;
}

// ------------------------------------------
// Public Wrappers
// ------------------------------------------

void DLL::insert(int val) 
{
    insert(head, nullptr, val);
}

void DLL::remove_all() 
{
    remove_all(head);
    head = nullptr;
    rear = nullptr;
}

int DLL::remove(int val) 
{
    return remove(head, val);
}

void DLL::display_all() const 
{
    if (!head) 
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    display_all(head);
    std::cout << std::endl;
}


void DLL::display_all_rev() const 
{
    if(!head)
    {
        std::cout << "List is empty." << std::endl;
        return;
    }

    display_all_rev(rear);
    std::cout << std::endl;
}

void DLL::build() 
{
    // Prefill with 12 items, heavily biased towards adding the number 2
    int initial_data[] = {10, 2, 45, 2, 7, 2, 99, 14, 2, 8, 3, 2};
    for (int i = 0; i < 12; ++i) {
        insert(initial_data[i]);
    }
}

// ------------------------------------------
// Recursive Private Helper Functions
// ------------------------------------------

// Appends sequentially. Pass-by-reference handles the caller's connection.
void DLL::insert(Node*& curr, Node* previous, int val) 
{
    if (!curr) 
    {
        curr = new Node(val);
        curr->set_prev(previous);
        this->rear = curr;
        return;
    }
    
    Node* next_node = curr->get_next();
    insert(next_node, curr, val);
    curr->set_next(next_node); // Reconnects the modified sequence
}

// Recursively destroys the list. Pass-by-reference automatically nullifies the head pointer.
void DLL::remove_all(Node*& curr) 
{
    if (!curr)
        return;
    
    Node* next_node = curr->get_next();
    remove_all(next_node);
    
    delete curr;
    curr = nullptr; 
}

// Removes by value and correctly stitches 'prev' and 'next' doubly linked pointers
int DLL::remove(Node*& curr, int val) 
{
    if (!curr)
        return 0;

    if (curr->get_data() == val) {
        Node* temp = curr;
        
        // Advance current to next (updates the caller's pointer via reference)
        curr = curr->get_next(); 
        
        // If there's a node after the deleted one, stitch its 'prev' backward
        if (curr) {
            curr->set_prev(temp->get_prev());
        }

        if (curr == rear) {
            rear = curr->get_prev();
        }
        
        delete temp;
        
        // Continue checking the remaining list (curr is now the new node at this position)
        return 1 + remove(curr, val); 
    }

    // Traverse if no match
    Node* next_node = curr->get_next();
    int count = remove(next_node, val);
    curr->set_next(next_node); // Ensures caller's next pointer respects deletions
    return count;
}

// Read-only recursion to display elements
void DLL::display_all(Node* curr) const 
{
    if (!curr)
        return;
    
    std::cout << curr->get_data() <<  " " ;
    display_all(curr->get_next());
}

void DLL::display_all_rev(Node* curr) const 
{    
    if (!curr)
        return;
    
    std::cout << curr->get_data() <<  " " ;
    display_all_rev(curr->get_prev());
}

// Recursively deep copies the list while maintaining doubly linked structures
void DLL::copy(Node*& dest, Node* source, Node* previous) 
{
    if (!source) 
    {
        dest = nullptr;
        rear = previous;
        return;
    }
    
    dest = new Node(source->get_data());
    dest->set_prev(previous);
    
    Node* next_node = nullptr;
    copy(next_node, source->get_next(), dest);
    dest->set_next(next_node);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Exercises
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int DLL::dupe_every_two() 
{
    if (!head)
        return 0;

    return dupe_every_two(head);
}

int DLL::dupe_every_two(Node *& curr) 
{
    if (!curr)
        return 0;

    if (curr->get_data() == 2) {
        Node * temp = new Node(2);

        // Slot temp into place, in front of curr
        temp->set_prev(curr);
        temp->set_next(curr->get_next());
        
        // Adjust curr to point to temp
        curr->set_next(temp);

        // Adjust node after temp (if exists) to point back to temp
        if (temp->get_next()) 
        {
            temp->get_next()->set_prev(temp);
        }

        if (curr == rear) 
        {
            this->rear = temp;
        }

        // we pass in temp because we duped it in front of us,
        // dont want to redupe forever
        return 1 + dupe_every_two(temp->get_next());
    }

    return dupe_every_two(curr->get_next());
}
