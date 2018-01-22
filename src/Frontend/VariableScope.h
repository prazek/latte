#pragma once
#include <cassert>
#include <unordered_map>
#include <vector>

template <typename Storage>
class VariableScope {
public:

  using Scope = std::unordered_map<std::string, Storage>;

  void openNewScope(Scope scope = Scope()) {
    varTypes.push_back(std::move(scope));
  }

  Scope closeScope() {
    assert(!varTypes.empty());
    Scope scope = std::move(varTypes.back());
    varTypes.pop_back();
    return scope;
  }

  [[nodiscard]]
  bool addName(std::string name, Storage type)  {
    if (findNameInCurrentScope(name))
      return false;
    varTypes.back()[std::move(name)] = type;
    return true;
  }

  // todo string_view
  Storage findName(const std::string &name) const {
    for (int i = varTypes.size() - 1; i >= 0; i--) {
      const auto &map = varTypes.at(i);
      if (map.count(name))
        return map.at(name);
    }
    return nullptr;
  }

  Storage findNameInCurrentScope(const std::string &name) const {
    if (varTypes.back().count(name))
      return varTypes.back().at(name);
    return nullptr;
  }

  /// Temorariy set type to nullptr
  Storage temporariryUnregisterName(const std::string &name) {
    for (int i = varTypes.size() - 1; i >= 0; i--) {
      auto &map = varTypes.at(i);
      if (map.count(name)) {
        Storage ret = map.at(name);
        map.at(name) = nullptr;
        return ret;
      }
    }
    return nullptr;
  }

  void registerBackName(const std::string &name, Storage type) {
    if (type == nullptr)
      return;

    for (int i = varTypes.size() - 1; i >= 0; i--) {
      auto &map = varTypes.at(i);
      if (map.count(name)) {

        assert(map.at(name) == nullptr);
        map.at(name) = type;
        return;
      }
    }
    assert(false && "need to find unregistered variable");
  }



private:

  std::vector<Scope> varTypes;
};

