/* objects.hpp serve per controllare ogni oggetto, a cui sarà applicata una regola in altri file. 
Ogni m_object sarà inizializzato e disegnato in 

*/

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
    


    public :
    constexpr Objects() = default; //per le celle vuote
    Objects(std::vector<Type> object_vect) : m_object{object_vect} {}
    const std::optional<std::vector<Type>> getTypes(); //se il vettore m_object è vuoto, std::optional è convertibile in false
    constexpr void addVerb(const Type verb);
    constexpr void addProperty(const Type property);
    bool operator==(const Objects& m_object) const;
    bool hasNOUN_TYPE(Type type);
    bool hasICON_NOUN_TYPE(Type type);
    bool hasVERB_TYPE(Type type);
    bool hasPROPERTY_TYPE(Type type);
};
} //namespace Baba_Is_Us
