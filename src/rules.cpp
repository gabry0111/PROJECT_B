#include "rules.hpp"
#include "objects.hpp"
#include <algorithm>

namespace Baba_Is_Us{
    std::tuple<Objects, Objects, Objects> Rule::get_tuple(Tuple& rule) const{
        return rule;
    }

    void RuleManager::addRule(const Rule& rule){
        m_rules.emplace_back(rule);
    }

    void RuleManager::removeRule(const Rule& rule){
        const auto iter = std::find(m_rules.begin(), m_rules.end(), rule);
        if (iter != m_rules.end()){
            m_rules.erase(iter);
        }
    }
    
    void RuleManager::clearRules(){
        m_rules.clear();
    }
    //servirà per avere un vettore con le tuple che hanno la regola type in modo da confrontare se un'azione è possibile
    std::vector<Rule> RuleManager::getWhichRuleHasType(Type type) const{
        std::vector<Rule> rules_with_rule;

        for (auto& rule : m_rules)
        {
            if (std::get<0>(rule.rule).HasType(type) ||
                std::get<1>(rule).HasType(type) ||
                std::get<2>(rule).HasType(type))
            {
                rules_with_rule.emplace_back(rule);
            }
        }

        return ret;
    }
    
    std::size_t RuleManager::GetNumRules() const{

    }
    
    Type RuleManager::FindPlayer() const{

    }
    
    bool RuleManager::HasProperty(const std::vector<Type>& types, Type property){

    }
}