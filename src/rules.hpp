/* rules.hpp serve per gestire le regole che esistono nel gioco, e verificando che queste esistano,
alcune azioni saranno possibili.
Saranno oggetti vettori di tre elementi ciascuno: NOUN_TYPE, VERB_TYPE, PROPERTY_TYPE.


- controlla se esiste oggetto con 'You' (per enum PlayState)
- un metodo per controllare se un vettore regola è uguale a un vetttore m_object

*/
#ifndef RULES_HPP
#define RULES_HPP
#include "enum_objects.hpp"
#include "objects.hpp"
#include "map.hpp"
#include <tuple>
#include <cassert>

namespace Baba_Is_Us {

// idea: creare una singola istanza di una regola
class Rule{
private : 
    std::tuple<Type, Type, Type> m_rule; // vedere differenza tra tuple e array
public : 
    Rule() = delete; // non si può creare una regola vuota
    Rule(Type type1, Type type2, Type type3) : m_rule{type1, type2, type3} { // ogni regola deve avere un noun, verb e property/noun 

        assert((
            (
                +type1 > +Type::NOUN_TYPE &&
                +type1 < +Type::ICON_NOUN_TYPE &&
                +type2 > +Type::VERB_TYPE &&
                +type2 < +Type::PROPERTY_TYPE &&
                +type3 > +Type::PROPERTY_TYPE
            ) || 
            (
                +type3 > +Type::NOUN_TYPE &&
                +type3 < +Type::ICON_NOUN_TYPE
            )
        ) && "Rule constructor condition not satisfied");
    }
    friend class RuleManager;
    friend bool operator==(const Rule& rhs, const Rule& lhs); // per algoritmi tipo find(), può forse diventare constexpr (dipende da std::tuple)
    bool hasType(Type type) const; // può diventare constexpr (dipende da objectHasType())
};

// idea: un singolo oggetto che gestisce tutte le regole
class RuleManager{
private :
    std::vector<Rule> m_rules;

public :
    void addRule(const Rule& rule); // può forse diventare constexpr (dipende da std::tuple)
    void removeRule(const Rule& rule); // come addRule()
    void initializem_rules(); // chiamata all'inizio, controlla tutte le griglie e crea le regole iniziali
    // chiamata quando una parola logica è mossa, controlla la vecchia posizione della regola e 
    // vede se era attaccata a altre parole logiche e modifica m_rules.
    void parseRule(); 
    constexpr void clearRules();
    // dato un'insieme di regole, servirà per avere un vettore con le tuple che hanno la regola type in modo da confrontare se un'azione è possibile.
    //N.B: se m_rules cambia, diventano dangling references
    constexpr std::vector<std::reference_wrapper<const Rule>> getWhichRuleHasType(Type type) const;
    // std::size_t GetNumRules() const; è inutile. guarda dove viene usato...
    Type findPlayer() const; // può diventare constexpr (dipende da objectHasType())
    bool objectHasProperty(const Objects& object, Type property); // controlla se un oggetto ha una proprietà
    // controlla le interazioni possibili tra un object e un altro object e dice se un'azione può essere fatta.
    // Per certe azioni che cambiano qualcosa dell'oggetto, si può vedere cosa è cambiato nell'ultimo Type del vector<Type> dell'oggetto
    // N.B: questa funzione NON si occupa di verificare la posizione nella mappa di niente. 
    // N.B: questa funzione NON si occupa di verificare che due parole logiche siano vicine
    // Se un oggetto ha più tipi, allora fare un ciclo che chiama conditions() per decidere se l'azione è legale.
    // le regole si leggono da sx a dx e da alto a basso
    PlayState conditions( Objects& object, const Objects& second) const; // restituisce la condizione di gioco; può forse diventare constexpr (non è finita)
};
}

#endif