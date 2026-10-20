#ifndef DLL_H
#define DLL_H

// The Node class is completely encapsulated and not a friend to the DLL class.
class Node {
    public:
        Node(int val);
        
        int get_data() const;
        void set_data(int val);
        
        Node* get_next() const;
        void set_next(Node* next_ptr);
        
        Node* get_prev() const;
        void set_prev(Node* prev_ptr);


    private:
        int data;
        Node* prev;
        Node* next;
};

// Doubly Linked List (Linear Linked List)
class DLL {
    public:
        DLL();
        ~DLL();
        DLL(const DLL& source); // Copy constructor
        DLL& operator=(const DLL& source); // Assignment operator

        void insert(int val);
        void remove_all();
        int remove(int val); // Returns the number of occurrences removed
        void display_all() const;
        void build();

    private:
        Node* head;

        // Recursive helper methods utilizing pointer pass-by-reference 
        // to cleanly handle edge cases (like modifying the head or caller's next pointer)
        void insert(Node*& curr, Node* previous, int val);
        void remove_all(Node*& curr);
        int remove(Node*& curr, int val);
        void display_all(Node* curr) const;
        void copy(Node*& dest, Node* source, Node* previous);
};

#endif // DLL_H~
