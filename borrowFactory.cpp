#include "transaction.h"

// sets type
BorrowFactory::BorrowFactory() { Transaction::addTransactionType('B', this); }

// creates borrow
Transaction *BorrowFactory::create() const { return new Borrow(); }