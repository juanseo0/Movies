#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "algorithm"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "movie.h"
#include <sstream>

class Inventory {
public:
  // constructor
  Inventory() = default;

  // destructor
  ~Inventory();
  // adds movie to inventory
  bool addMovie(Movie *movie);

  // retrieve movie, returns through movie pointer
  // varA and varB depends on how movie genre is sorted
  // Comedy (‘F’) sorted by Title, then Year it released
  // Drama (‘D’) sorted by Director, then Title
  // Classics (‘C’) are sorted by Release date, then Major actor
  void retrieveMovie(char type, const string &attributeA,
                     const string &attributeB, Movie *&movie);

  // display inventory
  void displayInventory() const;

private:
  // map for inventory of movies
  map<char, vector<Movie *>> movieInventory;

  // comparison functions
  static bool compareMovieF(Movie *movie, Movie *movie2);
  static bool compareMovieD(Movie *movie, Movie *movie2);
  static bool compareMovieC(Movie *movie, Movie *movie2);

  // checks if movies are the same
  static bool equalsMovieF(Movie *movie, Movie *movie2);
  static bool equalsMovieD(Movie *movie, Movie *movie2);
  static bool equalsMovieC(Movie *movie, Movie *movie2);

  // friend classes
  friend class store;
};
#endif
