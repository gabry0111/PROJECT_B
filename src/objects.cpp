#include "enum_objects.hpp"
#include <vector>
#include <optional> //forse da togliere
#include <iostream> //da togliere
#include <cassert>
#include <algorithm>


namespace Baba_Is_Us { //sarà il namespace di ogni file di questo progetto 

    
class Objects {
    private :
    std::vector<Type> m_object {}; //o std::tuple of heterogeneus types
        
/* 
Problema: assicurarsi che "noun" (parametro del costruttore) sia valida per stampare l'oggetto a schermo 
(non sia un aggettivo/proprietà). Creiamo una funzione per assicurarsi al compile time (il corpo del 
costruttore avviene al runtime) che l'oggetto sia valido per essere stampato a schermo (non sia aggettivo o verbo)
*/
    
    constexpr Objects() = default; //per le celle vuote
    Objects(std::vector<Type> object_vect) : m_object{object_vect} {};

    public :
    const friend std::optional<Objects> createObject (const std::vector<Type>&);
    const bool getTypes(const std::vector<Type>&, Type first, Type last);
    constexpr void addVerb(const Type verb);
    constexpr void Objects::addProperty(const Type property);
};


const bool hasNOUN_TYPE(const std::vector<Type>& words) {
    for (auto eee : words) {
        if (+eee > +Type::NOUN_TYPE && +eee < +Type::VERB_TYPE) return true;
    }
    return false;
}
const bool hasVERB_TYPE(const std::vector<Type>& words) {
    for (auto eee : words) {
        if (+eee > +Type::VERB_TYPE && +eee < +Type::PROPERTY_TYPE) return true;
    }
    return false;
}
const bool hasPROPERTY_TYPE(const std::vector<Type>& words) {
    for (auto eee : words) {
        if (+eee > +Type::PROPERTY_TYPE) return true;
    }
    return false;
}
/*
Idee:
1) cercare di andare avanti col compile-time (chiederea chatgpt)

*/

//implicitamente convertibile in falso se non contiene un valore; altrimenti inizializza un'istanza
const std::optional<Objects> createObject(const std::vector<Type>& noun) { 
    assert(hasNOUN_TYPE(noun) && "createObject not given a NOUN_TYPE");
    if(+noun <= +Type::VERB_TYPE && +noun > +Type::NOUN_TYPE) return Objects{noun};
    return {};
};  
/*
constexpr std::optional<Type> Objects::createObject(const std::vector<Type>& object_vect) {
    assert(+noun <= +Type::Wall && +noun > +Type::NOUN_TYPE && "CreatePrintableObject not given a NOUN_TYPE");
    if(+noun <= +Type::Wall && +noun > +Type::NOUN_TYPE) return noun;
    return nullptr;
}
*/

const bool Objects::getTypes(const std::vector<Type>&, Type first, Type last) {}

/*
template<Type verb>
constexpr void Objects::addVerb() {
    static_assert((+verb) <= +Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE && "addVerb not given a VERB_TYPE");
}
*/

constexpr void Objects::addVerb(const Type verb ) {
    assert(+verb <= +Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE && "addVerb not given a VERB_TYPE");
    if(+verb <= +Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE) m_object.emplace_back(verb);
}

constexpr void Objects::addProperty(const Type property) {
    assert(+property > +Type::PROPERTY_TYPE && "addProperty not given a PROPERTY_TYPE");
    if(+property <= +Type::PROPERTY_TYPE && +property > +Type::VERB_TYPE) m_object.emplace_back(property);
}


int main() {
    std::vector<Type> words{Type::Baba, Type::Is, Type::You};
    auto baba {createObject(words)};
    std::cerr << +(*baba) << " Riuscito \n";
    return 0;
    }

} //namespace Baba_Is_Us