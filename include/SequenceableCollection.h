
#ifndef SEQUENCEABLE_COLLECTION_H
#define SEQUENCEABLE_COLLECTION_H

class SequenceableCollection {
public:
    SequenceableCollection();  // Default constructor
    SequenceableCollection(int);  // Constructor with initial element
    SequenceableCollection(const SequenceableCollection&);  // Copy constructor
    virtual ~SequenceableCollection();  // Virtual destructor

    int basicSize() const;  // Returns the capacity of the allocated region
    int size() const;  // Returns the number of elements in the collection
    SequenceableCollection& insertAt(int index, int value);  // Inserts value at specified index
    int find(int value) const;  // Finds the index of a value, returns -1 if not found
    SequenceableCollection& removeAt(int index);  // Removes element at specified index
    SequenceableCollection& iterate(int (*fn)(int));  // Applies function to each element

    // for testing purpose
    void printCollection();  // print Sequenceable Collection


protected:
    int _start;
    int _end;
    int _size;
	int _basicSize;
	int* region;

    void grow();  // Expands the storage when needed

    //helper functions
    void leftShift(int i);  // Shifts elements left to make space
    void rightShift(int i);  // Shifts elements right to make space
};

#endif