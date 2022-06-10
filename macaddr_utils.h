#ifndef MACADDR_UTILS_H
#define MACADDR_UTILS_H


#include <stdint.h>
#include <string>

bool mac_atoi(uint8_t *i, const char *a);
void mac_itoa(char *a, uint8_t *i);
void mac_itos(std::string &s, const uint8_t *addr);
bool isValidMacAddress(const char* mac);

#endif // MACADDR_UTILS_H
