#include<iostream>
#include<dl/customer>
#include<dl/customermanager>
using namespace invoicegenerator;
using namespace data_layer;
using namespace std;
int main()
{
Customer customer;
string customerName;
string email;
string contactNumber;
string street;
string city;
int pinCode;
string state;
string country;

cout<<"------------------Detail------------------"<<endl;
cout<<"Enter Customer Name: ";
getline(cin,customerName);
 
int customerCode;
cout<<"Enter code: ";
cin>>customerCode;
cin.ignore(1000,'\n');

cout<<"Enter Email: ";
getline(cin,email);


cout<<"Enter Contact Number: ";
getline(cin,contactNumber);
 

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


customer.setCustomerCode(customerCode);
customer.setCustomerName(customerName);
customer.setEmail(email);
customer.setContactNumber(contactNumber);
customer.setStreet(street);
customer.setCity(city);
customer.setPinCode(pinCode);
customer.setState(state);
customer.setCountry(country);

CustomerManager customerManager;
try
{
customerManager.updateCustomer(&customer);
cout<<"Customer updated"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}