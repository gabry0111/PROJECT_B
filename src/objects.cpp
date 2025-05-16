#include "enum_objects.hpp"
#include <vector>
#include <optional>
#include <iostream> //da togliere
#include <cassert>


namespace Baba_Is_Us { //sarà il namespace di ogni file di questo progetto 
    
class Object {
    private :
    std::vector<Type> m_object {}; //o std::tuple of heterogeneus types
        
/* 
Problema: assicurarsi che "noun" (parametro del costruttore) sia valida per stampare l'oggetto a schermo 
(non sia un aggettivo/proprietà). Creiamo una funzione friend per assicurarsi al compile time (il corpo del 
costruttore avviene al runtime) che l'oggetto sia valido per essere stampato a schermo
*/
    Object() = default;
    Object(std::vector<Type> object_vect) : m_object{object_vect} {};
    public :
    friend constexpr std::optional<Type> createObject ();
    constexpr void addVerb(const Type& verb);
    void addProperty();
};

//con static_assert è incredibilmente più complesso: NON EDITARE MAIIIIIIIIIIIAWJDNFL SBDAIUL SEFLB s
template<Type t>
constexpr std::optional<Type> createObject() { //implicitamente convertibile in falso se non contiene un valore
    static_assert(+t <= +Type::Wall && +t > +Type::NOUN_TYPE);
    return t;
}
/*
constexpr auto createObject {
    [] (const std::vector<Type>& noun) {
        static_assert(+noun <= +Type::Wall && +noun > +Type::NOUN_TYPE && "CreatePrintableObject not given a NOUN_TYPE");
        return noun;
    return ;
    }
}


constexpr void addVerb(Type verb) {
    static_assert((+verb) <= + Type::PROPERTY_TYPE && +verb > +Type::VERB_TYPE && "addVerb not given a VERB_TYPE");

}
*/
} //namespace Baba

int main() {
    constexpr auto baba =
    Baba_Is_Us::createObject<Baba_Is_Us::Type::Baba>();
    std::cerr << +(*baba) << " Riuscito \n";
    return 0;
    }


