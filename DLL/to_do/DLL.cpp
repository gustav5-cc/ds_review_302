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
    int initial_data[] = {10, 2, 19, 2, 7, 2, 23, 14, 2, 8, 3, 2};
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
    // Base case: end of list
    if (!curr)
        return 0;

    if (curr->get_data() == 2) {
        Node * temp = new Node(2);

        // TODO 1: Slot 'temp' into place directly AFTER 'curr'.
        // Hint: Set the prev and next pointers for 'temp' first.
        

        // TODO 2: Adjust the surrounding nodes to point to 'temp'.
        // Hint: Update curr's next pointer, and don't forget to check 
        // if a node exists after temp before updating its prev pointer.
        

        // TODO 3: Tail pointer management.
        // Hint: What must happen to 'this->rear' if 'curr' was the last node?
        

        // TODO 4: Advance the recursion.
        // Hint: Add 1 to the total. How do you advance the pointer so you 
        // don't infinitely duplicate the node you just created?
        return 0;/* recursive call here */;
    }

    // TODO 5: Standard progression.
    // Hint: If the current data is NOT 2, just move to the next node.
    return 0;/* recursive call here */;
}

int DLL::remove_nodes_avg()
{
    int sum = 0;
    int avg = 0;
    int count = 0;

    if (!head)
        return 0;

    return remove_nodes_avg(head, count, sum, avg);
}

int DLL::remove_nodes_avg(Node * curr, int & count, int & sum, int & avg)
{
    // Base case: hit the end of the list
    if (!curr) 
    {
        // TODO 1: Compute the average.
        // Hint: This base case is reached only AFTER visiting every node.
        
        std::cout << "\n Avg:" << avg << std::endl;
        return 0;
    }

    // TODO 2: Traverse to the end of the list BEFORE processing deletions.
    // Hint: You cannot know if you should delete the current node until you
    // know the average of the whole list. Accumulate 'count' and 'sum' as you 
    // pass them into the recursive call.
    int total_removed = 0;/* recursive call here */;

    // --- Unwinding Phase: Evaluating nodes on the way back UP the call stack ---

    // TODO 3: Check the deletion condition.
    // Hint: Compare the current node's data to the calculated average.
    if ( 0/* condition */ ) 
    {
        Node * temp_n = curr->get_next();
        Node * temp_p = curr->get_prev();

        // TODO 4: Handle the node AFTER curr (temp_n).
        // Hint: If temp_n is null, curr was the last node—what pointer must be updated?
        // Otherwise, update temp_n's previous pointer.
        

        // TODO 5: Handle the node BEFORE curr (temp_p).
        // Hint: If temp_p is null, curr was the first node—what pointer must be updated?
        // Otherwise, update temp_p's next pointer.
        

        // TODO 6: Deallocate the memory for curr and increment your counter.
        // Hint: Don't forget to set curr to nullptr after deleting it to avoid dangling pointers.
        
    }

    // TODO 7: Pass the running total back up the stack.
    return 0;/* variable holding the removed count */;
}

void DLL::reverse() 
{
}
        
void DLL::reverse(Node * curr) 
{
}
