#ifndef DRAMA_H_
#define DRAMA_H_

#include "movie.h"
#include <iostream>
#include <string>

using namespace std;
/*
 * Drama class
 * Represents a drama movie
 * Dramas (‘D’) are sorted by Director, then Title
 */
class Drama : public Movie {
public:
  // default constructor
  Drama();

  // operator overloading
  bool operator>(const Drama *&mov) const;
  bool operator==(const Drama *&mov) const;
  bool operator<(const Drama *&mov) const;

private:
  // friend classes
  friend class DramaFactory;
  friend class Inventory;
  friend class Store;
  friend class Customer;
};

/*
 * DramaFactory class
 * Represents a factory for creating drama movies
 */
class DramaFactory : public MovieFactory {
public:
  // constructor
  DramaFactory();

  // overidded method that creates a drama movie
  Movie *createMovie() const override;
};
#endif