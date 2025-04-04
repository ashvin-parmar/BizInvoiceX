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
string newPassword;
string previousPassword;
cout<<"Enter email: ";
getline(cin,email);
cout<<"Enter previous password: ";
getline(cin,previousPassword);
cout<<"Enter new password: ";
getline(cin,newPassword);
try
{
companyManager.resetPassword(email,previousPassword,newPassword);
cout<<"Password reset successfully"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}