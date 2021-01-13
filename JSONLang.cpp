#include "JSONLang.h"

PROGRAM_BEGIN

PRINT "\n\nBasic initializations examples\n"
//define emptyObj json with empty object
JSON(emptyObj) = OBJECT {}
PRINT emptyObj

//define emptyArray json with empty array
JSON(emptyArray) = ARRAY
PRINT emptyArray

//define book json with an object containing data for a book
JSON(book) = OBJECT {
                KEY(title) : STRING("Gone Girl"),
                KEY(published) : NUMBER(2012),
                KEY(type) : STRING("Thriller"),
                KEY(author) : OBJECT{
                                    KEY(firstname) : STRING("GILLIAN"),
                                    KEY(surname) : STRING("FLYNN"),
                                    KEY(age) : NUMBER(45)
                }
}
PRINT book

//define week_temperatures json with an array of numbers
JSON(week_temperatures) = ARRAY[ NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
                                 NUMBER(19), NUMBER(18.5), NUMBER(19) ] 
PRINT week_temperatures

//define students json with an array of objects representing students
JSON(students) = ARRAY[
                    OBJECT{
                        KEY(name) : STRING("Pre Malone"),
                        KEY(id) : NUMBER(4444),
                        KEY(grades) : ARRAY[
                            OBJECT{ KEY(hy100) : NUMBER(9.5) },
                            OBJECT{ KEY(hy150) : NUMBER(9) } ]
                    },
                    OBJECT{
                        KEY(name) : STRING("Post Malone"),
                        KEY(id) : NUMBER(4444),
                        KEY(grades) : ARRAY[
                            OBJECT{ KEY(hy100) : NUMBER(9.5) },
                            OBJECT{ KEY(hy150) : NUMBER(9) } ]
                    } 
                     ]
PRINT students

/* EVERYTHING RELATED TO JSON MANIPULATION */
PRINT "\n\n\"SET json_lvalue ASSIGN value\" examples\n"
//change 3rdday temperature from 19 to 22
SET week_temperatures[2] ASSIGN NUMBER(22)
PRINT week_temperatures

//add email address for 1st student
PRINT students[0] 
SET students[0]["email"] ASSIGN STRING("csd404@csd.uoc.gr")
PRINT students

//assign new object in emptyObj json
SET emptyObj ASSIGN OBJECT{ KEY(a) : STRING("alpha") }
PRINT emptyObj["a"]

PRINT "\n\n\"ERASE json_value_or_variable\" examples\n"
ERASE book["author"]["age"] //removes age from author object of book
PRINT book
ERASE book["type"] //removes type of book
PRINT book
ERASE book //removes all book data, now book is an empty object
PRINT book

PRINT "\n\n\"SET json_array APPEND value1, value2, ?\" examples\n"
//appends values 23, 22, 20 to the end of the temperature array
SET week_temperatures APPEND NUMBER(23)//, NUMBER(22), NUMBER(20)
PRINT week_temperatures
//appends a grade for course hy255
SET students[0]["grades"] APPEND OBJECT { KEY(hy255) : NUMBER(9) }
PRINT students

PRINT "\n\nArithmetic and Comparison operators examples\n"

JSON(hy352_ang) = OBJECT{ KEY(exam) : NUMBER(8), KEY(project) : NUMBER(9.2) }
PRINT hy352_ang

JSON(Students) = ARRAY[
                    OBJECT {
                        KEY(name) : STRING("Angela ") + STRING("Martin"),
                        KEY(id) : NUMBER(4444) != NUMBER(4444),
                        KEY(grades) : ARRAY[
                        OBJECT {
                            KEY(hy352):
                            hy352_ang["exam"] * NUMBER(0.75) + hy352_ang["project"] * NUMBER(0.25)
                        }
                        ]
                    }
                ]

PRINT Students;

JSON(operators) = OBJECT{
                        KEY(operator+) : OBJECT{
                                            KEY(numbers: 2 + 3.14) : NUMBER(2) + NUMBER(3.14),
                                            KEY(strings: '2' + '3.14') : STRING("2") + STRING("3.14")//,
                                            //KEY(arrays: [2, 3.14] + [3, 2.72]) : ARRAY[NUMBER(2), NUMBER(3.14)] + ARRAY[NUMBER(3), NUMBER(2.72)]
                                            //KEY(objects: {'k1' : 3 } + {'k2' : "hellozz"}) : OBJECT{KEY(k1) :NUMBER(3) } + OBJECT{ KEY(k2) : STRING("hellozz")}
                        },
                        KEY(operator-) : OBJECT{
                                            KEY(numbers: 2 - 3.14) : NUMBER(2) - NUMBER(3.14)
                        },
                        KEY(operator*) : OBJECT{
                                            KEY(numbers: 2 * 3.14) : NUMBER(2) * NUMBER(3.14)
                        },
                        KEY(operator/) : OBJECT{
                                            KEY(numbers: 2 / 3.14) : NUMBER(2) / NUMBER(3.14)
                        },
                        KEY(operator%) : OBJECT{
                                            KEY(numbers: 2 % 3.14 (double converted to integer)) : NUMBER(2) % NUMBER(3.14),
                                            KEY(numbers: 996 % 100 (grade expected to this project<3)) : NUMBER(996) % NUMBER(100)
                        },
                        KEY(operator<) : OBJECT{
                                            KEY(numbers: 2 < 3.14) : NUMBER(2) < NUMBER(3.14),
                                            KEY(numbers: 3.14 < 2) : NUMBER(3.14) < NUMBER(2)
                        },
                        KEY(operator>) : OBJECT{
                                            KEY(numbers: 2 > 3.14) : NUMBER(2) > NUMBER(3.14),
                                            KEY(numbers: 3.14 > 2) : NUMBER(3.14) > NUMBER(2)
                        },
                        KEY(operator<=) : OBJECT{
                                            KEY(numbers: 2 <= 3.14) : NUMBER(2) <= NUMBER(3.14),
                                            KEY(numbers: 3.14 <= 2) : NUMBER(3.14) <= NUMBER(2),
                                            KEY(numbers: 3.14 <= 3.14) : NUMBER(3.14) <= NUMBER(3.14)
                        },
                        KEY(operator>=) : OBJECT{
                                            KEY(numbers: 2 >= 3.14) : NUMBER(2) >= NUMBER(3.14),
                                            KEY(numbers: 3.14 >= 2) : NUMBER(3.14) >= NUMBER(2),
                                            KEY(numbers: 3.14 >= 3.14) : NUMBER(3.14) >= NUMBER(3.14)
                        },
                        KEY(operator==) : OBJECT{
                                            KEY(numbers: 2 == 3.14) : NUMBER(2) == NUMBER(3.14),
                                            KEY(numbers: 3.14 == 3.14) : NUMBER(3.14) == NUMBER(3.14),
                                            KEY(strings: 'ok' == 'ko') : STRING("ok") == STRING("ko"),
                                            KEY(strings: 'ok' == 'ok') : STRING("ok") == STRING("ok"),
                                            KEY(booleans: true == true) : TRUE == TRUE,
                                            KEY(booleans: true == false) : TRUE == FALSE,
                                            //KEY(arrays: [2, 3.14] == [3, 2.72]) : ARRAY[NUMBER(2), NUMBER(3.14)] == ARRAY[NUMBER(3), NUMBER(2.72)],
                                            //KEY(objects: {'k1' : 3 } == {'k2' : "hellozz"}) : OBJECT{KEY(k1) :NUMBER(3) } == OBJECT{ KEY(k2) : STRING("hellozz")}
                        },
                        KEY(operator!=) : OBJECT{
                                            KEY(numbers: 2 != 3.14) : NUMBER(2) != NUMBER(3.14),
                                            KEY(numbers: 3.14 != 3.14) : NUMBER(3.14) != NUMBER(3.14),
                                            KEY(strings: 'ok' != 'ko') : STRING("ok") != STRING("ko"),
                                            KEY(strings: 'ok' == 'ok') : STRING("ok") != STRING("ok"),
                                            KEY(booleans: true != true) : TRUE != TRUE,
                                            KEY(booleans: true != false) : TRUE != FALSE,
                                            //KEY(arrays: [2, 3.14] != [3, 2.72]) : ARRAY[NUMBER(2), NUMBER(3.14)] != ARRAY[NUMBER(3), NUMBER(2.72)],
                                            //KEY(objects: {'k1' : 3 } != {'k2' : "hellozz"}) : OBJECT{KEY(k1) :NUMBER(3) } != OBJECT{ KEY(k2) : STRING("hellozz")}
                        },
                        KEY(operator!) : OBJECT{
                                            KEY(!TRUE) : !TRUE,
                                            KEY(!FALSE) : !FALSE
                        },
                        KEY(operator&&) : OBJECT{
                                            KEY(TRUE && FALSE) : TRUE && FALSE,
                                            KEY(TRUE && TRUE) : TRUE && TRUE
                        },
                        KEY(operator||) : OBJECT{
                                            KEY(TRUE || FALSE) : TRUE || FALSE,
                                            KEY(TRUE || TRUE) : TRUE || TRUE,
                                            KEY(FALSE || FALSE) : FALSE || FALSE
                        }
}


PRINT operators
PRINT "~.~.~.~.~.~.~.~ THAT'S ALL FOLKS! ~.~.~.~.~.~.~.~"

PROGRAM_END
