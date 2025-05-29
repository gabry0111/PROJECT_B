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
    Rule(Objects obj1, Objects obj2, Objects obj3) : m_rule{obj1, obj2, obj3} { // ogni regola deve avere un noun, verb e property/noun 
        static_assert(+obj1 > +Type::NOUN_TYPE && +obj1 < +Type::ICON_NOUN_TYPE &&
               +obj2 > +Type::VERB_TYPE && +obj2 < +Type::PROPERTY_TYPE &&
               +obj3 > +Type::PROPERTY_TYPE ||  +obj3 > +Type::NOUN_TYPE && +obj3 < +Type::ICON_NOUN_TYPE && "Rule constructor condition not satisfied");
    };
    std::tuple<Objects, Objects, Objects> get_tuple(Rule& rule) const;
};

// idea: un singolo oggetto che gestisce tutte le regole
class RuleManager{
private :
    std::vector<Rule> m_rules;

public :
    void addRule(const Rule& rule);
    void removeRule(const Rule& rule);
    void clearRules();
    std::vector<Rule> getWhichRuleHasType(Type type) const;
    std::size_t GetNumRules() const;
    Type FindPlayer() const; // determina quale oggetto si può muovere
    bool HasProperty(const std::vector<Type>& types, Type property);
};
}

#endif