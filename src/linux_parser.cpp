#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stol;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    // istringstream -> it allows us to pull tokens off the 		//stream 
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

//BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

//✔️TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memTotal= 0;
  float memFree = 0;
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream.is_open()){
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "memTotal: "){
         memTotal = stof(value);
      }
      if(key == "memFree: "){
      	memFree = stof(value);
      }  
    }      
  }
    return (memTotal - memFree ) / memTotal;
   }

//TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime_long;
  string uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()){
  std::getline(stream,line);
    //std::istringstream -> Input stream class to operate on strings
  std::istringstream linestream(line);
    linestream >> uptime;
    //stol() -> Convert string to long int
    uptime_long = std::stol(uptime);
  }
  return uptime_long; }

//✔️TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long total = 0;
  vector<string> cpuUtilization = LinuxParser::CpuUtilization();
  for(int i= kUser_; i <= kSteal_; i++){
    total += stol(cpuUtilization[i]);
  }
  return total; }

//✔️TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  long total_jiff;
  vector<string> stat_list;
  string value, line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
  	std::istringstream linestream(line);
    while(linestream >> value){ 
      stat_list.push_back(value);
    }
  }
  long int utime{std::stol(stat_list[13])};
  long int stime{std::stol(stat_list[14])};
  long int cutime{std::stol(stat_list[15])};
  long int cstime{std::stol(stat_list[16])};
  total_jiff = (utime + stime + cutime + cstime);
  return total_jiff;}

// TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies(int pid) { 
//   long idle_jiff;
//   string value, line;
//   std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
//   if(stream.is_open()){
//   	std::getline(stream, line);
//     std::istringstream linestream(line);
//     int i = 0;
//     while(linestream >> value){
//     	if(i >= 16 && i <= 17){
//         	idle_jiff += std::stol(value);
//         }
//       i++;
//     }
//   }
//   return idle_jiff; }

//✔️ TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
	string key;
  	string line;
    vector<string> cpu_stats;
  	std::ifstream stream(kProcDirectory + kStatFilename);
  	if(stream.is_open()){
     std::getline(stream, line);
      std::istringstream linestream(line);
      while(linestream >> key){
      	if(key != "cpu"){
        	cpu_stats.push_back(key);
        }
      }
    }
      return cpu_stats;	 
}

//✔️ TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key;
  int value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
  	while(std::getline(stream, line)){
    	std::istringstream linestream(line);
      	while(linestream >> key >> value){
      	if(key == "processes"){
          return value;}
    	}
  	}
  }
  return 0;
}
//✔️ TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key;
  int value;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
  	while(std::getline(stream, line)){
    	std::istringstream linestream(line);
      	while(linestream >> key >> value){
      	if(key == "procs_running"){
          return value;}
    }
    }

  }
   return 0;
}

//✔️ TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string command;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + 		     kCmdlineFilename);
  if(stream.is_open()){
  	while(std::getline(stream, line)){
    	std::istringstream linestream(line);
      	std::replace(line.begin(), line.end(), ' ', '*');
        while(linestream >> command){
        	std::replace(command.begin(), command.end(), '*', ' ');
          return command;
        }
    }
  }
  return string(); }

//✔️ TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  int vmSize;
  string key, value, kB;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(stream.is_open()){
  while(std::getline(stream, line)){
  	std::istringstream linestream(line);
    	while(linestream >> key >> value >> kB){
        	if(key == "VmSize"){
            	vmSize = std::stoi(value);
              vmSize /= 1024;
              	return std::to_string(vmSize);
            }
        }
  }
  }
  return string(); }

//✔️TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string uid;
  string key, value;
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) +  kStatusFilename);
  if(stream.is_open()){
  	while(std::getline(stream, line)){
    	std::replace(line.begin(), line.end(), ':', ' ');
      	std::istringstream linestream(line);
      	while(linestream >> key >> value) {
        	if(key == "Uid"){
            uid = value;
        
            }
        }
    }
  }
  return uid; }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string user;
  string password, uid;
  string line;
  
  std::ifstream stream(kPasswordPath);
  if(stream.is_open()){
  	while(std::getline(stream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);
      while(linestream >> user >> password >> uid){
      if(uid == LinuxParser::Uid(pid)){
        return user;
      }
     }
    }
  }
  return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
	string line, value;
  long int start_time, uptime;
  vector<string> list;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(stream.is_open()){
  	std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> value){
    	list.push_back(value);
    }
  }
  start_time = std::stol(list[22])/sysconf(_SC_CLK_TCK);
  uptime = (LinuxParser::UpTime() - start_time);  
	return uptime;
  }

  
