#ifndef LOGGER_H
#define LOGGER_H

#define TIME_STR_LEN 50

void __logDebug(const char *, ...); // NOLINT(*-reserved-identifier)

#ifdef NDEBUG
#define LOG_DEBUG(fmt, ...) ((void)0)
#else
#define LOG_DEBUG(...) __logDebug(__VA_ARGS__)
#endif

#endif /* LOGGER_H */
