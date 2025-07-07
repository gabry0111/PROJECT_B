#include "rules.hpp"

namespace Baba_Is_Us {

bool operator==(const Rule &rhs, const Rule &lhs) {
  return rhs.m_rule == lhs.m_rule;
}

const std::vector<Rule> &RuleManager::getm_rules() const { return m_rules; }

/////////////////////////////////// Chapter: Handling Interactions
/////////////////////////////////////////
PlayState handleDefeat(Objects &tail) {
  if (tail.objectHasType(Type::You)) {
    tail.resetObject();
    return PlayState::Invalid;
  }
  return PlayState::Playing;
}
PlayState handleWin(Objects &tail, Objects &mismatch) {
  if (mismatch.objectHasType(Type::Defeat)) {
    handleDefeat(tail);
  }
  return PlayState::Won;
}
PlayState handleHot(Objects &tail) {
  if (!tail.objectHasType(Type::Push)) {
    tail.resetObject();
    return PlayState::Invalid;
  }
  return PlayState::Playing;
}
PlayState handleMelt(Objects &tail) {
  tail.resetObject();
  return PlayState::Invalid;
}
PlayState handleShut(Objects &tail, Objects &mismatch) {
  if (!tail.objectHasType(Type::Open)) {
    tail.resetObject();
    return PlayState::Invalid;
  }
  mismatch.resetObject();
  tail.resetObject();
  return PlayState::Playing;
}
PlayState handleSpin(Objects &tail, Objects &mismatch) {
  if (mismatch.objectHasType(Type::Win)) {
    return handleWin(tail, mismatch);
  } else if (mismatch.objectHasType(Type::Defeat)) {
    return handleDefeat(tail);
  }
  return PlayState::Invalid;
}
PlayState handleStop(Objects &tail, Objects &mismatch) {
  if (mismatch.objectHasType(Type::Shut)) {
    return handleShut(tail, mismatch);
  }
  if (!tail.objectHasType(Type::Push)) {
    return PlayState::Invalid;
  }
  return PlayState::Playing;
}

PlayState conditions(Objects &tail, Objects &mismatch) {
  PlayState result{PlayState::Playing};
  if (mismatch == tail)
    return result;

  for (const Type mism_type : mismatch.getTypes()) {

    if (+mism_type <= +Type::PROPERTY_TYPE) {
      continue;
    }
    switch (mism_type) { // clang-format off
    case Type::Defeat:  return handleDefeat(tail);
    case Type::Hot:     if (tail.objectHasType(Type::Melt)){    
                          result = handleMelt(tail); 
                          break;
                        } else {
                          result = handleHot(tail);
                          break;
                        }
    case Type::Melt:    break; // Melt influenza solo se chi si muove incontra Hot
    case Type::Shut:    result = handleShut(tail, mismatch); break;
    case Type::Spin:    return handleSpin(tail, mismatch);
    case Type::Stop:    result = handleStop(tail, mismatch); break;

    case Type::Switch:
    case Type::Push:
    case Type::Open:
    case Type::You:     break;

    case Type::Win:     return handleWin(tail, mismatch); // verrebbe sovrascritto
    default:  throw(std::runtime_error("conditions(): default statement")); break;
    } // clang-format on
    if (result == PlayState::Invalid)
      return PlayState::Invalid;
  }
  return result;
}

} // namespace Baba_Is_Us