// https://github.com/mynguyen5194/US-Counties-Database-Analysis/blob/master/HashTable.h

#ifndef HashTable_hpp
#define HashTable_hpp

#include <iostream>
using namespace std;

template <class ItemType>
class HashTable {
private:
    ItemType * table;
    int loadNumber;
    int numberOfCollision;
    int TABLE_SIZE;
    
public:
    HashTable(const int hashSize);
    ~HashTable();
    
    bool isEmpty();
    int hash(const ItemType & newEntry);
    bool insert(const ItemType & newEntry);
    bool search(const ItemType & target, ItemType & returnTarget);
    bool remove(const ItemType target);
    void printItem(ItemType * nodePtr, bool displayList, void visit(ItemType &));
    void displayList(void visit(ItemType &));
    void printHashTable(void visit(ItemType &));
    int countNode(int index);
};

template <class ItemType>
HashTable<ItemType>::HashTable(const int hashSize) {
    TABLE_SIZE = hashSize;
    table = new ItemType[TABLE_SIZE];
    loadNumber = 0;
    numberOfCollision = 0;
}

template <class ItemType>
HashTable<ItemType>::~HashTable() {
    ItemType * currentPtr;
    ItemType * nextPtr;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        currentPtr = table[i].getNext();
        table[i].setNext(NULL); // Disconnect linked list from hash table
        
        // Start deleting the linked list from the beginning
        while (currentPtr) {
            nextPtr = currentPtr;
            currentPtr = currentPtr->getNext();
            delete nextPtr;
        }
    }
    delete [] table;
}

template <class ItemType>
bool HashTable<ItemType>::isEmpty() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].getTimestamp() == "") {
            return false;
        }
    }
    return true;
}


// FIX NEEDED
template <class ItemType>
int HashTable<ItemType>::hash(const ItemType & newEntry) {
    int index = 0;
    
    for (int i = 0; i < newEntry.getTimestamp().length(); ++i) {
        index ^= (index << 5) + (index >> 2) + newEntry.getTimestamp()[i];
    }
    
    return (index % TABLE_SIZE);
}

template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType & newEntry) {
    bool success = false;
    ItemType * newNode = new ItemType(newEntry);
    int index = hash(newEntry); // Get the index
    ItemType * nodePtr = &table[index];
    
    // if the place in the hash table is empty
    if (table[index].getTimestamp() == "") {
        table[index] = *newNode;
        loadNumber++;
        success = true;
    }
    
    // if not, then create a linked list at this index
    else {
        while (nodePtr->getNext())
            nodePtr = nodePtr->getNext();
        nodePtr->setNext(newNode);
        
        numberOfCollision++;
        success = true;
    }
    
    return success;
}

template <class ItemType>
bool HashTable<ItemType>::search(const ItemType & target, ItemType & returnTarget) {
    bool found = false;
    
    int index = hash(target);   // Get the index of the entered value
    ItemType * nodePtr = &table[index];
    
    while (nodePtr) {
        if (nodePtr->getKey() == target.getTimestamp()) {
            returnTarget = *nodePtr;
            found = true;
        }
        nodePtr = nodePtr->getNext();
    }
    
    if (!found)
        found = false;
    
    return found;
}


template <class ItemType>
bool HashTable<ItemType>::remove(const ItemType target) {
    bool deleted = false;
    ItemType * delPtr;
    
    int index = hash(target);
    
    if (table[index].getTimestamp() != "") {
        ItemType * tempPtr = NULL;
        ItemType * nodePtr = &table[index];
        
        // Walk the nodePtr and temPtr until the target is found
        while (nodePtr->getNext() != NULL && nodePtr->getTimestamp() != target.getTimestamp()) {
            tempPtr = nodePtr;
            nodePtr = nodePtr->getNext();
        }
        
        if (nodePtr->getTimestamp() == target.getTimestamp()) {
            // If the target is found in the hash table
            if (tempPtr == NULL) {
                delPtr = new ItemType(table[index]);
                if (nodePtr->getNext() == NULL) {
                    // Overwrite the data to delete the element in the hash table
                    table[index].setAlert("", 0, "", "", "", 0, "", 0);
                    deleted = true;
                }
                else {
                    // Swap the first node in the linked list with the table[index]
                    table[index].setInfo(nodePtr->getNext()->getTimestamp(), nodePtr->getNext()->getSignatureID(),
                                         nodePtr->getNext()->getMessage(),nodePtr->getNext()->getProtocol(),
                                         nodePtr->getNext()->getSourceIP(), nodePtr->getNext()->getsourcePort(),
                                         nodePtr->getNext()->getDestinationIP(), nodePtr->getNext()->getDestinationPort());
                    ItemType *temp_del = nodePtr->getNext();
                    nodePtr->setNext(temp_del->getNext());
                    
                    delete temp_del;
                    deleted = true;
                }
            }
            // If the target is found in the linked lists
            else {
                if (nodePtr->getNext())
                    tempPtr->setNext(nodePtr->getNext());
                else
                    tempPtr->setNext(NULL);
                
                delete nodePtr;
                deleted = true;
            }
        }
    }
    
    return deleted;
}

template <class ItemType>
void HashTable<ItemType>::printItem(ItemType * nodePtr, bool displayList , void visit(ItemType &)) {
    ItemType item;
    
    item.setAlert(nodePtr->getTimestamp(), nodePtr->getSignatureID(), nodePtr->getMessage(),
                  nodePtr->getProtocol(), nodePtr->getSourceIP(), nodePtr->getsourcePort,
                  nodePtr->getDestinationIP, nodePtr->getDestinationPort);
    if (!displayList) {
        cout << "\t       ";
    }
    visit(item);
    
    return;
}

template <class ItemType>
void HashTable<ItemType>::displayList(void visit(ItemType &)) {
    // Print the hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        ItemType * nodePtr = &table[i];
        printItem(nodePtr, true, visit);
        
        // Print the linked list if any
        while (nodePtr->getNext()) {
            nodePtr = nodePtr->getNext();
            printItem(nodePtr, true, visit);
        }
    }
    return;
}

template <class ItemType>
void HashTable<ItemType>::printHashTable(void (visit)(ItemType &)) {
    // Print the hash table and the index
    for (int i = 0; i < TABLE_SIZE; i++) {
        ItemType * nodePtr = &table[i];
        cout << "Index " << i << ": ";
        if (nodePtr->getTimestamp() != "") {
            printItem(nodePtr, true, visit);
            
            // Print the linked list if any
            while (nodePtr->getNext()) {
                nodePtr = nodePtr->getNext();
                printItem(nodePtr, false, visit);
            }
        }
        else
            cout << "// Empty" << endl;
    }
    return;
}

template <class ItemType>
int HashTable<ItemType>::countNode(int index) {
    int number = 0;
    ItemType * nodePtr = &table[index];
    
    if (!nodePtr)
        return 0;
    
    else {
        while (nodePtr->getNext()) {
            nodePtr = nodePtr->getNext();
            number++;
        }
    }
    return number;
}


#endif /* HashTable_hpp */
