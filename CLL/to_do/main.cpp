#include "CLL.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "===== Testing insert =====\n";

    CLL list;

    list.insert("Alice");
    list.insert("Bob");
    list.insert("Charlie");

    cout << "Expected count: 3\n";
    cout << "Actual count:   " << list.count() << "\n";

    cout << "\nExpected list:\n";
    cout << "Alice\nBob\nCharlie\n";

    cout << "Actual list:\n";
    list.display_all();


    cout << "\n===== Testing remove_by_name =====\n";

    int removed = list.remove_by_name("Bob");

    cout << "Expected removed: 1\n";
    cout << "Actual removed:   " << removed << "\n";

    cout << "Expected count: 2\n";
    cout << "Actual count:   " << list.count() << "\n";

    cout << "\nExpected list:\n";
    cout << "Alice\nCharlie\n";

    cout << "Actual list:\n";
    list.display_all();


    cout << "\n===== Testing remove_by_name with duplicates =====\n";

    list.insert("Alice");
    list.insert("Alice");

    cout << "Expected count: 4\n";
    cout << "Actual count:   " << list.count() << "\n";

    removed = list.remove_by_name("Alice");

    cout << "Expected removed: 3\n";
    cout << "Actual removed:   " << removed << "\n";

    cout << "Expected count: 1\n";
    cout << "Actual count:   " << list.count() << "\n";

    cout << "\nExpected list:\n";
    cout << "Charlie\n";

    cout << "Actual list:\n";
    list.display_all();


    cout << "\n===== Testing copy constructor =====\n";

    CLL original;

    original.insert("One");
    original.insert("Two");
    original.insert("Three");

    CLL copied(original);

    cout << "Original count: " << original.count() << "\n";
    cout << "Copied count:   " << copied.count() << "\n";

    cout << "\nOriginal:\n";
    original.display_all();

    cout << "\nCopied:\n";
    copied.display_all();


    cout << "\n===== Testing copy independence =====\n";

    cout << "Adding to original...\n";
    original.insert("Four");

    cout << "\nExpected original count: 4\n";
    cout << "Actual original count:   " << original.count() << "\n";

    cout << "Expected copied count: 3\n";
    cout << "Actual copied count:   " << copied.count() << "\n";

    cout << "\nOriginal:\n";
    original.display_all();

    cout << "\nCopied:\n";
    copied.display_all();


    cout << "\n===== Tests complete =====\n";

    return 0;
}
