#include "JSONLang.h"


PROGRAM_BEGIN

JSON(temp_string) = STRING("first attempt")
JSON(temp_integer) = NUMBER(3)
JSON(temp_double) = NUMBER(3.14)
JSON(key_temp) = KEY(test)

PRINT "\n\n===program output===\n"
PRINT temp_string
PRINT temp_integer
PRINT temp_double
PRINT "key: "
PRINT key_temp

PROGRAM_END