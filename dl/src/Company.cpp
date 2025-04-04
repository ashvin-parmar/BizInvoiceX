#include<iostream>
#include<dl/icompany>
#include<dl/company>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
Company::Company()
{
this->code=0;
this->name="";
this->email="";
this->contactNumber="";
this->street="";
this->state="";
this->country="";
this->UPIID="";
this->city="";
this->GSTNumber="";
this->pinCode=0;
this->password="";
}
Company::Company(const Company &other)
{
this->name=other.name;
this->email=other.email;
this->contactNumber=other.contactNumber;
this->street=other.street;
this->state=other.state;
this->country=other.country;
this->code=other.code;
this->UPIID=other.UPIID;
this->city=other.city;
this->GSTNumber=other.GSTNumber;
this->pinCode=other.pinCode;
this->password=other.password;
}
Company::Company(string email,string password)
{
this->email=email;
this->password=password;
}
Company::~Company()
{
//Nothing to do
}
void Company::setName(string name)
{
this->name=name;
}
void Company::setStreet(string street)
{
this->street=street;
}
void Company::setCity(string city)
{
this->city=city;
}
void Company::setState(string state)
{
this->state=state;
}
void Company::setPinCode(int pinCode)
{
this->pinCode=pinCode;
}
void Company::setContactNumber(string contactNumber)
{
this->contactNumber=contactNumber;
}
void Company::setEmail(string email)
{
this->email=email;
}
void Company::setGSTNumber(string gstNumber)
{
this->GSTNumber=gstNumber;
}
void Company::setUPIID(string UPIID)
{
this->UPIID=UPIID;
}
void Company::setPassword(string password)
{
this->password=password;	//Increption applied after learning increption process
}
void Company::setCountry(string country)
{
this->country=country;
}
string Company::getCountry() const
{
return this->country;
}
string Company::getName() const
{
return this->name;
}
string Company::getStreet() const
{
return this->street;
}
string Company::getCity() const 
{
return this->city;
}
int Company::getPinCode() const
{
return this->pinCode;
}
string Company::getState() const
{
return this->state;
}
string Company::getEmail() const
{
return this->email;
}
string Company::getContactNumber() const
{
return this->contactNumber;
}
string Company::getGSTNumber() const
{
return this->GSTNumber;
}
void Company::setCode(int code)
{
this->code=code;
}
string Company::getUPIID() const
{
return this->UPIID;
}
int Company::getCode() const
{
return this->code;
}
string Company::getPassword() const
{
return this->password;
}
abc::ICompany & Company::operator=(const abc::ICompany &other)
{
this->name=other.getName();
this->email=other.getEmail();
this->contactNumber=other.getContactNumber();
this->street=other.getStreet();
this->state=other.getState();
this->code=other.getCode();
this->city=other.getCity();
this->GSTNumber=other.getGSTNumber();
this->UPIID=other.getUPIID();
this->country=other.getCountry();
this->pinCode=other.getPinCode();
this->password=other.getPassword();
return *this;
}
int Company::operator==(const abc::ICompany &other)
{
return this->code==other.getCode();
}
int Company::operator<=(const abc::ICompany &other)
{
return this->code<=other.getCode();
}
int Company::operator>=(const abc::ICompany &other)
{
return this->code>=other.getCode();
}
int Company::operator!=(const abc::ICompany &other)
{
return this->code!=other.getCode();
}
int Company::operator<(const abc::ICompany &other)
{
return this->code<other.getCode();
}
int Company::operator>(const abc::ICompany &other)
{
return this->code>other.getCode();
}
