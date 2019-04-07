#ifndef TREE_EMPTY_EXCEPTION_H
#define TREE_EMPTY_EXCEPTION_H

#include "RunTimeException.h"
#include <iostream>

class TreeEmptyException: public RunTimeException {

public:
  TreeEmptyException();
  TreeEmptyException(std::string customErrorMessage);
  ~TreeEmptyException();

};

#endif
