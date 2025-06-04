#include "enum_objects.hpp"
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

    bool RuleManager::conditions(Objects& object, const Type second) const{

        if(+Type::NOUN_TYPE < +second < +Type::ICON_NOUN_TYPE) { // deve essere valido Baba is you, Baba is wall
            object.add(second);
            return true;
        }

        switch (+Type::ICON_NOUN_TYPE < +second < +Type::VERB_TYPE) { // ???
        case 11:
            break;
        case 12:
            break;
        default:
            break;
        }

        switch (+Type::VERB_TYPE < +second < +Type::PROPERTY_TYPE) { // ???
        case 11:
            break;
        case 12:
            break;
        default:
            break;
        }
        // Gli unici casi rimasti sono: i PropertyType e nessun caso è andato a buon fine (tra cui se second == Type::ICON_NOUN_TYPE e simili).
        // Quindi posso confrontare direttamente i Type e mettere come default il caso in cui niente è andato a buon fine,
        // tanto non c'è possibilità che questo switch sia saltato, ed è l'ultimo a venire controllato
        switch (second) { // se il tipo dell'oggetto target è ... allora fai ... e ritorna ...
        case Type::Hot:
            if (object.objectHasType(Type::Push)) ; //use movement() per spostare l'oggetto hot (N.B: se ci sono tanti casi così, usa goto...)
            else // rimuovi l'icon grafica da quella posizione
            break;
        case Type::Launch :
            // if(posizione di player è sopra l'object che ha property launch(obj2)) allora (position di obj2 +=2 a seconda di dove guarda player) 
            break;
        case Type::Move : // che differenza c'è tra Move e Push?
            break;
        case Type::Open : // ???
            
            break;
        case Type::Push : // ???
            
            break;
        case Type::Quantum :
            break;
        case Type::Shut :
            break;
        case Type::Stop :
            break;
        case Type::Win :
            break;
        case Type::You :
            break;
        default:
            break;
        }

        throw std::runtime_error("RuleManager::conditions nessun caso è andato a buon fine");
    }

}// namespace Baba_Is_Us