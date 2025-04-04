#include<dl/icustomer>
#include<dl/customer>
#include<dl/icustomermanager>
#include<dl/customermanager>
#include<dl/daoexception>
#include<dl/icompany>
#include<dl/company>
#include<dl/icompanymanager>
#include<dl/companymanager>
#include<fstream>
#include<string.h>
#include<common/stringutils>
using namespace stringutils;
using namespace invoicegenerator;
using namespace data_layer;
void CustomerManager::addCustomer(abc::ICustomer *customer) noexcept(false)
{
if(customer==NULL) throw DAOException("Required customer data, NULL encountered");
if(customer->getCustomerCode()!=0) throw DAOException("Required: Code should be zero");
const string vName=customer->getCustomerName();
string customerName=trimmed(vName);
if(customerName.size()==0) throw DAOException("Customer Name required, Name size zero");
if(customerName.size()>50) throw DAOException("Customer Name should not exeed 50 character");
string contactNumber=validateContactNumber(customer->getContactNumber());
if(contactNumber.size()==0) throw DAOException("Invalid contact number");

string companyEmail=validateEmail(customer->getCompanyEmail());
if(companyEmail.size()==0 || companyEmail.size()>80) throw DAOException("Invalid company email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");

string customerEmail=validateEmail(customer->getCustomerEmail());
if(customerEmail.size()==0 || customerEmail.size()>80) throw DAOException("Invalid customer email");
exist=companyManager.isCompanyWithEmailExist(customerEmail);
if(exist) throw DAOException("A Company with given email is already exist, use another email for customer use.");

string street=trimmed(customer->getStreet());
if(street.size()==0) throw DAOException("Please enter street address");
if(street.size()>50) throw DAOException("Street address can not exceed 50 character");
string city=trimmed(customer->getCity());
if(city.size()==0) throw DAOException("Please enter city address");
if(city.size()>50) throw DAOException("City address can not exceed 50 character");
string state=trimmed(customer->getState());
if(state.size()==0) throw DAOException("Please enter state address");
if(state.size()>50) throw DAOException("State address can not exceed 50 character");
string country=trimmed(customer->getCountry());
if(country.size()==0) throw DAOException("Please enter country address");
if(country.size()>50) throw DAOException("Country address can not exceed 50 character");
int pinCode=customer->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");
//Other All Type Of Validation	
CustomerManager::Header header;
_Customer _customer;
fstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
ofstream dFile(CUSTOMER_FILE_NAME,ios::app | ios::binary);
header.numberOfRecords=1;
header.lastGeneratedCustomerCode=1;
strcpy(_customer.customerName,customerName.c_str());
strcpy(_customer.customerEmail,customerEmail.c_str());
strcpy(_customer.companyEmail,companyEmail.c_str());
strcpy(_customer.contactNumber,contactNumber.c_str());
strcpy(_customer.street,street.c_str());
strcpy(_customer.city,city.c_str());
strcpy(_customer.state,state.c_str());
strcpy(_customer.country,country.c_str());
_customer.pinCode=pinCode;
_customer.customerCode=1;
dFile.write((char *)&header,sizeof(Header));
dFile.write((char *)&_customer,sizeof(_Customer));
dFile.close();
customer->setCustomerCode(header.lastGeneratedCustomerCode);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.seekp(0,ios::beg);
header.lastGeneratedCustomerCode=1;
header.numberOfRecords=1;
strcpy(_customer.customerName,customerName.c_str());
strcpy(_customer.customerEmail,customerEmail.c_str());
strcpy(_customer.companyEmail,companyEmail.c_str());
strcpy(_customer.contactNumber,contactNumber.c_str());
strcpy(_customer.street,street.c_str());
strcpy(_customer.city,city.c_str());
strcpy(_customer.state,state.c_str());
strcpy(_customer.country,country.c_str());
_customer.pinCode=pinCode;
_customer.customerCode=1;
dataFile.write((char *)&header,sizeof(Header));
dataFile.write((char *)&_customer,sizeof(_Customer));
dataFile.close();
customer->setCustomerCode(header.lastGeneratedCustomerCode);
return;
}
while(true)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.customerEmail,customerEmail.c_str())==0)
{
if(compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0)
{
dataFile.close();
throw DAOException(string("Customer already exist with email "+customerEmail));
}
}
if(compareStringIgnoreCase(_customer.contactNumber,contactNumber.c_str())==0)
{
if(compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0)
{
dataFile.close();
throw DAOException(string("Customer already exist with email "+customerEmail));
}
}
}
dataFile.clear();
header.lastGeneratedCustomerCode++;
header.numberOfRecords++;
strcpy(_customer.customerName,customerName.c_str());
strcpy(_customer.customerEmail,customerEmail.c_str());
strcpy(_customer.companyEmail,companyEmail.c_str());
strcpy(_customer.contactNumber,contactNumber.c_str());
strcpy(_customer.street,street.c_str());
strcpy(_customer.city,city.c_str());
strcpy(_customer.state,state.c_str());
strcpy(_customer.country,country.c_str());
_customer.pinCode=pinCode;
_customer.customerCode=header.lastGeneratedCustomerCode;
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_customer,sizeof(_Customer));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
customer->setCustomerCode(header.lastGeneratedCustomerCode);
}
void CustomerManager::updateCustomer(abc::ICustomer *customer) noexcept(false)
{
if(customer==NULL) throw DAOException("Required customer data, NULL encountered");
int customerCode=customer->getCustomerCode();
if(customerCode<=0) throw DAOException("Invalid customer code");
const string vName=customer->getCustomerName();
string customerName=trimmed(vName);
if(customerName.size()==0) throw DAOException("Customer name required, Name size zero");
if(customerName.size()>50) throw DAOException("Customer Name should not exeed 50 character");
string contactNumber=validateContactNumber(customer->getContactNumber());
if(contactNumber.size()==0) throw DAOException("Invalid contact number");
string companyEmail=validateEmail(customer->getCompanyEmail());
if(companyEmail.size()==0 || companyEmail.size()>80) throw DAOException("Invalid company email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");

string customerEmail=validateEmail(customer->getCustomerEmail());
if(customerEmail.size()==0 || customerEmail.size()>80) throw DAOException("Invalid customer email");
exist=companyManager.isCompanyWithEmailExist(customerEmail);
if(exist) throw DAOException("A Company with given email is already exist, use another email for customer use.");

string street=trimmed(customer->getStreet());
if(street.size()==0) throw DAOException("Please enter street address");
if(street.size()>50) throw DAOException("Street address can not exceed 50 character");
string city=trimmed(customer->getCity());
if(city.size()==0) throw DAOException("Please enter city address");
if(city.size()>50) throw DAOException("City address can not exceed 50 character");
string state=trimmed(customer->getState());
if(state.size()==0) throw DAOException("Please enter state address");
if(state.size()>50) throw DAOException("State address can not exceed 50 character");
string country=trimmed(customer->getCountry());
if(country.size()==0) throw DAOException("Please enter country address");
if(country.size()>50) throw DAOException("Country address can not exceed 50 character");
int pinCode=customer->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");
//Other All Type Of Validation
Header header;
_Customer _customer;
fstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid Customer code data");
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid customer code detail");
}
if(header.numberOfRecords==0 || customerCode>header.lastGeneratedCustomerCode)
{
dataFile.close();
throw DAOException("Invalid customer code detail");
}
int pos;
int found=0;
while(true)
{
pos=dataFile.tellg();
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(_customer.customerCode==customerCode)
{
found=1;
break;
}
}
if(!found)
{
dataFile.close();
throw DAOException("Customer with given code not found");
}
dataFile.clear();
dataFile.seekg(sizeof(Header),ios::beg);
while(true)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.customerEmail,customerEmail.c_str())==0 && _customer.customerCode!=customerCode && compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0)
{
dataFile.close();
throw DAOException(string("Customer already exist with email "+customerEmail));
}
if(compareStringIgnoreCase(_customer.contactNumber,contactNumber.c_str())==0 && _customer.customerCode!=customerCode && compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0)
{
dataFile.close();
throw DAOException(string("Customer already exist with contact number "+contactNumber));
}
}
dataFile.clear();
dataFile.seekp(pos,ios::beg);
strcpy(_customer.customerName,customerName.c_str());
strcpy(_customer.customerEmail,customerEmail.c_str());
strcpy(_customer.companyEmail,companyEmail.c_str());
strcpy(_customer.contactNumber,contactNumber.c_str());
strcpy(_customer.street,street.c_str());
strcpy(_customer.city,city.c_str());
strcpy(_customer.state,state.c_str());
strcpy(_customer.country,country.c_str());
_customer.pinCode=pinCode;
_customer.customerCode=customerCode;
dataFile.write((char *)&_customer,sizeof(_Customer));
dataFile.close();
}
void CustomerManager::updateCustomerAddressByEmail(abc::ICustomer *customer) noexcept(false)
{
string customerEmail=validateEmail(customer->getCustomerEmail());
if(customerEmail.size()==0 || customerEmail.size()>80) throw DAOException("Invalid customer email");

string companyEmail=validateEmail(customer->getCompanyEmail());
if(companyEmail.size()==0 || companyEmail.size()>80) throw DAOException("Invalid company email");

// done done: Later conveting password in hashing algoritm 
string street=trimmed(customer->getStreet());
if(street.size()==0) throw DAOException("Please enter street address");
if(street.size()>50) throw DAOException("Street address can not exceed 50 character");
string city=trimmed(customer->getCity());
if(city.size()==0) throw DAOException("Please enter city address");
if(city.size()>50) throw DAOException("City address can not exceed 50 character");
string state=trimmed(customer->getState());
if(state.size()==0) throw DAOException("Please enter state address");
if(state.size()>50) throw DAOException("State address can not exceed 50 character");
string country=trimmed(customer->getCountry());
if(country.size()==0) throw DAOException("Please enter country address");
if(country.size()>50) throw DAOException("Country address can not exceed 50 character");
int pinCode=customer->getPinCode();
if(pinCode>999999 || pinCode<100000) throw DAOException("Please enter correct Pin Code");
//Other All Type Of Validation
Header header;
_Customer _customer;
fstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid customer email id");
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid customer email id");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid customer email id");
}
int pos;
int found=0;
while(true)
{
pos=dataFile.tellg();
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.customerEmail,customerEmail.c_str())==0 && compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0)
{
found=1;
break;
}
}
if(!found)
{
dataFile.close();
throw DAOException("Invalid Email OR Company Email");
}
dataFile.clear();
dataFile.seekp(pos,ios::beg);
strcpy(_customer.street,street.c_str());
strcpy(_customer.city,city.c_str());
strcpy(_customer.state,state.c_str());
strcpy(_customer.country,country.c_str());
_customer.pinCode=pinCode;
dataFile.write((char *)&_customer,sizeof(_Customer));
dataFile.close();
}
void CustomerManager::removeCustomer(string &vCompanyEmail,string &vCustomerEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()==0) throw DAOException("Required email, email size cannot be zero");
if(companyEmail.size()>80) throw DAOException("Email size cannot exceed 80 characters");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");

string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()==0) throw DAOException("Required email, email size cannot be zero");
if(customerEmail.size()>80) throw DAOException("Email size cannot exceed 80 characters");

_Customer _customer;
Header header;
fstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException(string("Invalid email")+customerEmail);
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string("Invalid email")+customerEmail);
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException(string("Invalid email")+customerEmail);
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
header.numberOfRecords--;
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(!(compareStringIgnoreCase(_customer.customerEmail,customerEmail.c_str())==0 && compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0))
{
tmpFile.write((char *)&_customer,sizeof(_customer));
}
}
tmpFile.close();
dataFile.close();
tmpFile.clear();
dataFile.clear();
dataFile.open(CUSTOMER_FILE_NAME,ios::out | ios::binary);
tmpFile.open("tmp.tmp",ios::in | ios::binary);
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_customer,sizeof(_Customer));
if(tmpFile.fail()) break;
dataFile.write((char *)&_customer,sizeof(_Customer));
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
forward_list<abc::ICustomer *> * CustomerManager::getAllCustomer() noexcept(false)
{
Header header;
ifstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Customer does not exist");
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Customer does not exist");
}
if(header.numberOfRecords==0) 
{
dataFile.close();
throw DAOException("Customer does not exist");
}
_Customer _customer;
abc::ICustomer *customer;
forward_list<abc::ICustomer *> *customerList;
customerList=new forward_list<abc::ICustomer *>;
forward_list<abc::ICustomer *>::iterator listi=customerList->before_begin();
while(true)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
customer=new Customer;
customer->setCustomerName(string(_customer.customerName));
customer->setCustomerEmail(string(_customer.customerEmail));
customer->setCompanyEmail(string(_customer.companyEmail));
customer->setContactNumber(string(_customer.contactNumber));
customer->setStreet(string(_customer.street));
customer->setCity(string(_customer.city));
customer->setCountry(string(_customer.country));
customer->setState(string(_customer.state));
customer->setPinCode(_customer.pinCode);
customer->setCustomerCode(_customer.customerCode);
listi=customerList->insert_after(listi,customer);
}
dataFile.close();
return customerList;
}
abc::ICustomer * CustomerManager::getCustomerByEmail(string &vCompanyEmail,string &vCustomerEmail) noexcept(false)
{

string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()==0) throw DAOException("Required email, email size cannot be zero");
if(companyEmail.size()>80) throw DAOException("Email size cannot exceed 80 characters");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");

string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()==0) throw DAOException("Required email, email size cannot be zero");
if(customerEmail.size()>80) throw DAOException("Email size cannot exceed 80 characters");

ifstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Invalid customer email");
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Invalid customer email");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid customer email");
}
_Customer _customer;
abc::ICustomer *customer;
while(1)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.customerEmail,customerEmail.c_str())==0 && compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0)
{
customer=new Customer;
customer->setCustomerName(string(_customer.customerName));
customer->setCustomerEmail(string(_customer.customerEmail));
customer->setCompanyEmail(string(_customer.companyEmail));
customer->setContactNumber(string(_customer.contactNumber));
customer->setStreet(string(_customer.street));
customer->setCity(string(_customer.city));
customer->setCountry(string(_customer.country));
customer->setState(string(_customer.state));
customer->setPinCode(_customer.pinCode);
customer->setCustomerCode(_customer.customerCode);
dataFile.close();
return customer;
}
}
dataFile.close();
throw DAOException("Invalid email");
}
int CustomerManager::isCustomerWithEmailExist(const string &vCompanyEmail,const string &vCustomerEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()==0) return 0;
if(companyEmail.size()>80) return 0;
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) return 0;

string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()==0)return 0;
if(customerEmail.size()>80) return 0;

ifstream dataFile(CUSTOMER_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) return 0;
Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
return 0;
}
if(header.numberOfRecords==0)
{
dataFile.close();
return 0;
}
_Customer _customer;
abc::ICustomer *customer;
while(1)
{
dataFile.read((char *)&_customer,sizeof(_Customer));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_customer.customerEmail,customerEmail.c_str())==0 && compareStringIgnoreCase(_customer.companyEmail,companyEmail.c_str())==0)
{
dataFile.close();
return 1;
}
}
dataFile.close();
return 0;
}
void CustomerManager::showCustomerProfile(const string &vCompanyEmail,const string &vCustomerEmail) noexcept(false)
{
CustomerManager customerManager;
abc::ICustomer *customer;
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()==0) throw DAOException("Required email, email size cannot be zero");
if(companyEmail.size()>80) throw DAOException("Email size cannot exceed 80 characters");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");
string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()==0) throw DAOException("Required email, email size cannot be zero");
if(customerEmail.size()>80) throw DAOException("Email size cannot exceed 80 characters");
try
{
customer=customerManager.getCustomerByEmail(companyEmail,customerEmail);
}catch(DAOException daoException)
{
throw DAOException(daoException.what());
}
cout<<"                           ----------Customer Details----------"<<endl;
printf("Customer Name: %-80s    Customer Code: %-15d\n",customer->getCustomerName().c_str(),customer->getCustomerCode());
printf("Email: %-80s           Contact Number: %-15s\n\n",customer->getCustomerEmail().c_str(),customer->getContactNumber().c_str());

cout<<"                           ----------Customer Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",customer->getStreet().c_str(),customer->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",customer->getState().c_str(),customer->getCountry().c_str());
printf("Pin Code: %-15d\n\n",customer->getPinCode());

cout<<endl;
delete customer;
}