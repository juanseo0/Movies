#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "classic.h"
#include "movie.h"
#include "transaction.h"
#include <sstream>

class Transaction;

class Customer {
public:
  // constructor & destructor
  Customer();
  Customer(string id, string first, string last);
  ~Customer();

  // check if customer has movie
  bool hasMovie(char type, const string &sortAttr1, const string &sortAttr2);

  // return movie / remove from borrowedList
  bool returnMovie(char type, const string &sortAttr1, const string &sortAttr2);

private:
  // customer id
  string cID;
  // customer first name
  string fName;
  // customer last name
  string lName;

  // vector of borrowed movie
  vector<Movie *> borrowedList;

  // vector of transactions
  // change string to transaction class later
  vector<Transaction *> transHistory;

  // friend classes
  friend class HashTable;
  friend class Inventory;
  friend class Movie;
  friend class Store;
  friend class Transaction;
};
#endif