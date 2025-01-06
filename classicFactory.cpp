#include "classic.h"

// sets type
ClassicFactory::ClassicFactory() { Movie::registerType('C', this); }

// creates movie
Movie *ClassicFactory::createMovie() const { return new Classic(); }
