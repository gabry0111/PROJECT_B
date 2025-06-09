/* objects.hpp serve per controllare ogni oggetto, a cui sarà applicata una regola in altri file. 
Ogni m_object sarà inizializzato e disegnato in 

*/
#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "enum_objects.hpp"
#include <vector>
#include <optional> //forse da togliere
#include <iostream> //da togliere
#include <cassert>
#include <algorithm>


namespace Baba_Is_Us { //sarà il namespace di ogni file di questo progetto 

    
class Objects {
    private :
    std::vector<Type> m_object {}; //sarà del tipo: NOUN_TYPE e tanti PROPERTY_TYPE
        
/* 
Problema: assicurarsi che "noun" (parametro del costruttore) sia valida per stampare l'oggetto a schermo 
(non sia un aggettivo/proprietà). Creiamo una funzione per assicurarsi al compile time (il corpo del 
costruttore avviene al runtime) che l'oggetto sia valido per essere stampato a schermo (non sia aggettivo o verbo)
*/
    


    public :
    Objects() = default; //per le celle vuote
    Objects(std::vector<Type> object_vect) : m_object{object_vect} {}

    // potrà essere usato, una volta identificato quale oggetto ha un certo tipo con un'altra funzione,
    // per ottenere il NOUN_TYPE di chi ha quel tipo
    std::vector<Type> getTypes() const; // può diventare constexpr
    constexpr bool operator==(const Objects& object) const;
    bool objectHasType(const Type type) const; // può forse diventare constexpr (solo al runtime a meno di controllare, prima di chiamare la funzione, che il tipo sia valido) 
    void add(const Type word); // può diventare constexpr (solo al runtime)
    void remove(Type type); // come objectHasType()

};
} //namespace Baba_Is_Us

#endif