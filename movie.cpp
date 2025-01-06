#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"

// factories for movies
ComedyFactory comedyFactory;
DramaFactory dramaFactory;
ClassicFactory classicFactory;

// output operator
ostream &operator<<(ostream &out, const Movie &movie) {
  return movie.print(out);
}

// reads the movie
bool Movie::readMovie(string &movieData) { // assumes all inputs are correct
                                           // according to assignment specs
  istringstream ss(movieData);
  string current;

  getline(ss, current, ','); // skip genre

  getline(ss, current, ','); // get stock
  size_t pos = current.find_first_not_of(' ');
  if (pos != string::npos) {
    current = current.substr(pos);
  }
  stock = stoi(current); // convert stock to int
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

  getline(ss, current, ','); // get date
  pos = current.find_first_not_of(' ');
  if (pos != string::npos) {
    current = current.substr(pos);
  }
  releaseDate = current; // get date

  return true;
}

// prints the movie
ostream &Movie::print(ostream &out) const {
  out << "[" << media << "] | Genre: " << genre << " | Title: " << title
      << " | Director: " << director << endl;
  out << "Release Date: " << releaseDate << endl;
  out << "Stock: " << stock << "/" << maxStock << endl;
  return out;
}

// Registers a movie type with its corresponding factory.
// intializes map of factories
// this method is called in the constructor of each movie factory(instances
// above)
void Movie::registerType(const char &type, MovieFactory *factory) {
  getFactories()[type] = factory;
}

// creates the movie
Movie *Movie::create(const char &type) {
  if (getFactories().find(type) == getFactories().end()) {
    cerr << "Unknown genre " << type << endl;
    return nullptr;
  }
  return getFactories()[type]->createMovie();
}

// gets the factory
map<char, MovieFactory *> &Movie::getFactories() {
  static map<char, MovieFactory *> factories;
  return factories;
}