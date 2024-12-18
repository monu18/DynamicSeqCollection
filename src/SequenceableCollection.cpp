#include "../include/SequenceableCollection.h"
#include <iostream>
using namespace std;

/*
Default Constructor
*/
SequenceableCollection::SequenceableCollection() : _start(3), _end(2), _size(0), _basicSize(8) {

	region = new int[_basicSize];     // Allocating initial capacity
}

/*
Copy Constructor
*/
SequenceableCollection::SequenceableCollection(const SequenceableCollection& sequenceableCollection)
    : _start(sequenceableCollection._start), _end(sequenceableCollection._end), _size(sequenceableCollection._size), _basicSize(sequenceableCollection._basicSize) {
    region = new int[_basicSize];

    for (int z = 0; z < _basicSize; z++) {
		region[z] = sequenceableCollection.region[z];
	}
}

/*
Constructor taking an initial element
*/
SequenceableCollection::SequenceableCollection(int initialElement) : SequenceableCollection() {
    insertAt(0, initialElement);
}

// Destructor
SequenceableCollection::~SequenceableCollection() {
    delete[] region;  // Release memory to avoid leaks
}

// Returns the capacity of the allocated storage region
int SequenceableCollection::basicSize() const {
    return _basicSize;
}

// Returns the number of elements currently in the collection
int SequenceableCollection::size() const {
    return _size;
}

// Insert x at specified index, shifting elements as needed
SequenceableCollection& SequenceableCollection::insertAt(int i, int x) {
    if (i < 0 || i > _end - _start + 1) {
        cout << "......Index is out of bounds....." << endl;
        return *this;
    }

    // Grow the array if it's full
    if (_size >= _basicSize) {
        grow();
    }

    // Special case for the first insertion
    if (_size == 0) {
        // First element insertion
        _start = 3;  // Starting position as defined in project
        _end = _start;
        region[_start] = x;
    } else if (i == 0) {
        // Insert at the beginning
        if (_start > 0) {
            // Insert at the beginning without shifting if there's space
            _start--;
            region[_start] = x;
        } else if (_end < _basicSize - 1) {
            // Shift elements right to make space at the beginning
            for (int j = _end; j >= _start; --j) {
                region[j + 1] = region[j];
            }
            _end++;
            region[_start] = x;
        }
    } else if (i == _end - _start + 1) {
        // Insert at the end without shifting if there's space
        if (_end < _basicSize - 1) {
            _end++;
            region[_end] = x;
        } else if (_start > 0) {
            // Shift everything left to make space if there's room at the start
            int shiftAmount = _start;
            for (int j = _start; j <= _end; ++j) {
                region[j - shiftAmount] = region[j];
            }
            _end -= shiftAmount;
            _start = 0;
            _end++;
            region[_end] = x;
        }
    } else {
        // Shift elements if inserting in the middle
        if (i <= (_end - _start) / 2) {
            // Prefer shifting to the left if closer to the start
            if (_start > 0) {
                leftShift(i);
            } else if (_end < _basicSize - 1) {
                // If no space to shift left, fall back to shifting right
                rightShift(i);
            }
        } else {
            // Prefer shifting to the right if closer to the end
            if (_end < _basicSize - 1) {
                rightShift(i);
            } else if (_start > 0) {
                // If no space to shift right, fall back to shifting left
                leftShift(i);
            }
        }
        // Insert x at the specified position
        region[_start + i] = x;
    }

    // Update size and _end index
    _size++;

    return *this;
}

// Shift elements to the left to make space for a new element at a lower index
void SequenceableCollection::leftShift(int i) {
    // Only shift if there is space at the start
    if (_start > 0) {
        // Shift elements one position to the left
        for (int j = _start - 1; j < _start + i; ++j) {
            region[j] = region[j + 1];
        }
        _start--; // Adjust _start after left shift
    } else {
        cout << "No space on the left to shift elements." << endl;
    }
}

// Shift elements to the right to make space for a new element at a higher index
void SequenceableCollection::rightShift(int i) {
    // Only shift if there is space at the end
    if (_end < _basicSize - 1) {
        // Shift elements one position to the right
        for (int j = _end + 1; j > _start + i; --j) {
            region[j] = region[j - 1];
        }
        _end++; // Adjust _end after right shift
    } else {
        cout << "No space on the right to shift elements." << endl;
    }
}


// Expands the storage when needed
void SequenceableCollection::grow() {
    int newCapacity = _basicSize * 2;
    int* newRegion = new int[newCapacity];

    // Copy old elements to new region
    for (int j = 0; j < _basicSize; ++j) {
        newRegion[j] = region[j];
    }

    delete[] region;  // Free old memory
    region = newRegion;
    _basicSize = newCapacity;
}

// Finds the index of the specified value; returns -1 if not found
int SequenceableCollection::find(int x) const {
    for (int i = _start; i <= _end; ++i) {
        if (region[i] == x) {
            return i - _start;  // Return position relative to the start of the collection
        }
    }
    return -1;  // Return -1 if the value is not found
}

// Removes the element at the specified index
SequenceableCollection& SequenceableCollection::removeAt(int i) {
     // Check if index i is within bounds
    if (i < 0 || i >= _end - _start + 1) {
        cout << "Index out of bounds. No element removed." << endl;
        return *this;  // No action if index is out of bounds
    }

    // Case 1: Removing the first element, just move _start up
    if (i == 0) {
        region[_start] = 0;  // Clear the first element
        _start++;  // Move _start up to the next element
    }
    // Case 2: Removing the last element, just move _end down
    else if (i == _end - _start) {
        region[_end] = 0;  // Clear the last element
        _end--;  // Move _end down to the previous element
    }
    // Case 3: Removing a middle element, so shift elements to fill the gap
    else {
        // Determine whether to shift left or right based on proximity to _start and _end
        if (i <= (_end - _start) / 2) {
            // Closer to _start, shift elements right to fill the gap
            for (int j = _start + i; j > _start; --j) {
                region[j] = region[j - 1];
            }
            region[_start] = 0;  // Clear the now-unused first position
            _start++;  // Update _start to reflect the shift
        } else {
            // Closer to _end, shift elements left to fill the gap
            for (int j = _start + i; j < _end; ++j) {
                region[j] = region[j + 1];
            }
            region[_end] = 0;  // Clear the now-unused last position
            _end--;  // Update _end to reflect the shift
        }
    }

    // Update the size after removing the element
    _size--;

    return *this;
}

// Iterates over elements, applying the function fn to each element
SequenceableCollection& SequenceableCollection::iterate(int (*fn)(int)) {
    for (int i = _start; i <= _end; ++i) {
        region[i] = fn(region[i]);
    }
    return *this;
}

void SequenceableCollection::printCollection() {
    cout << "\n" << endl;

    cout << "Start index (_start): " << _start << endl;
    cout << "End index (_end): " << _end << endl;
    cout << "Current size (_size): " << _size << endl;
    cout << "Total capacity (_basicSize): " << _basicSize << endl;

    cout << "\n" << endl;

    cout << "Indices" << endl;
    cout << "[";
    for (int z = 0; z < _basicSize; ++z) {
        cout << z << "\t";
    }
    cout << "]" << endl;

    cout << "Values" << endl;
    cout << "[";
    for (int z = 0; z < _basicSize; ++z) {
        cout << region[z] << "\t";
    }
    cout << "]" << endl;

    cout << "\n" << endl;
    
}