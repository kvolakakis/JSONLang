#include "JSONLang.h"


PROGRAM_BEGIN

//JSON(temp_string) = STRING("first attempt")
//JSON(temp_integer) = NUMBER(3)
//JSON(temp_double) = NUMBER(3.14)
/*
    "outer" : {
        "key" : "value",
        "key2" : "value2",
        "number" : 32.6,
        "inner" : {
            "p" : "fuck yeah"
        }
    }
*/

JSON(outer) = OBJECT { 
    KEY(key) : STRING("value"),
    KEY(key2) : STRING("value2"),
    KEY(number): NUMBER(32.6),
    KEY(inner) : OBJECT {
        KEY(p) : STRING("fuck yeah"),
        KEY(inner2) : OBJECT {
                            KEY(p) : STRING("fuck yeah"),
                        },
    }
}

//PRINT temp

//JSON(arr) = ARRAY[NUMBER(2), STRING("3")]

PRINT "\n\n===program output===\n"
//PRINT temp_string
//PRINT temp_integer
//PRINT temp_double
PRINT outer

PROGRAM_END

