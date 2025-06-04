/* rules.hpp serve per gestire le regole che esistono nel gioco, e verificando che queste esistano,
alcune azioni saranno possibili.
Saranno oggetti vettori di tre elementi ciascuno: NOUN_TYPE, VERB_TYPE, PROPERTY_TYPE.


- controlla se esiste oggetto con 'You' (per enum PlayState)
- un metodo per controllare se un vettore regola è uguale a un vetttore m_object

*/
#ifndef RULES_HPP
#define RULES_HPP
#include "enum_objects.hpp"
#include "objects.hpp"
#include <tuple>
#include <cassert>

namespace Baba_Is_Us {

// idea: creare una singola istanza di una regola
class Rule{
private : 
    std::tuple<Objects, Objects, Objects> m_rule; // vedere differenza tra tuple e array
public : 
    Rule() = delete; // non si può creare una regola vuota
    Rule(Objects obj1, Objects obj2, Objects obj3) : m_rule{obj1, obj2, obj3} { // ogni regola deve avere un noun, verb e property/noun 
        assert((+obj1.getTypes()[0] > +Type::NOUN_TYPE && +obj1.getTypes()[0] < +Type::ICON_NOUN_TYPE &&
               +obj2.getTypes()[0] > +Type::VERB_TYPE && +obj2.getTypes()[0] < +Type::PROPERTY_TYPE &&
               +obj3.getTypes()[0] > +Type::PROPERTY_TYPE) ||  (+obj3.getTypes()[0] > +Type::NOUN_TYPE && +obj3.getTypes()[0] < +Type::ICON_NOUN_TYPE) && "Rule constructor condition not satisfied");
    };
    std::tuple<Objects, Objects, Objects> get_tuple(Rule& rule) const;
    friend class RuleManager;
    bool hasType(Type type) const;
};

// idea: un singolo oggetto che gestisce tutte le regole
class RuleManager{
private :
    std::vector<Rule> m_rules;

public :
    void addRule(const Rule& rule);
    void removeRule(const Rule& rule);
    void clearRules();
    // dato un'insieme di regole, servirà per avere un vettore con le tuple che hanno la regola type in modo da confrontare se un'azione è possibile.
    //N.B: se m_rules cambia, diventano dangling references
    const std::vector<std::reference_wrapper<const Rule>> getWhichRuleHasType(Type type) const;
    // std::size_t GetNumRules() const; è inutile. guarda dove viene usato...
    Type findPlayer() const; // determina quale oggetto si può muovere
    bool objectHasProperty(const Objects& object, Type property); // controlla se un oggetto ha una proprietà
    // controlla le interazioni possibili tra un object e un altro object e dice se un'azione può essere fatta.
    // Per certe azioni che cambiano qualcosa dell'oggetto, si può vedere cosa è cambiato nell'ultimo Type del vector<Type> dell'oggetto
    // N.B: questa funzione NON si occupa di verificare la posizione nella mappa di niente. 
    // Se un oggetto ha più tipi, allora fare un ciclo che chiama conditions() per decidere se l'azione è legale.
    //la chiamata a questa funzione sarà del tipo: 
    /* for()
    */
    bool conditions( Objects& object, const Type second) const; // restituisce vero se è andata a buon fine
};
}

#endif