#include<iostream>
#include<dl/customer>
#include<dl/customermanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
string email;
cout<<"Enter email: ";
getline(cin,email);
CustomerManager customerManager;
try
{
customerManager.showCustomerProfile(email);
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}