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
    void statistics();
    int countNode(int index);
};

#endif /* HashTable_hpp */
