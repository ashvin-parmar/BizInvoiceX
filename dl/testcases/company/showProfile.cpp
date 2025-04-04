#include<iostream>
#include<dl/company>
#include<dl/companymanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
string email;
cout<<"Enter email: ";
getline(cin,email);
CompanyManager companyManager;
try
{
companyManager.showProfile(email);
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}