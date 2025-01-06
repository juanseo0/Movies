#ifndef COMEDY_H_
#define COMEDY_H_

#include "movie.h"
#include <iostream>
#include <string>

using namespace std;
/*
 * Comedy class
 * Represents a comedy movie
 * Comedy (‘F’) sorted by Title, then Year it released
 */
class Comedy : public Movie {
public:
  // operator overloading
  bool operator>(const Comedy *&mov) const;
  bool operator==(const Comedy *&mov) const;
  bool operator<(const Comedy *&mov) const;

  // default constructor
  Comedy();

private:
  // friend classes
  friend class ComedyFactory;
  friend class Inventory;
  friend class Store;
  friend class Customer;
};
/*
 * ComedyFactory class
 * Represents a factory for creating comedy movies
 */
class ComedyFactory : public MovieFactory {
public:
  // constructor
  ComedyFactory();

  // overidded method that creates a comedy movie
  Movie *createMovie() const override;
};
#endif
