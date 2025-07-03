/* rules.hpp serve per gestire le regole che esistono nel gioco, e verificando
che queste esistano, alcune azioni saranno possibili. Saranno oggetti vettori di
tre elementi ciascuno: NOUN_TYPE, VERB_TYPE, PROPERTY_TYPE.


- controlla se esiste oggetto con 'You' (per enum PlayState)
- un metodo per controllare se un vettore regola è uguale a un vetttore m_object

*/
#ifndef RULES_HPP
#define RULES_HPP
#include "enum_objects.hpp"
#include "map.hpp"
#include "objects.hpp"
#include <array>
#include <cassert>
#include <tuple>

namespace Baba_Is_Us {

class Rule {
private:
  std::array<Type, 3> m_rule; 
public:
  Rule() = delete; // non si può creare una regola vuota
  Rule(Type type1, Type type2, Type type3)
      : m_rule{type1, type2,
               type3} { // ogni regola deve avere un noun, verb e property/noun

    assert(((+type1 > +Type::NOUN_TYPE && +type1 < +Type::ICON_NOUN_TYPE &&
             +type2 > +Type::VERB_TYPE && +type2 < +Type::PROPERTY_TYPE &&
             +type3 > +Type::PROPERTY_TYPE) ||
            (+type3 > +Type::NOUN_TYPE && +type3 < +Type::ICON_NOUN_TYPE)) &&
           "Rule constructor condition not satisfied");
  }

  friend class RuleManager;
  friend bool operator==(const Rule &rhs, const Rule &lhs); 
  
  bool hasType(
      Type type) const;
  const std::array<Type, 3> &getm_rule() const;
};


class RuleManager {
private:
  std::vector<Rule> m_rules{};

public:
  bool block_moved{false};
  RuleManager() = default;
  void addRule(const Rule &rule); 
  void removeRule(const Rule &rule); 

  const std::vector<Rule> &getm_rules() const;
  std::vector<Rule> &accessm_rules();
  void clearRules(); 

  std::optional<Type> findPlayerType() const; 
};
} // namespace Baba_Is_Us

#endif