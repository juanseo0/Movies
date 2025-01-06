#include "customer.h"
#include <iostream>

using namespace std;

// hash node struct used in hash table
struct HashNode {
public:
  Customer *data;
  HashNode *next;
  explicit HashNode(Customer *cData) : data(cData), next(nullptr) {}
};

class HashTable {
public:
  // constructor destructor
  HashTable();
  ~HashTable();

  // add customer into the hashtable
  bool add(Customer *cData);

  // get customer from the hashtable
  void get(string idNumber, Customer *&cData);

private:
  // hash table
  HashNode **hashTable;

  // size of hashtable
  const int htSize = 23;

  // get hash function
  int getHash(string &cID) const;
};