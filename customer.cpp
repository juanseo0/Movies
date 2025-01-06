#include "customer.h"

// constructor
Customer::Customer() {
  fName = "";
  lName = "";
  cID = "";
}

// constrctor
Customer::Customer(string id, string first, string last) {
  this->cID = id;
  this->fName = first;
  this->lName = last;
}

// destructor
Customer::~Customer() {

  for (int i = 0; i < transHistory.size(); i++) {
    delete transHistory[i];
  }
}

// checks if customer has movie
bool Customer::hasMovie(char type, const string &sortAttr1,
                        const string &sortAttr2) {
  for (int i = 0; i < borrowedList.size(); i++) {
    if (type == 'F' && borrowedList[i]->title == sortAttr1 &&
        borrowedList[i]->releaseDate == sortAttr2) {
      return true;
    }
    if (type == 'D' && borrowedList[i]->director == sortAttr1 &&
        borrowedList[i]->title == sortAttr2) {
      return true;
    }
    if (type == 'C' &&
        dynamic_cast<Classic *>(borrowedList[i])->majorActor == sortAttr2) {
      string temp;
      string releaseMonth;
      string releaseYear;
      istringstream ss(sortAttr1);
      getline(ss, temp, ' '); // get release month
      releaseMonth = temp;
      getline(ss, temp, ' '); // get release year
      releaseYear = temp;
      if (borrowedList[i]->releaseDate == releaseYear &&
          dynamic_cast<Classic *>(borrowedList[i])->month == releaseMonth) {
        return true;
      }
    }
  }
  return false;
}

// returns a movie
bool Customer::returnMovie(char type, const string &sortAttr1,
                           const string &sortAttr2) {
  for (int i = 0; i < borrowedList.size(); i++) {
    if (type == 'F' && borrowedList[i]->title == sortAttr1 &&
        borrowedList[i]->releaseDate == sortAttr2) {
      borrowedList.erase(borrowedList.begin() + i);
      return true;
    }
    if (type == 'D' && borrowedList[i]->director == sortAttr1 &&
        borrowedList[i]->title == sortAttr2) {
      borrowedList.erase(borrowedList.begin() + i);
      return true;
    }
    if (type == 'C' &&
        dynamic_cast<Classic *>(borrowedList[i])->majorActor == sortAttr2) {
      string temp;
      string releaseMonth;
      string releaseYear;
      istringstream ss(sortAttr1);
      getline(ss, temp, ' '); // get release month
      releaseMonth = temp;
      getline(ss, temp, ' '); // get release year
      releaseYear = temp;
      if (borrowedList[i]->releaseDate == releaseYear &&
          dynamic_cast<Classic *>(borrowedList[i])->month == releaseMonth) {
        borrowedList.erase(borrowedList.begin() + i);
        return true;
      }
    }
  }
  return false;
}