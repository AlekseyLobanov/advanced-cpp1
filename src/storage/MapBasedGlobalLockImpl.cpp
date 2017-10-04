#include "MapBasedGlobalLockImpl.h"

#include <mutex>

namespace Afina {
namespace Backend {

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Put(const std::string &key, const std::string &value) {
    std::unique_lock<std::mutex> guard(_lock);

    if ( find(_to_remove.begin(), _to_remove.end(), key) != _to_remove.end() )
		_to_remove.push_back(key);
	if ( _to_remove.size() > _max_size ) {
		Delete(_to_remove.front());
	}

    _backend[key] = value;
    return true;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::PutIfAbsent(const std::string &key, const std::string &value) {
    std::unique_lock<std::mutex> guard(_lock);
    if ( _backend.find(key) == _backend.end() )
		return Put(key, value);
	return false;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Set(const std::string &key, const std::string &value) {
    std::unique_lock<std::mutex> guard(_lock);
    if ( _backend.find(key) != _backend.end() )
		return Put(key, value);
    return Put(key, value);
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Delete(const std::string &key) {
    std::unique_lock<std::mutex> guard(_lock);
    auto pos = _backend.find(key);
    if ( pos != _backend.end() )
		_backend.erase(key);
	auto to_remove_pos = find(_to_remove.begin(), _to_remove.end(), key);
	if ( to_remove_pos != _to_remove.end() )
		_to_remove.erase(to_remove_pos);
    return true;
}

// See MapBasedGlobalLockImpl.h
bool MapBasedGlobalLockImpl::Get(const std::string &key, std::string &value) const {
    std::unique_lock<std::mutex> guard(*const_cast<std::mutex *>(&_lock));
    value = _backend.at(key);
    return true;
}

} // namespace Backend
} // namespace Afina
