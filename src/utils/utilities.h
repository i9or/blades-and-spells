#ifndef UTILITIES_H
#define UTILITIES_H

#define STRIP_NEWLINE(str) (str)[strcspn((str), "\r\n")] = '\0'

#endif /* UTILITIES_H */
