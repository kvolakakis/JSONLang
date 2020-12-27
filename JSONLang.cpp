#include "JSONLang.h"


PROGRAM_BEGIN

start();

JSON(temp_string) = STRING("first attempt");

cout << temp_string.getValue() << endl;

PROGRAM_END