#ifndef COMMON_HPP
#define COMMON_HPP

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define LWIP_INTERNAL

extern "C" {
    #include "ets_sys.h"
    // #include "os_type.h"
    #include "osapi.h"
    // #include "mem.h"
    // #include "user_interface.h"
}

#include "lwip/opt.h"
#include "lwip/tcp.h"
#include "lwip/inet.h"


namespace update {

enum Error {
    OK = 0,
    E_ALLOC_FAIL = 1,
    E_BIND_FAIL = 2,
};

class Args {
public:
    Args(const char* str) :
        m_Str(0), m_Keys(0), m_Values(0), m_Count(0) {
        int length = strlen(str);
        m_Str = new char[length];

        m_Count = 0;
        for (int i = 0; i < length; ++i) {
            if (m_Str[i] == '=') {
                ++m_Count;
            }
        }

        if (!m_Count)
            return;

        m_Keys   = new const char*[m_Count];
        m_Values = new const char*[m_Count];

        char* start = m_Str;
        const char* end = m_Str + length;
        int iArg;
        for (iArg = 0; iArg < m_Count; ++iArg) {
            char* next = strchr(start, '=');
            if (!next)
                break;
            *next = 0;
            m_Keys[iArg] = start;
            start = next + 1;

            if (start >= end)
                break;

            next = strchr(start, '&');
            if (!next)
                break;
            *next = 0;
            m_Values[iArg] = start;
            start = next + 1;

            if (start >= end)
                break;
        }

        m_Count = iArg;
    }

    ~Args() {
        delete[] m_Str;
        delete[] m_Keys;
        delete[] m_Values;
    }

    const char* get(const char* key) {
        for (int i = 0; i < m_Count; ++i) {
            if (strcmp(key, m_Keys[i]) == 0) {
                return m_Values[i];
            }
        }
        return 0;
    }

protected:
    char* m_Str;

    int m_Count;
    const char** m_Keys;
    const char** m_Values;
};

class Sink {
public:
    virtual Error begin(Args& args, size_t size) { return OK; }
    virtual Error write(const uint8_t* data, size_t size) { return OK; }
    virtual Error abort() { return OK; }
    virtual Error end() { return OK; }
};

class Source {
public:
    virtual Error begin(Args& args) = 0;
};

class AuthChecker {
public:
    virtual Error check(Args& args, const uint8_t* contentHash, const uint8_t* hmac) {
        return OK;
    }
};





} // namespace update



#endif //COMMON_HPP