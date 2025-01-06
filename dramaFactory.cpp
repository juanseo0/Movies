#include "drama.h"

// sets type
DramaFactory::DramaFactory() { Movie::registerType('D', this); }

// creates movie
Movie *DramaFactory::createMovie() const { return new Drama(); }