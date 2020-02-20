#include<unistd.h>
#include "processor.h"



// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  totalJiffiesStart_ = LinuxParser::Jiffies();
  activeJiffiesStart_ = LinuxParser::ActiveJiffies();
  
  usleep(100000);
  
  totalJiffiesEnd_ = LinuxParser::Jiffies();
  activeJiffiesEnd_ = LinuxParser::ActiveJiffies();
  
  long totalDelta = totalJiffiesEnd_ - totalJiffiesStart_;
  long activeDelta = activeJiffiesEnd_ - activeJiffiesStart_;
  
  if(totalDelta == 0){
  	return 0.0;
  }
  return float(activeDelta)/ float(totalDelta); }