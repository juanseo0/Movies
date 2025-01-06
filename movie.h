#ifndef MOVIE_H_
#define MOVIE_H_

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Movie; // forward declaration

// Movie Factory class
class MovieFactory {
public:
  // virtual to build movie
  virtual Movie *createMovie() const = 0;
};

class Movie {
  // overload operator<<
  friend ostream &operator<<(ostream &out, const Movie &movie);

  // print function
  virtual ostream &print(ostream &out) const;

public:
  // create method to create movie
  // takes in char (type), then corresponds to factory to create movie object
  static Movie *create(const char &type);

  /**
   * Registers a movie type with its corresponding factory.
   * This function is used to associate a movie type with its corresponding
   * factory, allowing the creation of movie objects of that type. The type
   * parameter specifies the name of the movie type, and the factory parameter
   * is a pointer to the corresponding MovieFactory object.
   */
  static void registerType(const char &type, MovieFactory *factory);

  virtual bool readMovie(string &movieData);

  // destructor
  virtual ~Movie() = default;

private:
  // map of factories
  // char represents the type of movie
  // MovieFactory represents the factory that creates the movie
  static map<char, MovieFactory *> &getFactories();

  // friend classes
  friend class Inventory;
  friend class Store;
  friend class Customer;
  friend class Transaction;

protected:
  // title of movie
  string title;

  // director of movie
  string director;

  // release date of movie
  string releaseDate;

  // stock of movie
  int stock;

  // stock of movie that has been borrowed
  int maxStock;

  // genre of movie
  char genre;

  // media type
  // default is always D
  char media;
};
#endif