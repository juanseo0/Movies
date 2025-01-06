#include "inventory.h"

// destructor
Inventory::~Inventory() {
  for (auto &movie : movieInventory) {
    for (auto &mov : movie.second) {
      delete mov;
    }
  }
}

// compares comedy movies
bool Inventory::compareMovieF(Movie *movie, Movie *movie2) {
  if (movie->title < movie2->title) {
    return true;
  }
  if (movie->title == movie2->title &&
      movie->releaseDate < movie2->releaseDate) {
    return true;
  }
  return false;
}

// compares drama movies
bool Inventory::compareMovieD(Movie *movie, Movie *movie2) {
  if (movie->director < movie2->director) {
    return true;
  }
  if (movie->director == movie2->director && movie->title < movie2->title) {
    return true;
  }
  return false;
}

// Compares classic movies
// Classics (‘C’) are sorted by Release date (Month and Date), then Major
// actor(First and Last Name) dynamic cast to classic needed to access
// majorActor (private) and month (private)
bool Inventory::compareMovieC(Movie *movie, Movie *movie2) {
  if (movie->releaseDate < movie2->releaseDate ||
      (movie->releaseDate == movie2->releaseDate &&
       dynamic_cast<Classic *>(movie)->month <
           dynamic_cast<Classic *>(movie2)->month)) {
    return true;
  }
  if (movie->releaseDate == movie2->releaseDate &&
      dynamic_cast<Classic *>(movie)->month ==
          dynamic_cast<Classic *>(movie2)->month) {
    if (dynamic_cast<Classic *>(movie)->majorActor <
        dynamic_cast<Classic *>(movie2)->majorActor) {
      return true;
    }
  }
  return false;
}

// checks if comedy movies are the same
bool Inventory::equalsMovieF(Movie *movie, Movie *movie2) {
  return movie->title == movie2->title &&
         movie->releaseDate == movie2->releaseDate;
}

// checks if drama movies are the same
bool Inventory::equalsMovieD(Movie *movie, Movie *movie2) {
  return movie->director == movie2->director && movie->title == movie2->title;
}

// checks if classic movies are the same
bool Inventory::equalsMovieC(Movie *movie, Movie *movie2) {
  return movie->releaseDate == movie2->releaseDate &&
         dynamic_cast<Classic *>(movie)->month ==
             dynamic_cast<Classic *>(movie2)->month &&
         dynamic_cast<Classic *>(movie)->majorActor ==
             dynamic_cast<Classic *>(movie2)->majorActor;
}

// adds the movies
bool Inventory::addMovie(Movie *movie) {
  // find vector for movie type
  char genre = movie->genre;
  auto current = movieInventory.find(genre);

  if (current == movieInventory.end()) {
    vector<Movie *> movies;
    movies.push_back(movie);
    movieInventory.insert(make_pair(genre, movies));
    return true;
  }

  switch (genre) {
  case 'F':
    if (find_if(current->second.begin(), current->second.end(),
                [this, movie](Movie *m) {
                  return this->equalsMovieF(m, movie);
                }) != current->second.end()) {
      cerr << "Error: Movie already exists in inventory" << endl;
      return false;
    }
    current->second.push_back(movie);
    sort(current->second.begin(), current->second.end(),
         [this](Movie *a, Movie *b) { return this->compareMovieF(a, b); });
    break;
  case 'D':
    if (find_if(current->second.begin(), current->second.end(),
                [this, movie](Movie *m) {
                  return this->equalsMovieD(m, movie);
                }) != current->second.end()) {
      cerr << "Error: Movie already exists in inventory" << endl;
      return false;
    }
    current->second.push_back(movie);
    sort(current->second.begin(), current->second.end(),
         [this](Movie *a, Movie *b) { return this->compareMovieD(a, b); });
    break;
  case 'C':
    if (find_if(current->second.begin(), current->second.end(),
                [this, movie](Movie *m) {
                  return this->equalsMovieC(m, movie);
                }) != current->second.end()) {
      cerr << "Error: Movie already exists in inventory" << endl;
      return false;
    }
    current->second.push_back(movie);
    sort(current->second.begin(), current->second.end(),
         [this](Movie *a, Movie *b) { return this->compareMovieC(a, b); });
    break;
  default:
    cerr << "Error: Invalid genre " << genre << endl;
    return false;
  }

  return true;
}

// retrieves movie from inventory
void Inventory::retrieveMovie(char type, const string &attributeA,
                              const string &attributeB, Movie *&movie) {
  for (auto &mov : movieInventory[type]) {
    if (type == 'F') {
      if (mov->title == attributeA && mov->releaseDate == attributeB) {
        movie = mov;
        return;
      }
    } else if (type == 'D') {
      if (mov->director == attributeA && mov->title == attributeB) {
        movie = mov;
        return;
      }
    } else if (type == 'C') {
      string temp;
      string releaseMonth;
      string releaseYear;
      istringstream ss(attributeA);
      getline(ss, temp, ' '); // get release month
      releaseMonth = temp;
      getline(ss, temp, ' '); // get release year
      releaseYear = temp;
      if (mov->releaseDate == releaseYear &&
          dynamic_cast<Classic *>(mov)->month == releaseMonth &&
          dynamic_cast<Classic *>(mov)->majorActor == attributeB) {
        movie = mov;
        return;
      }
    }
  }
}

// displays the inventory
void Inventory::displayInventory() const {
  for (auto it = movieInventory.rbegin(); it != movieInventory.rend(); ++it) {
    for (const auto &mov : it->second) {
      cout << *mov << endl;
    }
  }
}