#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include "customer.h"
#include "movie.h"
#include <iostream>

class Customer;

class Transaction;

class TransactionFactory {
public:
  // builds transaction
  virtual Transaction *create() const = 0;
};

class Transaction {

public:
  // constructor
  virtual ~Transaction() = default;

  // the type of transaction
  char transactionType;

  // movie used in transaction
  Movie *movie;

  // creates the transaction of type
  static Transaction *create(const char &type);

  // reads in the transaction command
  static bool read(string &cmdData, string &sortMovieType, string &sortAttr1,
                   string &sortAttr2);

  //runs the transaction commands
  bool runTrans(Movie *&tempMovie, Customer *&customer, string &sortAttr1,
                string &sortAttr2);

  //adds the transaction type
  static void addTransactionType(const char &type, TransactionFactory *factory);

  // prints the transaction
  virtual ostream &print(std::ostream &out) const;
  // output operator
  friend ostream &operator<<(ostream &out, const Transaction &transaction);

private:
  // map of factories
  static map<char, TransactionFactory *> &getFactory();

  // friend classes
  friend class Store;
  friend class Inventory;
  friend class Customer;
};

class BorrowFactory : public TransactionFactory {
public:
  // constructor
  BorrowFactory();

  // creates borrow transaction
  Transaction *create() const override;
};

class ReturnFactory : public TransactionFactory {
public:
  // constructor
  ReturnFactory();

  // creates return transaction
  Transaction *create() const override;
};

class Borrow : public Transaction {
private:
  // constructor
  explicit Borrow();

  // friend classes
  friend class BorrowFactory;
  friend class Store;
  friend class Inventory;
  friend class Customer;
};

class Return : public Transaction {
private:
  // constructor
  explicit Return();

  // friend classes
  friend class ReturnFactory;
};

#endif