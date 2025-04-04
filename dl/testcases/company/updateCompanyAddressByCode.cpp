#include<iostream>
#include<dl/company>
#include<dl/companymanager>
using namespace invoicegenerator;
using namespace data_layer;
using namespace std;
int main()
{
Company company;
string password;
string street;
string city;
int pinCode;
string state;
string country;
string UPIID;
string GSTNumber;

cout<<"------------------Detail------------------"<<endl;
int code;
cout<<"Enter code: ";
cin>>code;
cin.ignore(1000,'\n');
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

company.setCode(code);
company.setPassword(password);
company.setStreet(street);
company.setCity(city);
company.setPinCode(pinCode);
company.setState(state);
company.setCountry(country);

CompanyManager companyManager;
try
{
companyManager.updateCompanyAddressByCode(&company);
cout<<"Company Address updated"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}