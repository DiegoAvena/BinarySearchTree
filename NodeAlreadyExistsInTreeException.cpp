#include "NodeAlreadyExistsInTreeException.h"
using namespace std;

NodeAlreadyExistsInTreeException::NodeAlreadyExistsInTreeException():RunTimeException() {}

NodeAlreadyExistsInTreeException::NodeAlreadyExistsInTreeException(string customErrorMessage):RunTimeException(customErrorMessage){}

NodeAlreadyExistsInTreeException::~NodeAlreadyExistsInTreeException(){

}
