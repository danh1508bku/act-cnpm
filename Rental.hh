// Rental.hh
#ifndef RENTAL_HH
#define RENTAL_HH
#include "Movie.hh"

class Rental {
public:
  Rental( const Movie& movie, int daysRented );

  int getDaysRented() const;
  const Movie& getMovie() const;

private:
  Movie _movie;
  int _daysRented;
};

inline Rental::Rental( const Movie& movie, int daysRented ):
  _movie( movie ),
  _daysRented( daysRented ) {}

inline int Rental::getDaysRented() const { return _daysRented; }

inline const Movie& Rental::getMovie() const { return _movie; }

#endif // RENTAL_HH
