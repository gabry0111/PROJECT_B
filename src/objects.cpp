#include "enum_objects.hpp"
#include <vector>
#include <optional> //forse da togliere
#include <iostream> //da togliere
#include <cassert>
#include <algorithm>


namespace Baba_Is_Us { //sarà il namespace di ogni file di questo progetto 

    
class Objects {
    private :
    std::optional<std::vector<Type>> m_object {}; //o std::tuple of heterogeneus types
        
/* 
Problema: assicurarsi che "noun" (parametro del costruttore) sia valida per stampare l'oggetto a schermo 
(non sia un aggettivo/proprietà). Creiamo una funzione per assicurarsi al compile time (il corpo del 
costruttore avviene al runtime) che l'oggetto sia valido per essere stampato a schermo (non sia aggettivo o verbo)
*/
    
    constexpr Objects() = default; //per le celle vuote
    Objects(std::optional<std::vector<Type>> object_vect) : m_object(object_vect) {};

    public :
    const std::optional<std::vector<Type>> getTypes();
    friend Objects createObject (const std::optional<std::vector<Type>>&);
    constexpr void addVerb(const Type verb);
    constexpr void addProperty(const Type property);
};


bool hasNOUN_TYPE(const std::optional<std::vector<Type>>& words) {
    if(words){for (const auto& eee : *words) {
        if (+eee > +Type::NOUN_TYPE && +eee < +Type::ICON_NOUN_TYPE) return true;
    }}
    return false;
}
bool hasICON_NOUN_TYPE(const std::optional<std::vector<Type>>& words) {
    if(words){for (const auto& eee : *words) {
        if (+eee > +Type::ICON_NOUN_TYPE && +eee < +Type::VERB_TYPE) return true;
    }}
    return false;
}
bool hasVERB_TYPE(const std::vector<Type>& words) {
    for (auto eee : words) {
        if (+eee > +Type::VERB_TYPE && +eee < +Type::PROPERTY_TYPE) return true;
    }
    return false;
}
bool hasPROPERTY_TYPE(const std::vector<Type>& words) {
    for (auto eee : words) {
        if (+eee > +Type::PROPERTY_TYPE) return true;
    }
    return false;
}
const std::optional<std::vector<Type>> Objects::getTypes() {
    std::vector<Type> ret{};
    for (const auto& type : *m_object)
    {
        ret.emplace_back(type);
    }
    return ret;
}

//implicitamente convertibile in falso se non contiene un valore; altrimenti inizializza un'istanza
 Objects createObject(const std::optional<std::vector<Type>>& noun) { 
    assert(hasNOUN_TYPE(noun) && "createObject not given a NOUN_TYPE");
    if(hasNOUN_TYPE(noun)) return Objects(noun);
    return {};
};  
/*
constexpr std::optional<Type> Objects::createObject(const std::vector<Type>& object_vect) {
    assert(+noun <= +Type::Wall && +noun > +Type::NOUN_TYPE && "CreatePrintableObject not given a NOUN_TYPE");
    if(+noun <= +Type::Wall && +noun > +Type::NOUN_TYPE) return noun;
    return nullptr;
}
*/


/*
template<Type verb>
constexpr void Objects::addVerb() {
    static_assert((+verb) <= +Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE && "addVerb not given a VERB_TYPE");
}
*/

constexpr void Objects::addVerb(const Type verb ) {
    assert(+verb <= +Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE && "addVerb not given a VERB_TYPE");
    if(+verb <= +Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE) (*m_object).emplace_back(verb);
}

constexpr void Objects::addProperty(const Type property) {
    assert(+property > +Type::PROPERTY_TYPE && "addProperty not given a PROPERTY_TYPE");
    if(+property <= +Type::PROPERTY_TYPE && +property > +Type::VERB_TYPE) (*m_object).emplace_back(property);
}
} //namespace Baba_Is_Us

using namespace Baba_Is_Us;
int main() {
    std::vector<Type> words{Type::Baba, Type::Is, Type::You};
    Objects baba {createObject(words)};
    baba.getTypes().has_value() ? std::cerr << +(baba.getTypes())->at(0) << " Riuscito \n": std::cerr << "baba non ha NOUN_TYPE \n";
    Type type{toType(+(baba.getTypes()->at(0)))};
    assert(type == Type::Baba && "Sbagliato");
    return 0;
}