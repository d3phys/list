#ifndef LOG_H
#define LOG_H

#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <config.h>

extern const char LOG_NAME[];

static const char HEADER[] = "<!DOCTYPE html>                      \n"
                                "<html>                            \n"
                                   "<head>                         \n"
                                      "<meta charset=\"utf-8\" />  \n"
                                      "<title>Log</title>          \n"
                                   "</head>                        \n"
                                "<body>                            \n"
                                        "<pre><font color=\"navy\">\n"
                                                        "░▄▄▄▄░    \n"
                                                        "▀▀▄██►    \n"
                                                        "▀▀███►    \n"
                                                        "░▀███►░█► \n"
                                                        "▒▄████▀▀  \n"
                                                        "   </font>\n";  
                                                    
static inline FILE *create_log();
static FILE *LOG = create_log();
static void close_log();
inline FILE *get_log();

/**
 * @brief  Gets local time
 * @param  fmt  time format
 *
 * Function uses local static buffer with a constant length.
 * It is designed to be called multiple times.
 *
 * @return Local time as a formatted string.
 */
static char *local_time(const char *const fmt) 
{
        assert(fmt);

        static const size_t buf_size = 0xFF;
        static char str_tm[buf_size] = {0};

        static time_t t = time(nullptr);
        if (t == -1)
                return nullptr;

        static tm *lt = localtime(&t);
        strftime(str_tm, buf_size, fmt, lt); 

        return str_tm;
}

static inline FILE *create_log()
{
        LOG = fopen(LOG_NAME, "w");
        if (!LOG) {
                perror("Can't open log file");
                LOG = stderr;
        }

        int err = atexit(close_log);
        if (err)
                perror("Log file will not be closed");

        err = setvbuf(LOG, nullptr, _IONBF, 0);
        if (err)
                perror("Function 'setvbuf' failed");

        fprintf(LOG, HEADER);
        return LOG;
}

inline FILE *get_log()
{
        return LOG;
}

static void close_log()
{
        int err = fclose(LOG);
        if (err == EOF)
                perror("Can't close log file");
}

#define $(code) log("%s\n", #code); code

#ifndef LOG_FILE 
#define log(fmt, ...) (void(0))
#else
#define log(fmt, ...)                                                                         \
        do {                                                                                  \
                fprintf(get_log(), "<font color=\"Chocolate\"> >> [%s] At %s %s(%d): </font>" \
                        fmt, local_time("%x %H:%M:%S"),                                       \
                        __FILE__, __func__, __LINE__, ##__VA_ARGS__);                         \
        } while (0)
#endif /* LOG_FILE */

#ifndef LOG_FILE 
#define qlog(fmt, ...) (void(0))
#else
#define qlog(fmt, ...)                              \
        do {                                        \
                fprintf(get_log(), fmt, ##__VA_ARGS__); \
        } while (0)

#endif /* LOG_FILE */

#endif /* LOG_H */


