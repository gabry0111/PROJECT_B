#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "enum_objects.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

namespace Baba_Is_Us {

class Objects {
 private:
  // sarà del tipo: un NOUN_TYPE e tanti PROPERTY_TYPE
  std::vector<Type> m_object{};

 public:
  Objects() = default;
  Objects(std::vector<Type> object_vect) : m_object{object_vect} {}

  const std::vector<Type> getTypes() const;
  bool operator==(const Objects &object) const;
  bool objectHasType(const Type type) const;
  void addType(const Type word);
  void removeType(Type type);
  void resetObject();
};
}  // namespace Baba_Is_Us

#endif