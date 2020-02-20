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
  Process(int,long);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_{0};
  int Hz_;
  float total_time_{0.0}, seconds_{0.0};
  // float utime_ = 0.0;
  // float stime_ = 0.0;
  // float cutime_ = 0.0;
  // float cstime_ = 0.0;
  // float starttime_ = 0.0;
//   string user_{};
//   string cmd_{};
//   string ram_{};
int cpu_util_;
//  
  
};

#endif