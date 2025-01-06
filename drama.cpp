#include "drama.h"

// constructor
Drama::Drama() {
  media = 'D';
  genre = 'D';
}

// comparison operator
bool Drama::operator>(const Drama *&mov) const {
  if (director > mov->director) {
    return true;
  }
  if (director == mov->director && title > mov->title) {
    return true;
  }
  return false;
}

// == operator
bool Drama::operator==(const Drama *&mov) const {
  return director == mov->director && title == mov->title;
}

// comparison operator
bool Drama::operator<(const Drama *&mov) const {
  if (director < mov->director) {
    return true;
  }
  if (director == mov->director && title < mov->title) {
    return true;
  }
  return false;
}
