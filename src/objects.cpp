#include "enum_objects.hpp"
#include "objects.hpp"
#include <vector>
#include <optional> //forse da togliere
#include <iostream> //da togliere
#include <cassert>
#include <algorithm>


namespace Baba_Is_Us { //sarà il namespace di ogni file di questo progetto 

constexpr bool Objects::operator==(const Objects& obj) const {
    return (m_object == obj.m_object);
}

constexpr bool Objects::objectHasType(const Type type) const{ //DA AGGIUNGERE IF(E QUI ASSERT)
    assert(type != Type::NOUN_TYPE && type != Type::ICON_NOUN_TYPE && type != Type::VERB_TYPE && type != Type::PROPERTY_TYPE && "Objects::objectHasType() not given a valid type");
    if(type != Type::NOUN_TYPE && type != Type::ICON_NOUN_TYPE && type != Type::VERB_TYPE && type != Type::PROPERTY_TYPE) throw std::runtime_error("objectHasType() not given a valid type");
    return std::find(m_object.begin(), m_object.end(), type) != m_object.end();
    
}

std::vector<Type> Objects::getTypes() const{
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

constexpr void Objects::add(const Type word) {

    // Check if the word is valid and not already present
    bool is_valid_type = (word != Type::NOUN_TYPE && word != Type::ICON_NOUN_TYPE &&
                          word != Type::VERB_TYPE && word != Type::PROPERTY_TYPE);

    // Assert if word is invalid or already present
    assert(is_valid_type && "add() not given a valid type");

    // Only add if valid and not already present
    if (is_valid_type && std::find(m_object.begin(), m_object.end(), word) == m_object.end()) {
        m_object.emplace_back(word);  // Add to the vector if not already present
    }
}


constexpr void Objects::remove(const Type type) {
    auto iter {std::find(m_object.begin(), m_object.end(), type)};
    bool bbb{type != Type::NOUN_TYPE && type != Type::ICON_NOUN_TYPE && type != Type::VERB_TYPE && type != Type::PROPERTY_TYPE && 
        iter == m_object.end()};

    assert(bbb && "remove() not given a valid type or type not present");
    if(bbb) m_object.erase(iter);
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
