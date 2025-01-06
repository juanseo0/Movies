#include "comedy.h"

// constructor
Comedy::Comedy() {
  media = 'D';
  genre = 'F';
}

// comparison operator
bool Comedy::operator>(const Comedy *&mov) const {
  if (title > mov->title) {
    return true;
  }
  if (title == mov->title && releaseDate > mov->releaseDate) {
    return true;
  }
  return false;
}

//== operator
bool Comedy::operator==(const Comedy *&mov) const {
  return title == mov->title && releaseDate == mov->releaseDate;
}

// comparison operator
bool Comedy::operator<(const Comedy *&mov) const {
  if (title < mov->title) {
    return true;
    if (title == mov->title && releaseDate < mov->releaseDate) {
      return true;
    }
  }
  return false;
}
