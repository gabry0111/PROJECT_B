#ifndef RULES_HPP
#define RULES_HPP
/* rules.hpp serve per gestire le regole che esistono nel gioco, e verificando
che queste esistano, alcune azioni saranno possibili. Saranno oggetti vettori di
tre elementi ciascuno: NOUN_TYPE, VERB_TYPE, PROPERTY_TYPE.
*/

#include <array>

#include "enum_objects.hpp"
#include "objects.hpp"

namespace Baba_Is_Us {

class Rule {
 private:
  std::array<Type, 3> m_rule;

 public:
  Rule() = delete;  // non si può creare una regola vuota
  constexpr Rule(Type type1, Type type2, Type type3)
      : m_rule{type1, type2,
               type3} {  // ogni regola deve avere un noun, verb e property/noun

    assert(((+type1 > +Type::NOUN_TYPE && +type1 < +Type::ICON_NOUN_TYPE &&
             +type2 > +Type::VERB_TYPE && +type2 < +Type::PROPERTY_TYPE &&
             +type3 > +Type::PROPERTY_TYPE) ||
            (+type3 > +Type::NOUN_TYPE && +type3 < +Type::ICON_NOUN_TYPE)) &&
           "Rule constructor condition not satisfied");
  }

  friend class RuleManager;
  friend bool operator==(const Rule &rhs, const Rule &lhs);
  constexpr bool hasType(Type type) const;
  constexpr const std::array<Type, 3> &getm_rule() const { return m_rule; }
};

constexpr bool Rule::hasType(Type type) const {
  if (m_rule[0] == type || m_rule[1] == type || m_rule[2] == type)
    return true;
  return false;
}


class RuleManager {
 private:
  std::vector<Rule> m_rules{};

 public:
  bool block_moved{false};
  constexpr void addRule(const Rule &rule) { m_rules.emplace_back(rule); }
  const std::vector<Rule> &getm_rules() const;
  constexpr void clearRules();
};

constexpr void RuleManager::clearRules() {
  m_rules.clear();
  assert(m_rules.size() == 0);
}

PlayState conditions(Objects &, Objects &);

}  // namespace Baba_Is_Us

#endif