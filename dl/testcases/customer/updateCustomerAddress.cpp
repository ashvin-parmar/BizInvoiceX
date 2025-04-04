#include<iostream>
#include<dl/customer>
#include<dl/customermanager>
using namespace invoicegenerator;
using namespace data_layer;
using namespace std;
int main()
{
Customer customer;
string email;
string street;
string city;
int pinCode;
string state;
string country;
cout<<"Enter Email: ";
getline(cin,email);

cout<<"------------------Address------------------"<<endl;
cout<<"Enter Street: ";
getline(cin,street);
 
cout<<"Enter City: ";
getline(cin,city);
cout<<"Enter Pincode: ";
cin>>pinCode;
cin.ignore(100,'\n');

cout<<"Enter State: ";
getline(cin,state);
cout<<"Enter Country: ";
getline(cin,country);

customer.setEmail(email);
customer.setStreet(street);
customer.setCity(city);
customer.setPinCode(pinCode);
customer.setState(state);
customer.setCountry(country);

CustomerManager customerManager;
try
{
customerManager.updateCustomerAddressByEmail(&customer);
cout<<"Customer updated"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}