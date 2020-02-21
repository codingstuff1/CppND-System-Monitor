#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <linux_parser.h>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid(); 
  long Hz();                                // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_{0};
  long hz_{0};
  float total_time_{0.0}, seconds_{0.0};
  // float utime_ = 0.0;
  // float stime_ = 0.0;
  // float cutime_ = 0.0;
  // float cstime_ = 0.0;
  // float starttime_ = 0.0;
  std::string user_{};
  std::string command_{};
  std::string ram_{};
  int cpu_util_;
//  
  
};

#endif