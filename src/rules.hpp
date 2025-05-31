/* rules.hpp serve per gestire le regole che esistono nel gioco, e verificando che queste esistano,
alcune azioni saranno possibili.
Saranno oggetti vettori di tre elementi ciascuno: NOUN_TYPE, VERB_TYPE, PROPERTY_TYPE.


- controlla se esiste oggetto con 'You' (per enum PlayState)
- un metodo per controllare se un vettore regola è uguale a un vetttore m_object

*/
#ifndef RULES_HPP
#define RULES_HPP

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
        static_assert(+obj1 > +Type::NOUN_TYPE && +obj1 < +Type::ICON_NOUN_TYPE &&
               +obj2 > +Type::VERB_TYPE && +obj2 < +Type::PROPERTY_TYPE &&
               +obj3 > +Type::PROPERTY_TYPE ||  +obj3 > +Type::NOUN_TYPE && +obj3 < +Type::ICON_NOUN_TYPE && "Rule constructor condition not satisfied");
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
    constexpr std::vector<std::reference_wrapper<const Rule>> getWhichRuleHasType(Type type) const;
    // std::size_t GetNumRules() const; è inutile. guarda dove viene usato...
    Type findPlayer() const; // determina quale oggetto si può muovere
    bool objectHasProperty(const Objects& object, Type property); // controlla se un oggetto ha una proprietà
};
}

#endif