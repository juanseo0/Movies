#include "transaction.h"
#include "customer.h"

BorrowFactory bFactory;
ReturnFactory rFactory;

// create function
Transaction *Transaction::create(const char &type) {
  if (getFactory().count(type) > 0) {
    return getFactory().at(type)->create();
  }
  cerr << "Unknown factory: " << type << "!" << endl;
  return nullptr;
}

// runs the transaction
bool Transaction::runTrans(Movie *&tempMovie, Customer *&customer,
                           string &sortAttr1, string &sortAttr2) {
  if (transactionType == 'B') { // borrowing movie
    if (tempMovie->stock > 0) { // movie is in stock
      movie = tempMovie;        // set the transaction movie
      tempMovie->stock -= 1;    // reduces stock by 1
      customer->borrowedList.emplace_back(
          tempMovie); // adds movie to customer borrowed list
      return true;
    }
    cerr << "Movie Genre: " << tempMovie->genre
         << " | Title: " << tempMovie->title << " is out of stock!" << endl;
    return false;
  }
  if (transactionType == 'R') { // returning movie
    if (customer->hasMovie(tempMovie->genre, sortAttr1,
                           sortAttr2)) { // if customer has borrowed movie
      customer->returnMovie(tempMovie->genre, sortAttr1,
                            sortAttr2); // returns movie
      movie = tempMovie;                // set the transaction movie
      tempMovie->stock += 1;            // adds stock by 1
      return true;
    } // customer has not borrowed movie
    cerr << "Customer " << customer->cID
         << " does not have Movie Genre: " << tempMovie->genre
         << " | Title: " << tempMovie->title << "!" << endl;
    return false;
  }
  cerr << "Unknown transaction type: " << transactionType << "!" << endl;
  return false;
}

// reads the transaction
bool Transaction::read(string &cmdData, string &sortMovieType,
                       string &sortAttr1, string &sortAttr2) {
  char mediaN = cmdData[7];
  char genreN = cmdData[9];
  if (mediaN == 'D') {
    if (genreN == 'C') {
      // addClassicTrans(cmdData, customer);
      istringstream ss(cmdData);
      string current;
      string transType;
      string movieType;
      string releaseDate;
      string majorActor;
      getline(ss, current, ' '); // get transaction type
      transType = current;
      getline(ss, current, ' '); // get customer id
      getline(ss, current, ' '); // get Media type
      getline(ss, current, ' '); // get movie type
      movieType = current;
      getline(ss, current, ' '); // get release month
      releaseDate = current;
      getline(ss, current, ' '); // get release year
      releaseDate += " " + current;
      getline(ss, current, ' '); // get actor first name
      majorActor = current;
      getline(ss, current, ' '); // get actor first name
      majorActor += " " + current;
      sortMovieType = movieType;
      sortAttr1 = releaseDate;
      sortAttr2 = majorActor;
      return true;
    }
    if (genreN == 'D') {
      string current;
      string director;
      string title;
      string transType;
      string movieType;
      istringstream ss(cmdData);
      getline(ss, current, ' '); // get transaction type
      transType = current;
      getline(ss, current, ' '); // get customer id
      getline(ss, current, ' '); // get Media type
      getline(ss, current, ' '); // get movie type
      movieType = current;
      getline(ss, current, ','); // get director
      director = current;
      getline(ss, current, ','); // get title
      current.erase(0, 1);       // remove space in front of title
      title = current;
      sortMovieType = movieType;
      sortAttr1 = director;
      sortAttr2 = title;
      return true;
    }
    if (genreN == 'F') {
      // addComedyTrans(cmdData, customer);
      string current;
      string title;
      string year;
      string transType;
      string movieType;
      istringstream ss(cmdData);
      getline(ss, current, ' '); // get transaction type
      transType = current;
      getline(ss, current, ' '); // get customer id
      getline(ss, current, ' '); // get Media type
      getline(ss, current, ' '); // get movie type
      movieType = current;
      getline(ss, current, ','); // get title
      title = current;
      getline(ss, current, ' '); // get empty space
      getline(ss, current, ' '); // get year
      year = current;
      sortMovieType = movieType;
      sortAttr1 = title;
      sortAttr2 = year;
      return true;
    }
    cerr << "Unknown Genre: " << genreN << "!" << endl;
    return false;
  }
  cerr << "Unknown Media type: " << mediaN << "!" << endl;
  return false;
}

// adds transaction type
void Transaction::addTransactionType(const char &type,
                                     TransactionFactory *factory) {
  getFactory().emplace(type, factory);
}

// gets the factory map
map<char, TransactionFactory *> &Transaction::getFactory() {
  static map<char, TransactionFactory *> factoryMap;
  return factoryMap;
}

// output operator
ostream &operator<<(ostream &out, const Transaction &transaction) {
  return transaction.print(out);
}

// print operator
ostream &Transaction::print(ostream &out) const {
  out << "[" << transactionType << "] Type: " << movie->genre
      << " | Title: " << movie->title;
  return out;
}
