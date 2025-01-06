#include "classic.h"

// constructor
Classic::Classic() {
  media = 'D';
  genre = 'C';
}

// reads movie in
bool Classic::readMovie(string &movieData) { // assumes all inputs are correct
                                             // according to assignment specs
  istringstream ss(movieData);
  string current;

  getline(ss, current, ','); // skip genre

  getline(ss, current, ','); // get stock
  size_t pos = current.find_first_not_of(' ');
  if (pos != string::npos) {
    current = current.substr(pos);
  }
  stock = stoi(current); // get max stock
  maxStock = stock;

  getline(ss, current, ','); // get director
  pos = current.find_first_not_of(' ');
  if (pos != string::npos) {
    current = current.substr(pos);
  }
  director = current; // get director

  getline(ss, current, ','); // get title
  pos = current.find_first_not_of(' ');
  if (pos != string::npos) {
    current = current.substr(pos);
  }
  title = current; // get title

  getline(ss, current, ' '); // remove space
  pos = current.find_first_not_of(' ');
  if (pos != string::npos) {
    current = current.substr(pos);
  }

  getline(ss, current, ' '); // get major actor's first name
  pos = current.find_first_not_of(' ');
  string tempMajorActor = current;

  getline(ss, current, ' ');       // get major actor's last name
  tempMajorActor += " " + current; // append major actor's last name

  majorActor = tempMajorActor; // set major actor's name

  getline(ss, current, ' '); // get release month
  month = current;           // set release month

  getline(ss, current);  // get release year
  releaseDate = current; // append release year

  return true;
}

// comparison operator
//  Classics (‘C’) are sorted by Release date, then Major actor
bool Classic::operator>(const Classic *&mov) const {
  if (releaseDate > mov->releaseDate) {
    return true;
  }
  if (releaseDate == mov->releaseDate && month > mov->month) {
    return true;
  }
  if (releaseDate == mov->releaseDate && month == mov->month &&
      majorActor > mov->majorActor) {
    return true;
  }
  return false;
}

//== operator
bool Classic::operator==(const Classic *&mov) const {
  return releaseDate == mov->releaseDate && month == mov->month &&
         majorActor == mov->majorActor;
}

// comparison operator
bool Classic::operator<(const Classic *&mov) const {
  if (releaseDate < mov->releaseDate) {
    return true;
  }
  if (releaseDate == mov->releaseDate && month < mov->month) {
    return true;
  }
  if (releaseDate == mov->releaseDate && month == mov->month &&
      majorActor < mov->majorActor) {
    return true;
  }
  return false;
}

// output operator
ostream &operator<<(ostream &out, const Classic &movie) {
  return movie.print(out);
}

// print function
ostream &Classic::print(ostream &out) const {
  out << "[" << media << "] | Genre: " << genre << " | Title: " << title
      << " | Director: " << director << endl;
  out << "Major Actor: " << majorActor << endl;
  out << "Release Date: " << releaseDate << " | Month: " << month << endl;
  out << "Stock: " << stock << "/" << maxStock << endl;
  return out;
}
