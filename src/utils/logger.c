#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "logger.h"

static bool getTimeNow(char *buf, size_t len) {
  time_t currentTime = time(NULL);

  if (currentTime != (time_t)(-1)) {
    struct tm *localTime = localtime(&currentTime);

    if (localTime != NULL) {
      strftime(buf, len, "%F %T", localTime);
      return true;
    }
  }

  return false;
}

void logDebug(const char *fmt, ...) {
  char timeStr[50];
  if (!getTimeNow(timeStr, sizeof timeStr)) {
    strncpy(timeStr, "Failed to retrieve time", sizeof timeStr);
  }

  va_list args1;
  va_start(args1, fmt);
  va_list args2;
  va_copy(args2, args1);
  char debugStr[1 + vsnprintf(NULL, 0, fmt, args1)];
  va_end(args1);
  vsnprintf(debugStr, sizeof debugStr, fmt, args2);
  va_end(args2);

  printf("%s [DEBUG] %s\n", timeStr, debugStr);
}
