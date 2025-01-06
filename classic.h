#ifndef CLASSIC_H_
#define CLASSIC_H_

#include "movie.h"
#include <iostream>
#include <string>

using namespace std;
/*
 * Classic class
 * Represents a classic movie
 * Classics (‘C’) are sorted by Release date, then Major actor
 */
class Classic : public Movie {
public:
  // default constructor
  Classic();

  // operator overloading
  bool operator>(const Classic *&mov) const;
  bool operator==(const Classic *&mov) const;
  bool operator<(const Classic *&mov) const;

  friend ostream &operator<<(ostream &out, const Classic &movie);
  ostream &print(ostream &out) const override;
  bool readMovie(string &movieData) override;

private:
  // first and last name of major actor
  string majorActor;

  // release month of movie
  string month;

  // friend classes
  friend class ClassicFactory;
  friend class Inventory;
  friend class Store;
  friend class Customer;
};

/*
 * ClassicFactory class
 * Represents a factory for creating classic movies
 */
class ClassicFactory : public MovieFactory {
public:
  // constructor
  ClassicFactory();

  // overided method that creates a classic movie
  Movie *createMovie() const override;
};
#endif