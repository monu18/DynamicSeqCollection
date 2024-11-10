#include "SequenceableCollection.h"
#include <iostream>
using namespace std;

/*
Default Constructor
*/
SequenceableCollection::SequenceableCollection() : _start(3), _end(2), _size(0), _basicSize(8) {

	region = new int[_basicSize];     // Allocating initial capacity
	for (int z = 0; z < _basicSize; z++) {
		region[z] = 0;
	}
}

/*
Copy Constructor
*/
SequenceableCollection::SequenceableCollection(const SequenceableCollection& sequenceableCollection)
    : _start(sequenceableCollection._start), _end(sequenceableCollection._end), _size(sequenceableCollection._size), _basicSize(sequenceableCollection._basicSize) {
    region = new int[_basicSize];
    for (int i = 0; i < _basicSize; ++i) {
        region[i] = sequenceableCollection.region[i];
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
        std::cout << "......Index is out of bounds....." << std::endl;
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
    } else if (i == 0 && _start > 0) {
        // Insert at the beginning without shifting if there's space
        _start--;
        region[_start] = x;
    } else if (i == _end - _start + 1) {
        // Insert at the end
        if (_end + 1 >= _basicSize && _start > 0) {
            // Shift everything left to make space if there's room at the start
            int shiftAmount = _start;
            for (int j = _start; j <= _end; ++j) {
                region[j - shiftAmount] = region[j];
            }
            _end -= shiftAmount;
            _start = 0;
        }
        // Insert x at the end
        _end++;
        region[_end] = x;
    } else {
        // Shift elements if inserting in the middle
        if (i <= (_end - _start) / 2) {
            // Closer to _start, shift elements to the left
            leftShift(i);
        } else {
            // Closer to _end, shift elements to the right
            rightShift(i);
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
    if (_start == 0) {
        // If already at the start, can't shift left, call grow instead
        grow();
        return;
    }

    // Shift elements one position to the left
    for (int j = _start - 1; j < _start + i; ++j) {
        region[j] = region[j + 1];
    }

    // Update the starting index after the shift
    _start--;
}

// Shift elements to the right to make space for a new element at a higher index
void SequenceableCollection::rightShift(int i) {
    if (_end == _basicSize - 1) {
        // If already at the end, can't shift right, call grow instead
        grow();
        return;
    }

    // Shift elements one position to the right
    for (int j = _end + 1; j > _start + i; --j) {
        region[j] = region[j - 1];
    }

    // Update the ending index after the shift
    _end++;
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
    if (i < 0 || i > _end - _start) {
        std::cout << "......Index is out of bounds....." << std::endl;
        return *this;  // Do nothing if out of bounds
    }

    // Shift elements to the left to fill the gap left by the removed element
    for (int j = _start + i; j < _end; ++j) {
        region[j] = region[j + 1];
    }

    // Set the now-unused last element to 0
    region[_end] = 0;

    _end--;
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
    std::cout << "\n" << std::endl;

    std::cout << "Start index (_start): " << _start << std::endl;
    std::cout << "End index (_end): " << _end << std::endl;
    std::cout << "Current size (_size): " << _size << std::endl;
    std::cout << "Total capacity (_basicSize): " << _basicSize << std::endl;

    std::cout << "\n" << std::endl;

    std::cout << "Indices" << std::endl;
    std::cout << "[";
    for (int z = 0; z < _basicSize; ++z) {
        std::cout << z << "\t";
    }
    std::cout << "]" << std::endl;

    std::cout << "Values" << std::endl;
    std::cout << "[";
    for (int z = 0; z < _basicSize; ++z) {
        std::cout << region[z] << "\t";
    }
    std::cout << "]" << std::endl;

    std::cout << "\n" << std::endl;
    
}