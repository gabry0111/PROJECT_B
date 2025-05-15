#include <EnumObjects.hpp>

namespace Baba { //sarà il namespace di ogni file di questo progetto 
    class Object {
        private :
        Type m_object_type {};
        

        public :
        Object() = default;
        Object(Type t) : m_object_type{t} {};
    };
}
