#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "enum_objects.hpp"

#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

namespace Baba_Is_Us { // sarà il namespace di ogni file di questo progetto

class Objects {
private:
  std::vector<Type>
      m_object{}; // sarà del tipo: un NOUN_TYPE e tanti PROPERTY_TYPE

public:
  Objects() = default;
  Objects(std::vector<Type> object_vect) : m_object{object_vect} {}

  std::vector<Type> getTypes() const;
  std::vector<Type> &accessTypes();
  bool operator==(const Objects &object) const;
  bool objectHasType(const Type type) const;
  void addType(const Type word);
  void removeType(Type type);
  void resetObject();
};
} // namespace Baba_Is_Us

#endif