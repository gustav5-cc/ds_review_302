#include "DLL.h"
#include <iostream>

void print_test_header(const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

void descrip(const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

void print_sep() {
    std::cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}

void print_before() {
    std::cout << "\nList before changes \n";
}

void print_after() {
    std::cout << "\nList after changes\n";
}

void print_backwards() {
    std::cout << "\nIs list still valid backwards\n";
}

int main() {
    DLL list1;

    print_test_header("Test 1: Build & Display");
    // Prefills list with 12 items, heavily biased with '2's
    list1.build(); 
    std::cout << "List 1 initially: ";
    list1.display_all();

    print_test_header("Test 2: Copy Constructor (Deep Copy Check)");
    DLL list2(list1);
    std::cout << "List 2 (Copy of List 1): ";
    list2.display_all();

    print_test_header("Test 3: Remove Head Edge Case");
    std::cout << "Removing 10 from List 1 (head node)." << std::endl;
    list1.remove(10);
    std::cout << "List 1 after remove(10): ";
    list1.display_all();
    std::cout << "List 2 (should be unaffected): ";
    list2.display_all();

    print_test_header("Test 4: Remove Multiple Occurrences & Tail");
    std::cout << "Removing all '2's from List 1." << std::endl;
    int removed_count = list1.remove(2);
    std::cout << "Removed " << removed_count << " instances of '2'." << std::endl;
    std::cout << "List 1 after remove(2): ";
    list1.display_all();

    print_test_header("Test 5: Assignment Operator & Memory Leak Check");
    DLL list3;
    list3.insert(999); 
    std::cout << "List 3 before assignment: ";
    list3.display_all();
    
    list3 = list1; // Should cleanly delete 999 and copy list1
    std::cout << "List 3 after list3 = list1: ";
    list3.display_all();

    print_test_header("Test 6: Remove Non-Existent Element");
    std::cout << "Removing 100 from List 1 (doesn't exist)." << std::endl;
    removed_count = list1.remove(100);
    std::cout << "Removed " << removed_count << " instances." << std::endl;

    print_test_header("Test 7: Remove All (Clearing the List)");
    list1.remove_all();
    std::cout << "List 1 after remove_all: ";
    list1.display_all();

    print_test_header("Test 8: Insert into Empty List");
    list1.insert(50);
    list1.insert(60);
    std::cout << "List 1 after inserting 50, 60: ";
    list1.display_all();


    // Our testing
    print_sep();
    descrip("Testing Duplicate All 2's");
    DLL list5;
    list5.build();
    print_before();
    list5.display_all();
    int twos = list5.dupe_every_two();
    std::cout << "Twos duped: " << twos << std::endl;

    print_after();
    list5.display_all();
    print_backwards();
    list5.display_all_rev();

    print_sep();
    descrip("Testing remove nodes less than average");
    DLL list6;
    list6.build();
    print_before();
    list6.display_all();
    int rem = list6.remove_nodes_avg();
    std::cout << "Nodes removed: " << rem << std::endl;

    print_after();
    list6.display_all();
    print_backwards();
    list6.display_all_rev();

    print_sep();
    descrip("Reversing a doubly linked list");
    DLL list7;
    list7.build();
    print_before();
    list7.display_all();
    list7.reverse();

    print_after();
    list7.display_all();
    list7.display_all_rev();
    
    return 0;
}
