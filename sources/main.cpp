#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <thread>

struct MemInfo {
  float Active;
  float ActiveAnon;
  float ActiveFile;
  float AnonHugePages;
  float AnonPages;
  float Bounce;
  float Buffers;
  float Cached;
  float CmaFree;
  float CmaTotal;
  float CommitLimit;
  float Committed_AS;
  float DirectMap1G;
  float DirectMap2M;
  float DirectMap4k;
  float Dirty;
  float FileHugePages;
  float FilePmdMapped;
  float HardwareCorrupted;
  float HugePages_Free;
  float HugePages_Rsvd;
  float HugePages_Surp;
  float HugePages_Total;
  float Hugepagesize;
  float Hugetlb;
  float Inactive;
  float InactiveAnon;
  float InactiveFile;
  float KReclaimable;
  float KernelStack;
  float Mapped;
  float MemAvailable;
  float MemFree;
  float MemTotal;
  float Mlocked;
  float NFS_Unstable;
  float PageTables;
  float Percpu;
  float SReclaimable;
  float SUnreclaim;
  float SecPageTables;
  float Shmem;
  float ShmemHugePages;
  float ShmemPmdMapped;
  float Slab;
  float SwapCached;
  float SwapFree;
  float SwapTotal;
  float Unaccepted;
  float Unevictable;
  float VmallocChunk;
  float VmallocTotal;
  float VmallocUsed;
  float Writeback;
  float WritebackTmp;
  float Zswap;
  float Zswapped;
  float Process;
};

struct Iostat {
  unsigned int User;
  unsigned int Nice;
  unsigned int System;
  unsigned int Iowait;
  unsigned int Steal;
  unsigned int Idle;
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
  while (true) {
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
    for (const auto &pair : meminfo) {
      if (pair.first == "MemTotal") {
        meminform.MemTotal = std::stoi(pair.second);
      }
      if (pair.first == "MemFree") {
        meminform.MemFree = std::stoi(pair.second);
      }
      if (pair.first == "Cached") {
        meminform.Cached = std::stoi(pair.second);
      }
    }

    // get memory using but not in cached
    auto memUsed = (meminform.MemTotal - (meminform.MemFree + meminform.Cached)) / 1024 / 1024;
    auto memUsedWithCache = (meminform.MemTotal - meminform.MemFree) / 1024 / 1024;

    printf("| IOWAIT %.2f | MEM %.2f/%.2f/%.2f\n", 1.0, memUsed,  meminform.Cached / 1024 / 1024, memUsedWithCache);

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}
