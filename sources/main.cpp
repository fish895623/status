#include <fstream>
#include <iostream>
#include <map>

struct MemInfo {
  float   Active;
  float   ActiveAnon;
  float   ActiveFile;
  float   AnonHugePages;
  float   AnonPages;
  float   Bounce;
  float   Buffers;
  float   Cached;
  float   CmaFree;
  float   CmaTotal;
  float   CommitLimit; 
  float   Committed_AS; 
  float   DirectMap1G; 
  float   DirectMap2M;
  float   DirectMap4k;
  float   Dirty; 
  float   FileHugePages; 
  float   FilePmdMapped; 
  float   HardwareCorrupted; 
  float   HugePages_Free; 
  float   HugePages_Rsvd;
  float   HugePages_Surp;
  float   HugePages_Total; 
  float   Hugepagesize; 
  float   Hugetlb; 
  float   Inactive; 
  float   InactiveAnon; 
  float   InactiveFile; 
  float   KReclaimable; 
  float   KernelStack;
  float   Mapped; 
  float   MemAvailable; 
  float   MemFree; 
  float   MemTotal; 
  float   Mlocked; 
  float   NFS_Unstable; 
  float   PageTables; 
  float   Percpu; 
  float   SReclaimable; 
  float   SUnreclaim; 
  float   SecPageTables; 
  float   Shmem; 
  float   ShmemHugePages; 
  float   ShmemPmdMapped; 
  float   Slab; 
  float   SwapCached; 
  float   SwapFree; 
  float   SwapTotal ;
  float   Unaccepted;
  float   Unevictable;
  float   VmallocChunk;
  float   VmallocTotal; 
  float   VmallocUsed;
  float   Writeback; 
  float   WritebackTmp;
  float   Zswap;
  float   Zswapped;
  float   Process;
};

void trim(std::string &s) {
  s.erase(0, s.find_first_not_of(" \t\n"));
  s.erase(s.find_last_not_of(" \t\n") + 1);

  // find and remove the kB suffix
  size_t pos = s.find(" kB");
  if (pos != std::string::npos) {
    s.erase(pos);
  }
}
int main() {
  std::ifstream file("/proc/meminfo");
  if (!file) {
    std::cerr << "Cannot open /proc/meminfo" << std::endl;
    return 1;
  }

  std::map<std::string, std::string> meminfo;
  std::string line;
  while (std::getline(file, line)) {
    std::string key = line.substr(0, line.find(":"));
    std::string value = line.substr(line.find(":") + 1);
    trim(value);
    meminfo[key] = value;
  }

  struct MemInfo meminform;
  for (const auto& pair : meminfo) {
    if (pair.first == "MemTotal") {
      meminform.MemTotal = std::stoi(pair.second);
    }
    if (pair.first == "MemFree") {
      meminform.MemFree = std::stoi(pair.second);
    }

  }
  std::cout <<  meminform.MemFree / meminform.MemTotal << std::endl;

  return 0;
}
