g++ -c *.cpp -I ..\include -I ..\..\..\tmcommon\include -I e:\sqlite3\include
del ..\lib\invoicedl.lib
ar rcs ..\lib\invoicedl.lib *.o
cd..
cd..
cd pl\dlpl
cmp
