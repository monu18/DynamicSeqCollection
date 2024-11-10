#include "SequenceableCollection.h"
#include <iostream>

void testInsertFunction() {
    SequenceableCollection collection;

    std::cout << "\nTesting Insertion:\n" << std::endl;

    // Insert at the beginning
    collection.insertAt(0, 5);
    std::cout << "After inserting 5 at index 0:" << std::endl;
    collection.printCollection();

    // Insert at index 1 (should go right after the first element)
    collection.insertAt(1, 10);
    std::cout << "After inserting 10 at index 1:" << std::endl;
    collection.printCollection();

    // Insert at the beginning again
    collection.insertAt(0, 15);
    std::cout << "After inserting 15 at index 0:" << std::endl;
    collection.printCollection();

    // Insert in the middle
    collection.insertAt(1, 20);
    std::cout << "After inserting 20 at index 1:" << std::endl;
    collection.printCollection();

    // Insert at the end
    collection.insertAt(4, 25);
    std::cout << "After inserting 25 at index 4:" << std::endl;
    collection.printCollection();

    // Insert at a new position to test grow functionality
    for (int i = 5; i < 12; ++i) {
        collection.insertAt(i, i * 10);
        std::cout << "After inserting "<< i*10<< " at index "<< i <<" :" << std::endl;
        collection.printCollection();
    }
    std::cout << "After inserting elements to trigger growth:" << std::endl;
    collection.printCollection();
}

void testFindFunction() {
    SequenceableCollection collection;
    collection.insertAt(0, 10);
    collection.insertAt(1, 20);
    collection.insertAt(2, 30);
    collection.insertAt(3, 30);


    std::cout << "\nTesting Find:\n" << std::endl;

    // Find existing elements
    int index = collection.find(20);
    std::cout << "Finding 20, expected index: 1, got: " << index << std::endl;

    index = collection.find(30);
    std::cout << "Finding 30, expected index: 2, got: " << index << std::endl;

    // Attempt to find a non-existent element
    index = collection.find(40);
    std::cout << "Finding 40, expected index: -1, got: " << index << std::endl;
}

void testRemoveFunction() {
    SequenceableCollection collection;
    collection.insertAt(0, 5);
    collection.insertAt(1, 10);
    collection.insertAt(2, 15);
    collection.insertAt(3, 20);

    std::cout << "\nTesting Removal:\n" << std::endl;

    std::cout << "Before removing any element:" << std::endl;
    collection.printCollection();

    // Remove an element from the beginning
    collection.removeAt(0);
    std::cout << "After removing element at index 1:" << std::endl;
    collection.printCollection();

    // Remove an element from the middle
    collection.removeAt(1);
    std::cout << "After removing element at index 1:" << std::endl;
    collection.printCollection();

    // Remove an element from the end
    collection.removeAt(1);
    std::cout << "After removing element at index 1 (end):" << std::endl;
    collection.printCollection();

    // Attempt to remove an element out of bounds
    collection.removeAt(10);
    std::cout << "After attempting to remove element at out-of-bounds index 10:" << std::endl;
    collection.printCollection();
}

void testIterateFunction() {
    SequenceableCollection collection;
    collection.insertAt(0, 5);
    collection.insertAt(1, 10);
    collection.insertAt(2, 15);

    std::cout << "\nTesting Iterate:\n" << std::endl;
    std::cout << "Original collection:" << std::endl;
    collection.printCollection();

    // Define a lambda to increment each element by 1
    auto incrementFunction = [](int x) { return x + 1; };

    // Apply `iterate` with the increment function
    collection.iterate(incrementFunction);

    std::cout << "Collection after applying iterate with increment function:" << std::endl;
    collection.printCollection();
}

void testEdgeCases() {
    SequenceableCollection collection;

    std::cout << "\nTesting Edge Cases:\n" << std::endl;

    // Attempt insertion out of bounds
    collection.insertAt(-1, 50);
    collection.insertAt(10, 50);

    // Attempt to remove from an empty collection
    collection.removeAt(0);

    // Print after invalid operations
    std::cout << "Collection after out-of-bounds operations:" << std::endl;
    collection.printCollection();

    // Test iterate on an empty collection
    auto incrementFunction = [](int x) { return x + 1; };
    collection.iterate(incrementFunction);

    std::cout << "Collection after applying iterate on an empty collection:" << std::endl;
    collection.printCollection();
}

int main() {
    // Call each test case
    // testInsertFunction();
    // testFindFunction();
    // testRemoveFunction();
    // testIterateFunction();
    testEdgeCases();

    std::cout << "All tests completed." << std::endl;
    return 0;
}