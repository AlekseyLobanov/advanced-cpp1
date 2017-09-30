#ifndef AFINA_ALLOCATOR_POINTER_H
#define AFINA_ALLOCATOR_POINTER_H

#include <set>

namespace Afina {
namespace Allocator {
// Forward declaration. Do not include real class definition
// to avoid expensive macros calculations and increase compile speed
class Simple;

class Pointer {
public:
	Pointer() : _pos(nullptr) {
        Pointer::_pointers.insert(this);
    }
    
    Pointer(Pointer const& p): _pos(p._pos) {
        Pointer::_pointers.insert(this);
    }

    ~Pointer();

    void *get() const { return _pos; }
    friend Simple;
private:
    void *_pos;
    static std::set<Pointer*> _pointers;
};

} // namespace Allocator
} // namespace Afina

#endif // AFINA_ALLOCATOR_POINTER_H
