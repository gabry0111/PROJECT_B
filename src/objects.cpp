#include "objects.hpp"

namespace Baba_Is_Us {  // sarà il namespace di ogni file di questo progetto

const std::vector<Type> &Objects::getTypes() const { return m_object; }

bool Objects::operator==(const Objects &obj) const {
  return (m_object == obj.m_object);
}

bool Objects::objectHasType(const Type type) const {
  assert(type != Type::NOUN_TYPE && type != Type::ICON_NOUN_TYPE &&
         type != Type::VERB_TYPE && type != Type::PROPERTY_TYPE &&
         "Objects::objectHasType() not given a valid type");
  if (type == Type::NOUN_TYPE || type == Type::ICON_NOUN_TYPE ||
      type == Type::VERB_TYPE || type == Type::PROPERTY_TYPE) {
    throw std::runtime_error("objectHasType() not given a valid type");
  }
  return std::find(m_object.begin(), m_object.end(), type) != m_object.end();
}

void Objects::addType(const Type word) {
  const bool is_valid_type{
      word != Type::NOUN_TYPE && word != Type::ICON_NOUN_TYPE &&
      word != Type::VERB_TYPE && word != Type::PROPERTY_TYPE};

  assert(is_valid_type && "add() not given a valid type");

  // aggiungi se valido e non già presente
  if (is_valid_type &&
      std::find(m_object.begin(), m_object.end(), word) == m_object.end()) {
    m_object.emplace_back(word);
  }
}

void Objects::removeType(const Type type) {
  const auto iter{std::find(m_object.begin(), m_object.end(), type)};
  const bool is_valid{type != Type::NOUN_TYPE && type != Type::ICON_NOUN_TYPE &&
                      type != Type::VERB_TYPE && type != Type::PROPERTY_TYPE &&
                      iter != m_object.end()};
  if (is_valid) m_object.erase(iter);
}

}  // namespace Baba_Is_Us