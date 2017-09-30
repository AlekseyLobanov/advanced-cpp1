#include <afina/allocator/Pointer.h>

namespace Afina {
namespace Allocator {

std::set<Pointer*> Pointer::_pointers;

Pointer::~Pointer() {
	Pointer::_pointers.erase(this);
}

} // namespace Allocator
} // namespace Afina
