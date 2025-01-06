#include "store.h"

// constructor which runs helper functions to create the queues
Store::Store(const string &customers, const string &movies,
             const string &commands) {
  makeCustomerQueue(customers);
  makeMovieQueue(movies);
  makeCmdQueue(commands);
}

// creates the queue for customers
void Store::makeCustomerQueue(const string &customers) {
  string temp;
  ifstream customerInput(customers);
  if (customerInput) {
    while (getline(customerInput, temp)) {
      if (!temp.empty()) {
        customerQueue.push(temp);
      }
    }
    addCustomer();
  } else {
    cerr << "Invalid File: " << customers << "!" << endl;
  }
}

// creates the queue for movies
void Store::makeMovieQueue(const string &movies) {
  string temp;
  ifstream movieInput(movies);
  if (movieInput) {
    while (getline(movieInput, temp)) {
      if (!temp.empty()) {
        movieQueue.push(temp);
      }
    }
    addMovie();
  } else {
    cerr << "Invalid File: " << movies << "!" << endl;
  }
}

// creates the queue for commands
void Store::makeCmdQueue(const string &commands) {
  string temp;
  ifstream cmdInput(commands);
  if (cmdInput) {
    while (getline(cmdInput, temp)) {
      if (!temp.empty()) {
        commandQueue.push(temp);
      }
    }
    addCommand();
  } else {
    cerr << "Invalid File:  " << commands << "!" << endl;
  }
}

// adds movie
void Store::addMovie() {
  while (!movieQueue.empty()) {
    Movie *temp = Movie::create(movieQueue.front()[0]);
    if (temp != nullptr) {
      if (temp->readMovie(movieQueue.front())) {
        movieInv[temp->media].addMovie(temp);
      } else {
        cerr << "Invalid Movie: " << movieQueue.front() << "!" << endl;
      }
    }
    movieQueue.pop();
  }
}

// adds customer
void Store::addCustomer() {
  string cID;
  string lName;
  string fName;
  while (!customerQueue.empty()) {
    istringstream ss(customerQueue.front());
    string current;

    getline(ss, current, ' ');
    cID = current;

    getline(ss, current, ' ');
    lName = current;

    getline(ss, current, ' ');
    fName = current;
    customerInv.add(new Customer(cID, lName, fName));
    customerQueue.pop();
  }
}

// runs the commands, calls helper function for B and R
void Store::addCommand() {
  while (!commandQueue.empty()) {
    char cmd = commandQueue.front()[0];
    if (cmd == 'B' || cmd == 'R') {
      addTransaction(commandQueue.front());
    } else if (cmd == 'I') {
      cout << "Printing store inventory: " << endl;
      movieInv['D'].displayInventory();
    } else if (cmd == 'H') {
      Customer *customer;
      customerInv.get(commandQueue.front().substr(2, 4), customer);
      if (customer != nullptr) {
        cout << "\nTransaction History for " << customer->cID << " "
             << customer->fName << " " << customer->lName << endl;
        if (customer->transHistory.empty()) {
          cout << "Customer has not made any transactions!" << endl;
        }
        for (auto &i : customer->transHistory) {
          cout << *i << endl;
        }
      }
    } else {
      cerr << "Unknown command: " << cmd << "!" << endl;
    }
    if (!commandQueue.empty()) {
      commandQueue.pop();
    }
  }
}
// runs the transaction
void Store::addTransaction(string &cmdData) {
  Customer *customer = nullptr;
  string cID = cmdData.substr(2, 4);
  customerInv.get(cID, customer); // get customer from id
  if (customer == nullptr) {
    cerr << "Unknown Customer ID: " << cID << "!" << endl;
    return;
  }
  Transaction *currTrans = Transaction::create(cmdData[0]);
  if (currTrans == nullptr) {
    cerr << "Unknown Transaction Type: " << cmdData[0] << "!" << endl;
    return;
  }
  string sortMovieType;
  string sortAttr1;
  string sortAttr2;
  if (Transaction::read(cmdData, sortMovieType, sortAttr1, sortAttr2)) {
    Movie *tempMovie = nullptr;
    movieInv['D'].retrieveMovie(sortMovieType[0], sortAttr1, sortAttr2,
                                tempMovie);
    if (tempMovie == nullptr) {
      cerr << "Unknown Movie! Movie with attributes: " << sortAttr1 << " "
           << sortAttr2 << " does not exist!" << endl;
      delete currTrans;
      return;
    } // if movie is in inventory
    if (currTrans->runTrans(tempMovie, customer, sortAttr1, sortAttr2)) {
      customer->transHistory.push_back(
          currTrans); // adds transaction to customer transaction
      return;
    }
    delete currTrans;
    return;
  }
  delete currTrans;
}