#include "TreeEmptyException.h"
using namespace std;

TreeEmptyException::TreeEmptyException():RunTimeException(){}

TreeEmptyException::TreeEmptyException(string customErrorMessage):RunTimeException(customErrorMessage) {}

TreeEmptyException::~TreeEmptyException() {

}
