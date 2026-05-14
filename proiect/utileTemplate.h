#pragma once
#include <vector>


template <typename TipDorit, typename TipBaza>

int numaraDeTip(const std::vector<TipBaza*>& vec) {
    int count = 0;
    for (const auto* elem : vec) {
        if (dynamic_cast<const TipDorit*>(elem) != nullptr) {
            count++;
        }
    }
    return count;
}