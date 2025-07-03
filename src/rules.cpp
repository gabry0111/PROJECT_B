#include "rules.hpp"
#include "enum_objects.hpp"
#include "objects.hpp"
#include <algorithm>
#include <functional>

namespace Baba_Is_Us {

bool operator==(const Rule &rhs, const Rule &lhs) {
  return rhs.m_rule == lhs.m_rule;
}

bool Rule::hasType(Type type) const {
  if (m_rule[0] == type || m_rule[1] == type || m_rule[2] == type)
    return true;
  return false;
}

const std::array<Type, 3> &Rule::getm_rule() const { return m_rule; }

void RuleManager::addRule(const Rule &rule) { m_rules.emplace_back(rule); }

void RuleManager::removeRule(const Rule &rule) { 
  auto iter{std::find(m_rules.begin(), m_rules.end(), rule)};
  if (iter != m_rules.end()) {
    m_rules.erase(iter);
  }
}

const std::vector<Rule> &RuleManager::getm_rules() const { return m_rules; }
std::vector<Rule> &RuleManager::accessm_rules() { return m_rules; }

void RuleManager::clearRules() {
  m_rules.clear();
  assert(m_rules.size() == 0);
}

std::optional<Type> RuleManager::findPlayerType() const {
  for (const auto &each_rule : m_rules) {
    if (each_rule.m_rule[2] == Type::You) {

      Type type_Player{each_rule.m_rule[0]};
      return type_Player;
    }
  }
  return std::nullopt;
}

} // namespace Baba_Is_Us