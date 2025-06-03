#include "rules.hpp"
#include "objects.hpp"
#include <algorithm>
#include <functional>

namespace Baba_Is_Us{

    bool Rule::hasType(Type type) const{
        if (std::get<0>(m_rule).objectHasType(type) ||
            std::get<1>(m_rule).objectHasType(type) ||
            std::get<2>(m_rule).objectHasType(type))
            return true;
        return false;
    }

    void RuleManager::addRule(const Rule& rule){
        m_rules.emplace_back(rule);
    }

    void RuleManager::removeRule(const Rule& rule){
        const auto iter {std::find(m_rules.begin(), m_rules.end(), rule)};
        if (iter != m_rules.end()){
            m_rules.erase(iter);
        }
    }
    
    void RuleManager::clearRules(){
        m_rules.clear();
    }

    const std::vector<std::reference_wrapper<const Rule>> RuleManager::getWhichRuleHasType(Type type) const{
        std::vector<std::reference_wrapper<const Rule>> rules_with_rule;

        for (const auto& rule : m_rules) {
            if (rule.hasType(type))
            {
                rules_with_rule.emplace_back(rule);
            }
        }
        return rules_with_rule;
    }
    
    Type RuleManager::findPlayer() const{
        for (const auto& each_rule : m_rules) {
            if (std::get<2>(each_rule.m_rule).objectHasType(Type::You)) {

                Objects obj {std::cref(std::get<0>(each_rule.m_rule))};
                if (std::size(obj.getTypes()) != 0) 
                    return (obj.getTypes())[0];
            }
        }
        return Type::Void;
    }
    
    bool RuleManager::objectHasProperty(const Objects& object, Type property){
        if (std::find(object.getTypes().begin(), object.getTypes().end(), object.objectHasType(property)) != object.getTypes().end()) 
            return true;
        return false;
    }

}// namespace Baba_Is_Us