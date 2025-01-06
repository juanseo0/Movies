#include "classic.h"
#include "customer.h"
#include "hashtable.h"
#include "inventory.h"
#include "movie.h"
#include <fstream>
#include <queue>
#include <sstream>

class Store {
private:
  // map for inventory of movies
  // char represents the type of movie, right now we only have "D" for DVD
  // allows for other types of movies to be added
  map<char, Inventory> movieInv;

  // hashtable for list of customers
  HashTable customerInv;

  // queues for file input
  queue<string> customerQueue;
  queue<string> movieQueue;
  queue<string> commandQueue;

public:
  // constructor & destructor
  Store(const string &customers, const string &movies, const string &commands);
  ~Store() = default;

  // helper to make queues
  void makeCustomerQueue(const string &customers);
  void makeMovieQueue(const string &movies);
  void makeCmdQueue(const string &commands);

  // add data helper
  void addCustomer();
  void addMovie();
  void addCommand();

  // add transactions to customer
  void addTransaction(string &cmdData);
};