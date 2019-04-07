#ifndef RUN_TIME_EXCEPTION
#define RUN_TIME_EXCEPTION

#include <iostream>

/*

-A generic exception class that can be inherited from to build more focused exception classes

*/
class RunTimeException {

private:
  std::string err; //the message this exception can tell the user when caught

public:
  RunTimeException(); //default constructor
  RunTimeException(std::string customErrorMessage); //overloaded constructor, allows for a more detailed message to be set for this exception
  ~RunTimeException(); //destuctor
  std::string getErrorMessage(); //accessor method for getting the details of this exception

};

#endif
