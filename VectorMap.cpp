#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

struct StructWithoutDefaultConstructor
{
    StructWithoutDefaultConstructor() = delete;
    int number_;
};

template <class KeyType, class ValueType>
class VectorMap
{
public:
    bool isIntKey()
    {
        return (std::is_integral<KeyType>::value ? true : false);
    }

    void insert(KeyType key, ValueType value)
    {
        keyVector_.emplace_back(key);
        valueVector_.emplace_back(value);
    }

    ValueType at(const KeyType &key)
    {
        auto keyIter = std::ranges::find(keyVector_, key);

        if (keyIter == end(keyVector_))
        {
            throw std::out_of_range("Thrown from VectorMap::at()");
        }
        else
        {
            auto dist = std::distance(begin(keyVector_), keyIter);
            return valueVector_.at(dist);
        }
    }

    ValueType &operator[](const KeyType &key)
    {
        auto keyIter = std::ranges::find(keyVector_, key);

        if (keyIter == end(keyVector_))
        {
            std::cout << "There is no given value" << std::endl;
            insert(key, static_cast<ValueType>(48));
            return valueVector_.back();
        }
        else
        {
            auto dist = std::distance(begin(keyVector_), keyIter);
            return valueVector_.at(dist);
        }
    }

    constexpr static bool is_int_key{std::is_integral<KeyType>::value};

private:
    static_assert(std::is_default_constructible<ValueType>::value, "You need to provide type with default constructor");
    std::vector<KeyType> keyVector_{};
    std::vector<ValueType> valueVector_{};
};

template <class ValueType>
class VectorMap<bool, ValueType>
{
public:
    void insert(bool key, ValueType value)
    {
        if (counter_ == 0)
        {
            pair1_.first = key;
            pair1_.second = value;
            counter_++;
        }
        else if (counter_ == 1)
        {
            pair2_.first = key;
            pair2_.second = value;
            counter_++;
        }
        else
            throw std::out_of_range("VectorMap filled");
    }

    ValueType at(const KeyType &key)
    {
        if(counter_)
        {
            throw std::out_of_range("VectorMap empty");
        }
        if(key == true)
        {
            if(pair1_.first == true)
            {
                return pair1_.second;
            }
            else if(pair2_.first == true)
            {
                return pair2_.second;
            }
            else

        }

    }

private:
    static_assert(std::is_default_constructible<ValueType>::value, "You need to provide type with default constructor");
    std::pair<bool, ValueType> pair1_{};
    std::pair<bool, ValueType> pair2_{};
    int counter_{0};
};

int main()
{
    VectorMap<int, char> vectorMap;
    vectorMap.insert(1, 'a');
    vectorMap.insert(2, 'b');

    // std::cout << vectorMap.keyVector_.at(0) << std::endl;
    // std::cout << vectorMap.valueVector_.at(0) << std::endl;
    // std::cout << vectorMap.keyVector_.at(1) << std::endl;
    // std::cout << vectorMap.valueVector_.at(1) << std::endl;

    // std::cout << vectorMap[1] << std::endl;
    // std::cout << vectorMap[2] << std::endl;
    // std::cout << vectorMap[10] << std::endl;
    // std::cout << vectorMap[10] << std::endl;
    // std::cout << vectorMap.at(1) << std::endl;
    // std::cout << vectorMap.at(10) << std::endl;

    // VectorMap<int, StructWithoutDefaultConstructor> vectorMap2;

    // std::cout << std::boolalpha << vectorMap.isIntKey() << std::endl;
    // std::cout << vectorMap.is_int_key << std::endl;

    // VectorMap<double, char> vectorMap2;
    // std::cout << vectorMap2.is_int_key << std::endl;

    VectorMap<bool, int> vectorMap3;
    vectorMap3.insert(true, 10);
    vectorMap3.insert(false, 20);
    vectorMap3.insert(true, 30);

    return 0;
}
