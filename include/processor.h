#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"


class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 float totalJiffiesStart_{0.0}, activeJiffiesStart_{0.0}, totalJiffiesEnd_{0.0}, activeJiffiesEnd_{0.0};
};

#endif