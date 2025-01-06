#include "transaction.h"

// adds the transaction type
ReturnFactory::ReturnFactory() { Transaction::addTransactionType('R', this); }

// creates the transaction
Transaction *ReturnFactory::create() const { return new Return(); }