#ifndef storage_h
#define storage_h

#include "Handler.h"
#include <map>
#include <mutex>

class Storage {
  using buffer = std::string;
  using id = int;
  using element = std::pair<std::shared_ptr<Handler>,buffer>;
  
  id count = 0;  

  Storage(Storage&) = delete;
  Storage& operator=(Storage&) = delete;

protected:
  Storage() = default;
  std::map<id,element> data;

public:
  static Storage& Instance();  
  const id& addHandler(const int&);
  element& getHandler(const id&);
  void removeHandler(const id&);
};

#endif