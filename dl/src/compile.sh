#!/bin/bash
g++ -c *.cpp -I ../include -I ../../../tmcommon/include -I ../../../../sqlite3/include
ar rcs ../lib/libinvoicegenerator.a *.o

