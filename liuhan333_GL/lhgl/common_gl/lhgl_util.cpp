#include <iostream>
#include <fstream>
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include "lhgl_util.h"
#include "base_config.h"

namespace lh_gl {
    bool read_file(const char* filename, string& outfile)
    {
        ifstream f(filename);
        bool ret = false;
        if (f.is_open()) 
        {
            string line;
            while (getline(f, line)) 
            {
                outfile.append(line);
                outfile.append("\n");
            }
            f.close();
            ret = true;
        }
        else {
            LHGL_FILE_ERROR(filename);
        }

        return ret;
    }


#ifdef WIN32

    bool read_binaryfile(const char* filename, std::vector<int>& v)
    {
        HANDLE f = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (f == INVALID_HANDLE_VALUE) {
            LHGL_FILE_ERROR(filename);
            return false;
        }

        int len = GetFileSize(f, NULL);

        if (len == INVALID_FILE_SIZE) {
            LHGL_ERROR("Invalid file size %s\n", filename);
            return false;
        }

        // wip for tutorial51
        assert(0);

        return true;
    }

#else
    bool read_binaryfile(const char* filename, std::vector<int>& v)
    {
        int f = open(filename, O_RDONLY);

        if (f == -1) {
            printf("Error opening '%s': %s\n", filename, strerror(errno));
            return false;
        }

        v.clear();

        int len = 0;
        int index = 0;

        do {
            int syms[64];

            len = read(f, syms, sizeof(syms));
            assert((len % 4) == 0);

            if (len > 0) {
                v.resize(v.size() + len / 4);
                for (int i = 0; i < len / 4; i++) {
                    v[index] = syms[i];
                    index++;
                }
            }
        } while (len > 0);

        close(f);

        return true;
    }
#endif

    void lhgl_error(const char* filename, uint line, const char* format, ...)
    {
        char msg[MSG_BUFFER_LEN];
        va_list args;
        va_start(args, format);
        VSNPRINTF(msg, sizeof(msg), format, args);
        va_end(args);

#ifdef WIN32 
        char msg2[MSG_BUFFER_LEN];
        _snprintf_s(msg2, sizeof(msg2), "%s:%d: %s", filename, line, msg);
        MessageBoxA(NULL, msg2, NULL, 0);
#else
        fprintf(stderr, "%s:%d - %s", filename, line, msg);
#endif    
    }


    void lhgl_file_error(const char* filename, uint line, const char* fileerror)
    {
#ifdef WIN32
        char msg[MSG_BUFFER_LEN];
        _snprintf_s(msg, sizeof(msg), "%s:%d: unable to open file `%s`", filename, line, fileerror);
        MessageBoxA(NULL, msg, NULL, 0);
#else
        fprintf(stderr, "%s:%d: unable to open file `%s`\n", filename, line, fileerror);
#endif    
    }


    long long get_curr_timemillis()
    {
#ifdef WIN32    
        return GetTickCount();
#else
        timeval t;
        gettimeofday(&t, NULL);

        long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
        return ret;
#endif    
    }

#ifdef WIN32
#if (_MSC_VER == 1900)
#elif (_MSC_VER == 1800)
#else
    float fmax(float a, float b)
    {
        if (a > b)
            return a;
        else
            return b;
    }
#endif
}

#endif