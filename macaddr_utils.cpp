#include <cstring>
#include <ctype.h>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "stdio.h"

#include "macaddr_utils.h"

using namespace std;

bool atonybble(const char c, uint8_t &nybble)
{
    bool rc = true;

    if (c >= '0' && c <= '9')
    {
        nybble = static_cast<uint8_t>(c - '0');
    }
    else if (c >= 'A' && c <= 'F')
    {
        nybble = static_cast<uint8_t>(c - 'A' + 10);
    }
    else if (c >= 'a' && c <= 'f')
    {
        nybble = static_cast<uint8_t>(c - 'a' + 10);
    }
    else
    {
        rc = false;
        cerr << "atonybble(): Invalid input char " << std::hex << c << endl;
    }
    return rc;
}

bool atoui(const char *c, uint8_t &ui)
{
    bool rc = true;
    uint8_t nybble_low;
    uint8_t nybble_high;

    rc = atonybble(*c, nybble_high);
    if (rc == true)
    {
        rc = atonybble(*(c+1), nybble_low);
        if (rc == true)
        {
            ui = static_cast<uint8_t>(nybble_high << 4) | nybble_low;
        }
    }
    return rc;
}

bool mac_atoi(uint8_t *i, const char *a)
{
    bool rc = true;

//    cerr << "decoding string " << a << "." << endl << flush;
    rc = atoui(&a[0], i[0]);
    if (rc == true)
    {
        rc = atoui(&a[3], i[1]);
        if (rc == true)
        {
            rc = atoui(&a[6], i[2]);
            if (rc == true)
            {
                rc = atoui(&a[9], i[3]);
                if (rc == true)
                {
                    rc = atoui(&a[12], i[4]);
                    if (rc == true)
                    {
                        rc = atoui(&a[15], i[5]);
                    }
                }
            }
        }
    }
    return rc;
}

void mac_itoa(char *a, uint8_t *i)
{
    snprintf(a,
             18, // number of characters in a formatted MAC address (including null terminator).
             "%02x:%02x:%02x:%02x:%02x:%02x",
             i[0], i[1], i[2], i[3], i[4], i[5]);
}

// mac_itos: converts byte array containing mac address to string.
void mac_itos(string &s, const uint8_t *addr)
{
    std::stringstream sstream;
    uint32_t iiii;  // stringstream doesn't work right with a u8 as input.

    s.clear();

    for (int i = 0; i < 6; ++i)
    {
        iiii = addr[i];
        //cout << "iiii (assigned from addr[i]) is " << iiii << "." << endl;
        sstream.str("");
        sstream << std::setfill ('0') << std::setw(2) << std::hex << iiii;
        s.append(sstream.str());
        if (i != 5)
        {
            s.append(":");
        }
    }
}

// checks a string to determine whether it is a valid MAC address
// in the form "aa:bb:cc:dd:ee:ff" or just "aabbccddeeff"
// from https://stackoverflow.com/questions/4792035/how-do-you-validate-that-a-string-is-a-valid-mac-address-in-c
// not perfect, but probably good enough.

bool isValidMacAddress(const char* mac)
{
    int i = 0;  // count of hex digits found
    int s = 0;  // count of separators found
    bool rc;
    int len;

    len = strlen(mac);
    if (len != 17)
    {
        cout << "isValidMacAddress(): strlen of mac address is " << len << "." << endl << flush;
    }
    while (*mac)
    {
        if (isxdigit(*mac))
        {
            i++;
        }
        else if (*mac == ':' || *mac == '-')
        {
            if ((i == 0) || (s != (i / 2) - 1))
            {
                break;
            }
            ++s;
        }
        else
        {
            s = -1;
            break;
        }
        ++mac;
    }

    if (i == 12 && (s == 5 || s == 0))
    {
        rc = true;
    }
    else
    {
        rc = false;
        cout << "isValidMacAddress() returning false. mac = "
             << mac << ". i = " << i << " and s = " << s << "." << endl << flush;
    }
    return rc;
}
