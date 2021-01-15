Meli omadas:
-Olga Dourountaki, AM: 3940, email: csd3940@csd.uoc.gr
-Konstantinos Volakakis, AM: 3923, email: csd3923@csd.uoc.gr

To paradoteo mas periexei ta eksis:
-JSONLang.h : header file pou periexei olh thn ylopoihsh twn apaithsewn tou project mas (main stuff)
-JSONLang.cpp: .ccp file to opoio periexei ola(sxedon) ta paradeigmata apo thn ekfwnhsh kai arketa dika mas (to ti DEN periexetai kai giati tha to deite parakatw) Epishs periexontai kapoia runtime errors ta opoia kanoume handle me error message kai termatismo, epomenws ta exoume se sxolia kai sthn ekestash an xreiastei ta testaroume kai auta.
-makefile: to gnwsto makefile :) (parakatw exoume leitourgia)

Sto makefile kanontas:
-make all : ginetai compile and run to project mas
-make compile: ginetai compile to project mas
-make execute: ekteleitai to project mas (arkei fysika na exei ginei prwta compile)
(An epithymeite wstoso xwris makefile kanoume compile me 'g++ JSONLang.cpp  -std=c++0x -o json'(to  -std=c++0x einai parametros pou xrhsimopoieitai gia na ektelestoun oi dynatothtes tou c++11) kai meta ektelesh klasika './json'(if run on Linux).)

Apo leitourgies exoume ylopoihsei ta panta ektos apo:
-APPEND gia multiple, comma separated values (douleuei mono gia ena value an kanoume APPEND)
-ARRAY + ARRAY / OBJECT + OBJECT einai ylopoihmeno se synarthseis, wstoso den mporei na elegxthei me ton tropo pou exume kanei define ta ARRAY kai OBJECT. To kaname pros to telos kai epomenws den emene polys xronos na diorthwsoume(ekshghseis sthn eksetash fysika).
-PRINT gia multiple, comma separated values (same as APPEND, fantazomai an lyname to ena problhma tha lynotan kai to allo). 

Parathrhseis:
-Kanontas redefine to keyword NULL, mas dhmiourgei ena warning, to opoio wstoso den prokalei kapoio problhma. Se aporia sth lista eipwthike oti den yparxei problhma.

P.S.:Sorry gia ta greeklish. Apla mesw turnin tis perissoteres fores yparxoun problhmata kwdikopoihshs.

  