//
// Created on 2018/8/1.
//
#include <iostream>
#include <string>
#include <vector>
#include <map>

template<class K, class V>
class KeyValues {
public:
    KeyValues() = default;

    ~KeyValues() = default;

    bool Find(const K &key, const V &value, bool update = false) {
        bool ret = false;
        const auto &mapIt = _lookupTable.lower_bound(key);
        if (mapIt != _lookupTable.cend() && mapIt->first == key) {
            const auto &valueIt = std::lower_bound(mapIt->second.cbegin(),
                                                   mapIt->second.cend(),
                                                   value);
            if (valueIt != mapIt->second.cend() && *valueIt == value) {
                ret = true;
            } else if (update) {
                mapIt->second.emplace(valueIt, value);
            }
        } else if (update) {
            std::vector<V> values = {value};
            _lookupTable.emplace_hint(mapIt, key, values);
        }
        return ret;
    }

private:
    // { t1 : [sa, sb]),
    //   t2 : [sc, sd, se]),
    //   ... }
    std::map<const K, std::vector<V>> _lookupTable;
};

int main() {
    KeyValues<int, int> keyValues1;
    std::cout << keyValues1.Find(1, 1, true) << std::endl;
    std::cout << keyValues1.Find(2, 2, true) << std::endl;
    std::cout << keyValues1.Find(2, 4, true) << std::endl;
    std::cout << keyValues1.Find(1, 1, true) << std::endl;
    std::cout << keyValues1.Find(2, 2, true) << std::endl;
    std::cout << keyValues1.Find(3, 2, true) << std::endl;
    std::cout << keyValues1.Find(3, 1, true) << std::endl;
    std::cout << keyValues1.Find(2, 1, true) << std::endl;
    std::cout << keyValues1.Find(2, 3, true) << std::endl;
    std::cout << keyValues1.Find(2, 6, true) << std::endl;
    std::cout << keyValues1.Find(2, 6, true) << std::endl;
    std::cout << keyValues1.Find(0, 0, true) << std::endl;
    std::cout << keyValues1.Find(5, 5) << std::endl;
    std::cout << keyValues1.Find(3, 3) << std::endl;
    std::cout << keyValues1.Find(3, 1) << std::endl;
    std::cout << keyValues1.Find(2, 5) << std::endl;
    std::cout << keyValues1.Find(2, 0) << std::endl;
    std::cout << keyValues1.Find(0, 0) << std::endl;
    std::cout << keyValues1.Find(-1, -1) << std::endl;

    KeyValues<std::string, std::string> keyValues2;
    std::cout << keyValues2.Find("James", "Oxford", true) << std::endl;
    std::cout << keyValues2.Find("Mike", "Belfast", true) << std::endl;
    std::cout << keyValues2.Find("James", "Manchester", true) << std::endl;
    std::cout << keyValues2.Find("John", "London", true) << std::endl;
    std::cout << keyValues2.Find("John", "London", true) << std::endl;
}