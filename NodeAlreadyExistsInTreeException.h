#ifndef NODE_ALREADY_EXISTS_IN_TREE_EXCEPTION_H
#define NODE_ALREADY_EXISTS_IN_TREE_EXCEPTION_H

#include "RunTimeException.h"
#include <iostream>

class NodeAlreadyExistsInTreeException:public RunTimeException {

public:
  NodeAlreadyExistsInTreeException();
  NodeAlreadyExistsInTreeException(std::string customErrorMessage);
  ~NodeAlreadyExistsInTreeException();

};

#endif
