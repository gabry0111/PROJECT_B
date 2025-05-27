/* rules.hpp serve per gestire le regole che esistono nel gioco, e verificando che queste esistano,
alcune azioni saranno possibili.
Saranno oggetti vettori di tre elementi ciascuno: NOUN_TYPE, VERB_TYPE, PROPERTY_TYPE.


- controlla se esiste oggetto con 'You' (per enum PlayState)
- un metodo per controllare se un vettore regola è uguale a un vetttore m_object

*/
#include "objects.hpp"
#include <tuple>

namespace Baba_Is_Us {

class Rule{
public : 
    std::tuple<Objects, Objects, Objects> rule;
    Rule(Objects obj1, Objects obj2, Objects obj3);
};

class RuleManager{
private :
    std::vector<Rule> m_rules;

public :
    void addRule(const Rule& rule);
    void removeRule(const Rule& rule);
    void clearRules();
    std::vector<Rule> GetRules(Type type) const;
    std::size_t GetNumRules() const;
    //Type FindPlayer() const;
    bool HasProperty(const std::vector<Type>& types, Type property);
}
}
