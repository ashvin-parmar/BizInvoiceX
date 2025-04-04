#include<stdio.h>
#include<dl/customer>
#include<dl/customermanager>
#include<dl/daoexception>
using namespace invoicegenerator;
using namespace data_layer;
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
customerManager.addCustomer(&customer);
cout<<"Customer added with code: "<<customer.getCustomerCode()<<endl;
cout<<"Remember this code for future reference."<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}