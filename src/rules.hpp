#ifndef RULES_HPP
#define RULES_HPP

/* rules.hpp serve per gestire le regole che esistono nel gioco, e verificando
che queste esistano, alcune azioni saranno possibili. Saranno oggetti vettori di
tre elementi ciascuno: NOUN_TYPE, VERB_TYPE, PROPERTY_TYPE.
*/
#include <array>
#include <optional>

#include "enum_objects.hpp"
#include "objects.hpp"

namespace Baba_Is_Us {

class Rule {
 private:
  std::array<Type, 3> m_rule;

 public:
  Rule() = delete;  // non si può creare una regola vuota
  constexpr Rule(const Type type1, const Type type2, const Type type3)
      : m_rule{type1, type2,
               type3} {  // ogni regola deve avere un noun, verb e property/noun

    assert(((+type1 > +Type::NOUN_TYPE && +type1 < +Type::ICON_NOUN_TYPE &&
             +type2 > +Type::VERB_TYPE && +type2 < +Type::PROPERTY_TYPE &&
             +type3 > +Type::PROPERTY_TYPE) ||
            (+type3 > +Type::NOUN_TYPE && +type3 < +Type::ICON_NOUN_TYPE)) &&
           "Rule constructor condition not satisfied");
  }

  friend class RuleManager;
  constexpr friend bool operator==(const Rule &rhs, const Rule &lhs);
  constexpr bool hasType(const Type type) const;
  constexpr const std::array<Type, 3> &getm_rule() const;
};

constexpr bool operator==(const Rule &rhs, const Rule &lhs) {
  return rhs.m_rule == lhs.m_rule;
}

constexpr bool Rule::hasType(const Type type) const {
  if (m_rule[0] == type || m_rule[1] == type || m_rule[2] == type) return true;
  return false;
}

constexpr const std::array<Type, 3> &Rule::getm_rule() const { return m_rule; }

class RuleManager {
 private:
  std::vector<Rule> m_rules{};

 public:
  bool block_moved{false};
  constexpr void addRule(const Rule &rule) { m_rules.emplace_back(rule); }
  constexpr void removeRule(const Rule &rule);
  const std::vector<Rule> &getm_rules() const;
  constexpr void clearRules() { m_rules.clear(); }
  const std::optional<Type> findPlayerType() const;
};

constexpr void RuleManager::removeRule(const Rule &rule) {
  const auto &iter{std::find(m_rules.begin(), m_rules.end(), rule)};
  if (iter != m_rules.end()) {
    m_rules.erase(iter);
  }
}

PlayState conditions(Objects &, Objects &);

}  // namespace Baba_Is_Us

#endif