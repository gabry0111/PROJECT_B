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
#include "map.hpp"
#include <tuple>
#include <cassert>
#include <array>

namespace Baba_Is_Us {

// idea: creare una singola istanza di una regola
class Rule{
private : 
    std::array<Type,3> m_rule; // vedere differenza tra tuple e array
public : 
    Rule() = delete; // non si può creare una regola vuota
    Rule(Type type1, Type type2, Type type3) : m_rule{type1, type2, type3} { // ogni regola deve avere un noun, verb e property/noun 

        assert((
            (
                +type1 > +Type::NOUN_TYPE &&
                +type1 < +Type::ICON_NOUN_TYPE &&
                +type2 > +Type::VERB_TYPE &&
                +type2 < +Type::PROPERTY_TYPE &&
                +type3 > +Type::PROPERTY_TYPE
            )
             || 
            (
                +type3 > +Type::NOUN_TYPE &&
                +type3 < +Type::ICON_NOUN_TYPE
            )
        ) && "Rule constructor condition not satisfied");   
    }

    friend class RuleManager;
    friend bool operator==(const Rule& rhs, const Rule& lhs); // per algoritmi tipo find(), può forse diventare constexpr (dipende da std::tuple)
    bool hasType(Type type) const; // può diventare constexpr (dipende da objectHasType())
    const std::array<Type, 3>& getm_rule() const;
};

// idea: un singolo oggetto che gestisce tutte le regole
class RuleManager{
private :
    std::vector<Rule> m_rules {};

public :
    bool block_moved {false};
    RuleManager() = default;
    void addRule(const Rule& rule); // può forse diventare constexpr (dipende da std::tuple)
    void removeRule(const Rule& rule); // come addRule()
    const std::vector<Rule>& getm_rules();
    void clearRules(); // forse non serve
    // dato un'insieme di regole, servirà per avere un vettore con le tuple che hanno la regola type in modo da confrontare se un'azione è possibile.
    //N.B: se m_rules cambia, diventano dangling references
    constexpr std::vector<Rule> getWhichRuleHasType(Type type) const;
    // std::size_t GetNumRules() const; è inutile. guarda dove viene usato...
    std::optional<Type> findPlayerType() const; // può diventare constexpr (dipende da objectHasType())
};
}

#endif