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
        if (std::get<0>(m_rule) == type ||
            std::get<1>(m_rule) == type ||
            std::get<2>(m_rule) == type)
            return true;
        return false;
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
    
    void RuleManager::initializem_rules() {
        m_rules.clear();
        for (auto pos : m_map.getPositions(Type::Block)) {
            // N.B: per Block: [0] = Block, [1] = NOUN_TYPE, [2] (da vedere se sarà così) = ICON_NOUN_TYPE
            // check orizzontale
            if (m_map.At(pos.second - 1, pos.first).getTypes()[0] == Type::Block) {continue; // se non sei la prima parola logica
            } else {
                std::vector<Type> word1 {m_map.At(pos.second, pos.first).getTypes()};
                std::vector<Type> word2 {m_map.At(pos.second + 1, pos.first).getTypes()};
                std::vector<Type> word3 {m_map.At(pos.second + 2, pos.first).getTypes()};
                if (word2[0] == Type::Block && word3[0] == Type::Block) { // se ci sono altre 2 parole logiche in fila
                    if(+word1[1] < +Type::ICON_NOUN_TYPE && // se 3 parole di fila sono NOUN_TYPE, VERB_TYPE e PROPERTY_TYPE
                        +word2[1] > +Type::VERB_TYPE &&
                        +word2[1] < +Type::PROPERTY_TYPE &&
                        +word3[1] > +Type::PROPERTY_TYPE) {
                            Rule new_rule {word1[1], word2[1], word3[1]};
                            addRule(new_rule);
                    }
                }
            }
            //check verticale
            if (m_map.At(pos.second, pos.first - 1).getTypes()[0] == Type::Block) {continue; // se non sei la prima parola logica
            } else {
                std::vector<Type> word1 {m_map.At(pos.second, pos.first).getTypes()};
                std::vector<Type> word2 {m_map.At(pos.second, pos.first + 1).getTypes()};
                std::vector<Type> word3 {m_map.At(pos.second, pos.first + 2).getTypes()};
                if (word2[0] == Type::Block && word3[0] == Type::Block) { // se ci sono altre 2 parole logiche in fila
                    if(+word1[1] < +Type::ICON_NOUN_TYPE && // se 3 parole di fila sono NOUN_TYPE, VERB_TYPE e PROPERTY_TYPE
                        +word2[1] > +Type::VERB_TYPE &&
                        +word2[1] < +Type::PROPERTY_TYPE &&
                        +word3[1] > +Type::PROPERTY_TYPE) {
                            Rule new_rule {word1[1], word2[1], word3[1]};
                            addRule(new_rule);
                    }
                }
            }
        }
    }

    // void RuleManager::movedBlock()

    constexpr void RuleManager::clearRules(){
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
    
    Type RuleManager::findPlayer() const{
        for (const auto& each_rule : m_rules) {
            if (std::get<2>(each_rule.m_rule) == Type::You) {

                Type type_Player {std::get<0>(each_rule.m_rule)};
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

    PlayState RuleManager::conditions(Objects& object, Objects& second) const{
        std::vector<Type> second_types {second.getTypes()};
        for(const auto type : second_types){
            // deve essere valido Baba is you, Baba is wall, Baba is lava, ma non Baba is block
            if(+Type::NOUN_TYPE < +type && +type < +Type::ICON_NOUN_TYPE && type != Type::Block) { 
                assert(!object.objectHasType(type)); // controlla non abbia già quel tipo in m_object
                if(!object.objectHasType(type)) { // per la grafica (nel caso Baba is wall and rock) verrà applicata solo la skin del primo tipo
                    object.addType(type);
                    return PlayState::Playing;
                }
                else {std::iter_swap(std::find(object.getTypes().begin(), object.getTypes().end(), type), object.getTypes().end() - 1);}
            }
            // non ci interessa degli ICON_NOUN_TYPE
            // non ci interessa gei verb type che creeranno una regola. Ci penserà un'altra funzione

            // Gli unici casi rimasti sono: i PropertyType e nessun caso è andato a buon fine (tra cui se second_types == Type::ICON_NOUN_TYPE e simili).
            // Quindi posso confrontare direttamente i Type e mettere come default il caso in cui niente è andato a buon fine,
            // tanto non c'è possibilità che questo switch sia saltato, ed è l'ultimo a venire controllato
            switch (+type > +Type::PROPERTY_TYPE) { // se il tipo dell'oggetto target è ... allora fai ... e ritorna ...
            case +Type::Hot :
                if (second.objectHasType(Type::Push)) {
                    return PlayState::Playing;
                }
                else {object.resetObject();}; 
                return PlayState::Playing;
            
            case +Type::Launch : // Lo togliamo? // cosa fare se un oggetto cammina sopra un altro:
                // vedere se è già presente un oggetto; 
                // if(posizione di player è sopra l'object che ha property launch(obj2)) allora (position di obj2 +=2 a seconda di dove guarda player) 
                return PlayState::Playing;
            
            case +Type::Move : // ???
                return PlayState::Playing;
            
            case +Type::Open : // ???
                return PlayState::Playing;
            
            case +Type::Push : // ???
                return PlayState::Playing;
            
            case +Type::Quantum : // Lo togliamo?
                return PlayState::Playing;
            
            case +Type::Shut : // Lo togliamo?
                return PlayState::Playing;

            case +Type::Sink :
                if (object.objectHasType(Type::Float)) {
                    second.resetObject();
                    // in teoria si dovrebbe vedere solo la sprite dell'oggetto, senza essere un oggetto fisico?
                    // oppure scompaiono entrambi
                    object.resetObject();
                    return PlayState::Playing;
                }
                else {object.resetObject();}
                return PlayState::Playing;

            case +Type::Stop :
                if(second.objectHasType(Type::Push))
                    return PlayState::Playing;
                return PlayState::Invalid;
            case +Type::Win :
                return PlayState::Won;
            case +Type::You : // ???
                return PlayState::Playing;
            default:
                return PlayState::Invalid;
            }
        }
        throw std::runtime_error("RuleManager::conditions nessun caso è andato a buon fine");
    }

}// namespace Baba_Is_Us