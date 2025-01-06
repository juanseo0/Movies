#include "hashtable.h"

// constructor
HashTable::HashTable() {
  hashTable = new HashNode *[htSize];
  for (int i = 0; i < htSize; i++) {
    hashTable[i] = nullptr;
  }
}

// destructor
HashTable::~HashTable() {
  for (int i = 0; i < htSize; i++) {
    if (hashTable[i] != nullptr) {
      HashNode *curr = hashTable[i];
      HashNode *temp;
      while (curr != nullptr) {
        temp = curr->next;
        delete curr->data;
        delete curr;
        curr = temp;
      }
    }
  }
  delete[] hashTable;
}

// adds customer to the hash table
bool HashTable::add(Customer *cData) {
  // temp node for customer
  auto *temp = new HashNode(cData);
  // find position to insert customer
  int index = getHash(cData->cID);
  // set curr node to position where customer should be in hashtable
  HashNode *curr = hashTable[index];
  // check if customer already exists in hashtable through whileloop
  while (curr != nullptr && curr->next != nullptr) {
    if (curr->data->cID == cData->cID) {
      delete temp; // delete temp to prevent memory leak
      return false;
    }
    curr = curr->next;
  }
  // if customer does not exist && curr == nullptr
  // add customer to hashtable at pos curr
  if (curr == nullptr) {
    hashTable[index] = temp;
    return true;
  }
  // else add customer to next pos if curr != nullptr
  curr->next = temp;
  return true;
}

// gets customer from the hash table
void HashTable::get(string idNumber, Customer *&cData) {
  // find pos where customer should be
  HashNode *node = hashTable[getHash(idNumber)];
  // loop to find customer, immediately returning if found
  while (node != nullptr) {
    if (node->data->cID == idNumber) {
      cData = node->data;
      return;
    }
    node = node->next;
  }
  cData = nullptr;
}

// gets the hash function
int HashTable::getHash(string &cID) const {
  return ((cID[0] - '0') + (2 * (cID[1] - '0')) + (3 * (cID[2] - '0')) +
          (4 * (cID[3] - '0'))) %
         htSize;
}