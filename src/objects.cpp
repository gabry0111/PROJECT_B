#include "enum_objects.hpp"
#include "objects.hpp"
#include <vector>
#include <optional> //forse da togliere
#include <iostream> //da togliere
#include <cassert>
#include <algorithm>


namespace Baba_Is_Us { //sarà il namespace di ogni file di questo progetto 

bool Objects::operator==(const Objects& obj) const {
    return (m_object == obj.m_object);
}

bool Objects::hasNOUN_TYPE(Type word) {
    return (+word > +Type::NOUN_TYPE && +word < +Type::ICON_NOUN_TYPE);
}
bool Objects::hasICON_NOUN_TYPE(Type word) {
    return (+word > +Type::ICON_NOUN_TYPE && +word < +Type::VERB_TYPE);
}
bool Objects::hasVERB_TYPE(Type word) {
    return (+word > +Type::VERB_TYPE && +word < +Type::PROPERTY_TYPE);
}
bool Objects::hasPROPERTY_TYPE(Type word) {
    return (+word > +Type::PROPERTY_TYPE);
}
bool Objects::objectHasType(Type type) const{
    return std::find(m_object.begin(), m_object.end(), type) != m_object.end();
}

const std::vector<Type> Objects::getTypes() const{
    std::vector<Type> types{};
    for (const auto& type : m_object)
    {
        types.emplace_back(type);
    }
    return types;
}

//implicitamente convertibile in falso se non contiene un valore; altrimenti inizializza un'istanza
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
    if(+verb <= +Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE) (m_object).emplace_back(verb);
}

constexpr void Objects::addProperty(const Type property) {
    assert(+property > +Type::PROPERTY_TYPE && "addProperty not given a PROPERTY_TYPE");
    if(+property <= +Type::PROPERTY_TYPE && +property > +Type::VERB_TYPE) (m_object).emplace_back(property);
}
} //namespace Baba_Is_Us
/*
using namespace Baba_Is_Us;
int main() {
    std::vector<Type> words{Type::Baba, Type::Is, Type::You};
    Objects baba {createObject(words)};
    baba.getTypes().has_value() ? std::cerr << +(baba.getTypes())->at(0) << " Riuscito \n": std::cerr << "baba non ha NOUN_TYPE \n";
    Type type{toType(+(baba.getTypes()->at(0)))};
    assert(type == Type::Baba && "Sbagliato");
    return 0;
}
*/