#include<iostream>
#include<dl/icustomer>
#include<dl/customer>
using namespace invoicegenerator;
using namespace data_layer;
using namespace std;
Customer::Customer()
{
this->customerCode=0;
this->customerName="";
this->contactNumber="";
this->customerEmail="";
this->companyEmail="";
this->street="";
this->city="";
this->state="";
this->country="";
this->pinCode=0;
}
Customer::Customer(const Customer &other)
{
this->customerCode=other.customerCode;
this->customerName=other.customerName;
this->contactNumber=other.contactNumber;
this->customerEmail=other.customerEmail;
this->companyEmail=other.companyEmail;
this->street=other.street;
this->city=other.city;
this->state=other.state;
this->country=other.country;
this->pinCode=other.pinCode;
}
Customer::~Customer()
{
// For now do nothing
}
void Customer::setCustomerCode(int customerCode)
{
this->customerCode=customerCode;
}
void Customer::setCustomerName(string customerName)
{
this->customerName=customerName;
}
void Customer::setContactNumber(string contactNumber)
{
this->contactNumber=contactNumber;
}
void Customer::setCustomerEmail(string customerEmail)
{
this->customerEmail=customerEmail;
}
void Customer::setCompanyEmail(string companyEmail)
{
this->companyEmail=companyEmail;
}
void Customer::setStreet(string street)
{
this->street=street;
}
void Customer::setCity(string city)
{
this->city=city;
}
void Customer::setState(string state)
{
this->state=state;
}
void Customer::setCountry(string country)
{
this->country=country;
}
void Customer::setPinCode(int pinCode)
{
this->pinCode=pinCode;
}
int Customer::getCustomerCode() const
{
return this->customerCode;
}
string Customer::getCustomerName() const
{
return this->customerName;
}
string Customer::getStreet() const
{
return this->street;
}
string Customer::getCity() const
{
return this->city;
}
string Customer::getState() const
{
return this->state;
}
string Customer::getCustomerEmail() const
{
return this->customerEmail;
}
string Customer::getCompanyEmail() const
{
return this->companyEmail;
}
string Customer::getContactNumber() const
{
return this->contactNumber;
}
string Customer::getCountry() const
{
return this->country;
}
int Customer::getPinCode() const
{
return this->pinCode;
}
abc::ICustomer & Customer::operator=(const abc::ICustomer &other)
{
this->customerCode=other.getCustomerCode();
this->customerName=other.getCustomerName();
this->contactNumber=other.getContactNumber();
this->customerEmail=other.getCustomerEmail();
this->companyEmail=other.getCompanyEmail();
this->street=other.getStreet();
this->city=other.getCity();
this->state=other.getState();
this->country=other.getCountry();
this->pinCode=other.getPinCode();
return *this;
}
int Customer::operator==(const abc::ICustomer &other)
{
return this->customerCode==other.getCustomerCode();
}
int Customer::operator<=(const abc::ICustomer &other)
{
return this->customerCode<=other.getCustomerCode();
}
int Customer::operator>=(const abc::ICustomer &other)
{
return this->customerCode>=other.getCustomerCode();
}
int Customer::operator!=(const abc::ICustomer &other)
{
return this->customerCode!=other.getCustomerCode();
}
int Customer::operator<(const abc::ICustomer &other)
{
return this->customerCode<other.getCustomerCode();
}
int Customer::operator>(const abc::ICustomer &other)
{
return this->customerCode>other.getCustomerCode();
}