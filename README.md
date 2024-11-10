# SequenceableCollection Project
# Author : Monu Kumar

**Overview:**

This project implements a SequenceableCollection class in C++, designed to store integer numbers. This class combines array-like direct access with list-like variable sizing. It features contiguous storage that grows dynamically, allowing efficient insertions and deletions while keeping elements stored sequentially in memory.


**Features:**
1.	Dynamic Resizing: Starts with an initial capacity of 8 elements. When full, it doubles its capacity, copying over existing elements to maintain contiguous storage.
2.	Contiguous Storage Requirement: Ensures that all elements are stored consecutively within the allocated memory region.
3.	Efficient Insertions and Deletions: Supports inserting elements at any position and removing elements with minimal shifting.
4.	Functionality:<br/>
    **•	basicSize():** Returns the total allocated capacity.<br/>
    **•	size():** Returns the current number of elements stored in the collection.<br/>
    **•	insertAt(int i, int x):** Inserts an integer x at position i, shifting elements as needed. If the array is full, it doubles the capacity before inserting.<br/>
    **•	find(int x):** Returns the index of an integer x in the collection or -1 if not found.<br/>
    **•	removeAt(int i):** Removes the element at position i, filling the gap by shifting elements.<br/>
    **•	iterate(int (*fn)(int)):*** Applies a function fn to each element, replacing each element with the function’s return value.<br/>
5.	Constructors and Destructor:<br/>
        •	Default, copy, and parameterized constructors are implemented.<br/>
        •	Destructor frees all allocated memory, preventing memory leaks.
6.	Memory Management: The **grow()** method ensures efficient memory allocation, doubling the collection’s capacity only when necessary.

**Project Structure**
```
project/
├── include/
│   └── SequenceableCollection.h       # Header file for SequenceableCollection class
├── src/
│   └── SequenceableCollection.cpp     # Implementation file for SequenceableCollection class
├── tests/
│   └── testSequenceableCollection.cpp # Test cases for constructors, insertions, deletions, and more
└── README.md                          # Project documentation and usage instructions
```

**Compilation Instructions:**

1.	Navigate to the Project Directory:
```
        cd Monu_Kumar_mp3
```

2.	Compile the Code:
        Use the following command to compile the project, including both the implementation and test files. 
        ```
        clang++ -std=c++11 SequenceableCollection.cpp testSequenceableCollection.cpp -o testSequenceableCollection
        ```
    This will generate an executable file named testSequenceableCollection.


**Running the Project:**

After compiling, run the tests as follows:
```
    ./testSequenceableCollection
```

This will execute all the test cases and output the results to the console.


**Test Coverage**

The testSequenceableCollection.cpp file contains tests for:

	1.	Constructors and Destructor: Tests the default, copy, and parameterized constructors, as well as the destructor.
	2.	Basic Methods: Tests basicSize(), size(), insertAt(), find(), removeAt(), and iterate() to verify their functionality.
	3.	Edge Cases:
        •	Insertions and deletions at the beginning, middle, and end of the collection.
        •	Growing the collection’s capacity when the current region is full.
        •	Verifying contiguous storage after multiple operations.
        •	Confirming independence of copies made with the copy constructor.


**Using printCollection():**

The **printCollection()** method is a helper/utility function provided for debugging and testing purposes. It prints the internal state of the SequenceableCollection to the console, showing both the indices and their corresponding values within the allocated region.

**Output Format of printCollection():**

When you call printCollection(), it will display:

	•	Indices: Shows the full range of indices in the allocated region.
	•	Values: Shows the values stored in each index, with 0 or another placeholder indicating unused positions.

For example, after inserting a few elements, printCollection() might output:
```
Start index (_start): 3
End index (_end): 5
Current size (_size): 3
Total capacity (_basicSize): 8

Indices:
[0     1     2     3     4     5     6     7]
Values:
[0     0     0     5     10    15    0     0]
```

In this example:

	•	_start is at 3, where the first element (5) is stored.
	•	_end is at 5, where the last element (15) is stored.
	•	Unused positions (outside _start to _end) are displayed as 0 to indicate that they contain no meaningful data.


How to Use printCollection()

	1.	Call printCollection() after Modifications:
	•	After inserting, removing, or modifying elements, call printCollection() to verify that the collection’s internal state matches expectations.
	2.	Example Usage:
        SequenceableCollection collection;
        collection.insertAt(0, 10).insertAt(1, 20).insertAt(2, 30);
        collection.printCollection();

        // After removing the element at index 1
        collection.removeAt(1);
        collection.printCollection();

This example will first print the collection after three insertions, and then print the updated state after removing one element.


**Benefits of printCollection():**

The printCollection() function provides a quick and easy way to:

	•	Visualize the collection after each operation.
	•	Debug issues related to insertion, removal, and shifting.
	•	Verify contiguous storage by ensuring elements are stored consecutively within _start and _end.


Usage Notes

	•	Inserting Elements: Elements can be inserted at any position in the collection. The insertAt function will shift elements and resize the array if needed to ensure  contiguous storage.
	•	Removing Elements: Elements removed from the collection will cause surrounding elements to shift, maintaining contiguous storage.
	•	Copy Constructor: The copy constructor creates a deep copy, ensuring that modifications to a copied collection do not affect the original.
	•	Iterating with a Function: The iterate method takes a function pointer to apply a transformation to each element in the collection.


Requirements

	•	C++11 or later
	•	g++ or clang++ compiler