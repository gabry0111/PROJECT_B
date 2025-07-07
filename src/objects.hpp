#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <algorithm>
#include <cassert>
#include <vector>

#include "enum_objects.hpp"

namespace Baba_Is_Us {  // sarà il namespace di ogni file di questo progetto

class Objects {
 private:
  // sarà del tipo: un NOUN_TYPE e tanti PROPERTY_TYPE
  std::vector<Type> m_object{};

 public:
  Objects() = default;
  Objects(const std::vector<Type> &object_vect) : m_object{object_vect} {}

  const std::vector<Type> &getTypes() const;
  bool operator==(const Objects &object) const;
  bool objectHasType(const Type type) const;
  void addType(const Type word);
  void removeType(const Type type);
  constexpr void resetObject();
};

constexpr void Objects::resetObject() {
  m_object.clear();
  m_object.push_back(Type::Void);
  assert(m_object[0] == intToType(0) &&
         "resetObject() doesn't work like intended");
}

}  // namespace Baba_Is_Us

#endif