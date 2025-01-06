#include "comedy.h"
// sets type
ComedyFactory::ComedyFactory() { Movie::registerType('F', this); }

// creates movie
Movie *ComedyFactory::createMovie() const { return new Comedy(); }