#include<iostream>
#include<dl/adminmanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
string email;
string password;
cout<<"Enter email: ";
getline(cin,email);
cout<<"Enter password: ";
getline(cin,password);
AdminManager adminManager;
try
{
int verification=adminManager.verifyAdmin(email,password);
if(!verification) cout<<"Invalid email or password"<<endl;
else cout<<"Varification complete"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}