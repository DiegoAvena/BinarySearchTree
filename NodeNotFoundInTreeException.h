#ifndef NODE_NOT_FOUND_IN_TREE_EXCEPTION_H
#define NODE_NOT_FOUND_IN_TREE_EXCEPTION_H

#include <iostream>
#include "RunTimeException.h"

class NodeNotFoundInTreeException: public RunTimeException {

public:
  NodeNotFoundInTreeException();
  NodeNotFoundInTreeException(std::string customErrorMessage);
  ~NodeNotFoundInTreeException();

};

#endif
