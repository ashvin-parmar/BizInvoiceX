#include<iostream>
#include<dl/company>
#include<dl/companymanager>
using namespace invoicegenerator;
using namespace data_layer;
using namespace std;
int main()
{
Company company;
string name;
string email;
string contactNumber;
string password;
string street;
string city;
int pinCode;
string state;
string country;
string UPIID;
string GSTNumber;

cout<<"------------------Detail------------------"<<endl;
cout<<"Enter Company Name: ";
getline(cin,name);
 
cout<<"Enter Email: ";
getline(cin,email);

int code;
cout<<"Enter code: ";
cin>>code;
cin.ignore(1000,'\n');

cout<<"Enter Contact Number: ";
getline(cin,contactNumber);
cout<<"Contact Number: "<<contactNumber<<endl; 
cout<<"Enter Password: ";
getline(cin,password);
 

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

cout<<"------------------Banking------------------"<<endl;
cout<<"Enter UPI ID: ";
getline(cin,UPIID);
cout<<"Enter GST Number: ";
getline(cin,GSTNumber);

company.setCode(code);
company.setName(name);
company.setEmail(email);
company.setContactNumber(contactNumber);
company.setPassword(password);
company.setStreet(street);
company.setCity(city);
company.setPinCode(pinCode);
company.setState(state);
company.setCountry(country);
company.setUPIID(UPIID);
company.setGSTNumber(GSTNumber);

CompanyManager companyManager;
try
{
companyManager.updateCompany(&company);
cout<<"Company updated"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}