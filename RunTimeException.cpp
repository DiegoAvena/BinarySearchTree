#include "RunTimeException.h"
using namespace std;

//default constructor, sets the message to a default one:
RunTimeException::RunTimeException() {

  err = "Runtime exception";

}

//overloaded constructor, allows for a more detailed message to be set for this exception
RunTimeException::RunTimeException(string customErrorMessage) {

  err = customErrorMessage;

}

//destuctor
RunTimeException::~RunTimeException() {

}

//accessor method for getting the details of this exception
string RunTimeException::getErrorMessage() {

  return err;

}
