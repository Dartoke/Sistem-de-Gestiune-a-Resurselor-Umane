#pragma once
#include <cstring>

char* copiazaSir(const char* sursa) {
    if (!sursa) return nullptr;
    char* dest = new char[strlen(sursa) + 1];
    strcpy(dest, sursa);
    return dest;
}
