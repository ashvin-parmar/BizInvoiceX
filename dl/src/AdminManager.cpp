#include<iostream>
#include<dl/adminmanager>
#include<common/stringutils>
#include<string.h>
#include<dl/daoexception>
#include<sqlite3.h>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
using namespace stringutils;
int AdminManager::verification(const string vEmail,const string vPassword) noexcept(false)
{
string email=trimmed(vEmail);
string password=trimmed(vPassword);
int size;
if((size=email.size())<=0 || size>80) throw DAOException("Incorrect Email");
if((size=password.size())<=0 || size>80) throw DAOException("Incorrect Password");
sqlite3 *db;
int resultCode;
resultCode=sqlite3_open(ADMIN_FILE_NAME.c_str(),&db);
if(resultCode!=SQLITE_OK)
{
sqlite3_close(db);
throw DAOException("Invalid Admin email or password");
}
char sql[1000];
sprintf(sql,"select email,password from admin where UPPER(email)=UPPER('%s');",email.c_str());
sqlite3_stmt *stmt;
resultCode=sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
if(resultCode!=SQLITE_OK)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Invalid Admin email or password");
}
resultCode=sqlite3_step(stmt);
if(resultCode!=SQLITE_ROW)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Invalid Admin email or password");
}
if(compareStringIgnoreCase(reinterpret_cast<const char *>(sqlite3_column_text(stmt,0)),email.c_str())!=0)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Invalid email");
}
if(compareStringIgnoreCase(reinterpret_cast<const char *>(sqlite3_column_text(stmt,1)),password.c_str())!=0)
{
sqlite3_finalize(stmt);
sqlite3_close(db);
throw DAOException("Invalid password");
}
sqlite3_finalize(stmt);
sqlite3_close(db);
return 1;
}

