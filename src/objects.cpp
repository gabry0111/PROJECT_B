#include <enum_objects.hpp>
#include <vector>
#include <optional>

namespace Baba { //sarà il namespace di ogni file di questo progetto 
    class Object {
        private :
        std::vector<Type> m_object {};
        
/* 
Problema: assicurarsi che "noun" (vedi costruttore) sia valida per stampare l'oggetto a schermo 
(non sia un aggettivo,...). Creiamo una funzione friend per assicurarsi al compile time (il corpo del 
costruttore avviene al runtime) che l'oggetto sia valido per essere stampato a schermo
*/
        Object() = default;
        Object(Type noun) : m_object{noun} {};
        public :
        friend std::optional<Type> createObject (Type noun);
    };
    
    std::optional<Type> createObject(Type noun) { //implicitamente convertibile in falso se non contiene un valore
        if (+noun <= +Type::Wall)
            return {noun};
        return {};
    }

} //namespace Baba
