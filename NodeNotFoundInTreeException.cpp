#include "NodeNotFoundInTreeException.h"
using namespace std;

NodeNotFoundInTreeException::NodeNotFoundInTreeException():RunTimeException() {}

NodeNotFoundInTreeException::NodeNotFoundInTreeException(string customErrorMessage):RunTimeException(customErrorMessage){}

NodeNotFoundInTreeException::~NodeNotFoundInTreeException() {

}
