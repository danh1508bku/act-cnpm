#include <iostream>
#include <sstream>

#include "Movie.hh"
#include "Rental.hh"
#include "Customer.hh"
//
int main()
{
  // Define the reference test output

  std::string line1("Rental Record for ");
  std::string line2("Snow White and the Seven Dwarfs");
  std::string line3("Gone with the Wind");
  std::string line4("Amount owed is 3.5");
  std::string line5("You earned 2 frequent renter points");

  std::stringstream ss;
  ss << line1 << "\n"
	    << "\t" << line2 << "\t" << 1.5  << "\n"
	    << "\t" << line3 << "\t" << 2 << "\n"
	    << line4 << "\n"
	    << line5;
  std::string reference = ss.str();
  std::cout << "Reference result: " << std::endl 
	    << reference << std::endl << std::endl;
 
  Movie snow("Snow White and the Seven Dwarfs");
  snow.setPriceCode(Movie::CHILDRENS);
  std::cout << snow.getTitle() 
	    << ", Price code = " 
	    << snow.getPriceCode()
	    << std::endl;

  Rental snowRental(snow, 3);

  Movie gone("Gone with the Wind");
  gone.setPriceCode(Movie::REGULAR);
  std::cout << gone.getTitle() 
	    << ", Price code = " 
	    << gone.getPriceCode()
	    << std::endl;

  Rental goneRental(gone, 1);

  Customer customer;
  customer.addRental(snowRental);
  customer.addRental(goneRental);

  std::string receipt = customer.statement();
  std::cout  << std::endl 
	     << "Test result: " << std::endl
	     << receipt << std::endl;

  // Check if the test is passed 
  std::cout << std::endl;
  if (receipt == reference) std::cout << "---- OK ----" << std::endl;
  else  std::cout << "**** FAILED ****" << std::endl;
}
