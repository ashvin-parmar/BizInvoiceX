#include<iostream>
#include<dl/company>
#include<dl/companymanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
Company company;
CompanyManager companyManager;
string email;
string password;
cout<<"Enter email: ";
getline(cin,email);
cout<<"Enter password: ";
getline(cin,password);
try
{
companyManager.removeCompany(email,password);
cout<<"Company removed"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}