#include "async.h"
#include "Storage.h"
#include <iostream>

namespace async {

handle_t connect(std::size_t bulk) {
    return static_cast<void*>(const_cast<int*>(&Storage::Instance().addHandler(bulk)));
}

void receive(handle_t handle, const char *data, std::size_t size) {
}

void disconnect(handle_t handle) {
    if (!handle) throw(std::runtime_error("handle is nullptr"));
    Storage::Instance().removeHandler(*static_cast<int*>(handle));
}

}
