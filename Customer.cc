// Customer.cc
#include <sstream>
#include <vector>
#include "Customer.hh"

using std::ostringstream;
using std::vector;

std::string Customer::statement()
{
  double totalAmount = 0;
  int frequentRenterPoints = 0;
  std::vector< Rental >::iterator iter = _rentals.begin();
  std::vector< Rental >::iterator iter_end = _rentals.end();
  std::ostringstream result;
  result << "Rental Record for " << getName() << "\n";
  for ( ; iter != iter_end; ++iter ) {
    double thisAmount = 0;
    Rental each = *iter;

    // determine amounts for each line
    switch ( each.getMovie().getPriceCode() ) {
      case Movie::REGULAR:
        thisAmount += 2;
        if ( each.getDaysRented() > 2 )
          thisAmount += ( each.getDaysRented() - 2 ) * 1.5 ;
        break;
      case Movie::NEW_RELEASE:
        thisAmount += each.getDaysRented() * 3;
        break;
      case Movie::CHILDRENS:
        thisAmount += 1.5;
        if ( each.getDaysRented() > 3 )
          thisAmount += ( each.getDaysRented() - 3 ) * 1.5;
        break;
    }

    // add frequent renter points
    frequentRenterPoints++;
    // add bonus for a two day new release rental
    if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
         && each.getDaysRented() > 1 ) frequentRenterPoints++;

    // show figures for this rental
    result << "\t" << each.getMovie().getTitle() << "\t"
           << thisAmount << "\n";
    totalAmount += thisAmount;
  }
  // add footer lines
  result << "Amount owed is " << totalAmount << "\n";
  result << "You earned " << frequentRenterPoints
         << " frequent renter points";
  return result.str();
}

std::string Customer::htmlstatement()
{
  double totalAmount = 0;
  int frequentRenterPoints = 0;
  std::vector< Rental >::iterator iter = _rentals.begin();
  std::vector< Rental >::iterator iter_end = _rentals.end();
  std::ostringstream result;

  // Start JSON object
  result << "{\n";
  result << "  \"customer\": \"" << getName() << "\",\n";
  result << "  \"rentals\": [\n";

  bool first = true;
  for ( ; iter != iter_end; ++iter ) {
    double thisAmount = 0;
    Rental each = *iter;

    // determine amounts for each line (DUPLICATED LOGIC!)
    switch ( each.getMovie().getPriceCode() ) {
      case Movie::REGULAR:
        thisAmount += 2;
        if ( each.getDaysRented() > 2 )
          thisAmount += ( each.getDaysRented() - 2 ) * 1.5 ;
        break;
      case Movie::NEW_RELEASE:
        thisAmount += each.getDaysRented() * 3;
        break;
      case Movie::CHILDRENS:
        thisAmount += 1.5;
        if ( each.getDaysRented() > 3 )
          thisAmount += ( each.getDaysRented() - 3 ) * 1.5;
        break;
    }

    // add frequent renter points (DUPLICATED LOGIC!)
    frequentRenterPoints++;
    // add bonus for a two day new release rental
    if ( ( each.getMovie().getPriceCode() == Movie::NEW_RELEASE )
         && each.getDaysRented() > 1 ) frequentRenterPoints++;

    // add comma separator for all but first rental
    if (!first) {
      result << ",\n";
    }
    first = false;

    // output rental as JSON object
    result << "    {\n";
    result << "      \"title\": \"" << each.getMovie().getTitle() << "\",\n";
    result << "      \"amount\": " << thisAmount << "\n";
    result << "    }";

    totalAmount += thisAmount;
  }

  // Close rentals array
  result << "\n  ],\n";

  // Add summary fields
  result << "  \"totalAmount\": " << totalAmount << ",\n";
  result << "  \"frequentRenterPoints\": " << frequentRenterPoints << "\n";

  // Close JSON object
  result << "}";

  return result.str();
}
