#include "enum_objects.hpp"
#include "rules.hpp"
#include "objects.hpp"
#include <algorithm>
#include <functional>

namespace Baba_Is_Us{

    bool operator==(const Rule& rhs, const Rule& lhs) {
        return rhs.m_rule == lhs.m_rule;
    }

    bool Rule::hasType(Type type) const{
        if (m_rule[0] == type ||
            m_rule[1] == type ||
            m_rule[2] == type)
            return true;
        return false;
    }

    const std::array<Type, 3>& Rule::getm_rule() const {
        return m_rule;
    }


    void RuleManager::addRule(const Rule& rule){
        m_rules.emplace_back(rule);
    }

    void RuleManager::removeRule(const Rule& rule){ // ??? se il parametro fosse const, "error: no match for ‘operator==’ (operand types are ‘Baba_Is_Us::Rule’ and ‘const Baba_Is_Us::Rule’)"(da std::find)
        //assert ?
        auto iter {std::find(m_rules.begin(), m_rules.end(), rule)};
        if (iter != m_rules.end()){
            m_rules.erase(iter);
        }
    }

    const std::vector<Rule>& RuleManager::getm_rules(){
        return m_rules;
    }
    
    // void RuleManager::movedBlock()

    void RuleManager::clearRules(){
        m_rules.clear();
    }

    constexpr std::vector<std::reference_wrapper<const Rule>> RuleManager::getWhichRuleHasType(Type type) const{
        std::vector<std::reference_wrapper<const Rule>> rules_with_rule;

        for (const auto& rule : m_rules) {
            if (rule.hasType(type))
            {
                rules_with_rule.emplace_back(rule);
            }
        }
        return rules_with_rule;
    }
    
    Type RuleManager::findPlayerType() const{
        for (const auto& each_rule : m_rules) {
            if (each_rule.m_rule[2] == Type::You) {

                Type type_Player {each_rule.m_rule[0]};
                return type_Player;
            }
        }
        return Type::Void;
    }
    /* In teoria non serve: Objects ha funzione objectHasType, e objectHasProperty è usata per controllare 
    in una cella della mappa se l'oggetto ha RuleManager.objectHasProperty(Objects, Type::SINK) (che comunque abbiamo conditions()).

    bool RuleManager::objectHasProperty(const Objects& object, Type property){
        if (std::find(object.getTypes().begin(), object.getTypes().end(), object.objectHasType(property)) != object.getTypes().end()) 
            return true;
        return false;
    }
    */


}// namespace Baba_Is_Us