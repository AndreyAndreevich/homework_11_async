#include "Storage.h"
#include "Handler.h"

Storage& Storage::Instance() {
  static Storage instance;
  return instance;
}

const Storage::id& Storage::addHandler(const int& N) {
  count++;
  auto it = data.emplace_hint(data.end(),count,element(std::make_shared<Handler>(N),std::string{}));
  return it->first;
}

Storage::element& Storage::getHandler(const id& id_) {
  return data.at(id_);
}

void Storage::removeHandler(const id& id_) {
  data.erase(id_);
}