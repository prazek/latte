#pragma once
#include <cassert>
#include <unordered_map>
#include <vector>

template <typename Storage>
class VariableScope {
public:
  void openNewScope() {
    varTypes.emplace_back();
  }

  void closeScope() {
    assert(!varTypes.empty());
    varTypes.pop_back();
  }

  bool addVariableType(std::string name, Storage type)  {
    if (findVariableTypeCurrentScope(name))
      return false;
    varTypes.back()[std::move(name)] = type;
    return true;
  }

  // todo string_view
  Storage findVariableType(const std::string &name) const {
    for (int i = varTypes.size() - 1; i >= 0; i--) {
      const auto &map = varTypes.at(i);
      if (map.count(name))
        return map.at(name);
    }
    return nullptr;
  }

  Storage findVariableTypeCurrentScope(const std::string &name) const {
    if (varTypes.back().count(name))
      return varTypes.back().at(name);
    return nullptr;
  }

  /// Temorariy set type to nullptr
  Storage temporariryUnregister(const std::string &name) {
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

  void registerBack(const std::string &name, Storage type) {
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
  std::vector<std::unordered_map<std::string, Storage>> varTypes;
};

