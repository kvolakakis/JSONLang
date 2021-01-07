#include "JSONLang.h"


PROGRAM_BEGIN

/*JSON(emptyObj) = OBJECT {}

JSON(book) = OBJECT {
    KEY(title) : STRING("GoneEEEEEEE Girl"),
    KEY(published) : NUMBER(2012),
    KEY(type) : STRING("Thriller"),
    KEY(author) : OBJECT{
                        KEY(firstname) : TRUE,//STRING("GILLIAN"),
                        KEY(surname) : FALSE,//STRING("FLYNN"),
                        KEY(age) : NUMBER(45)
                        }
}


JSON(week_temperatures) = ARRAY [
    NUMBER(20),NUMBER(19.5),NUMBER(19),NUMBER(20),
    NUMBER(19),NUMBER(18.5),NUMBER(19)
]

JSON(emptyArray) = ARRAY

JSON(students) = ARRAY [
    OBJECT {
        KEY(name) : STRING("Kevin Malone"),
        KEY(id) : NUMBER(4444),
        KEY(grades) : ARRAY[
            OBJECT { KEY(hy100) : NUMBER(9.5) },
            OBJECT { KEY(hy150) : NUMBER(9) }
        ]
    }
]*/

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

/*JSON(outer) = OBJECT { 
    KEY(key) : STRING("value"),
    KEY(key2) : STRING("value2"),
    KEY(number): NUMBER(32.6),
    KEY(inner) : OBJECT {
        KEY(p) : STRING("fuck yeah"),
        KEY(inner2) : OBJECT {
                            KEY(p) : STRING("fuck yeah"),
                        },
    }
}*/

JSON(arr) = ARRAY[
                    NUMBER(1), 
                    NUMBER(2), 
                    NUMBER(3), 
                    STRING("p"),
                    OBJECT { 
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
                ]
//JSON(arr) = OBJECT{
//    KEY(0) : NUMBER(100)
//}
//JSON(arr) = JSON_val();//[NUMBER(2)]

PRINT "\n\n===program output===\n"
/*PRINT temp_string
PRINT temp_integer
PRINT temp_double
PRINT outer
PRINT arr
PRINT emptyObj
PRINT emptyArray
PRINT book
PRINT week_temperatures
PRINT students*/
PRINT arr[4]["inner"]["inner2"]["p"]
PROGRAM_END

