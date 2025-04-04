#include<iostream>
#include<dl/adminmanager>
#include<dl/company>
#include<dl/companymanager>
#include<dl/customer>
#include<dl/customermanager>
#include<dl/invoice>
#include<dl/invoicemanager>
#include<dl/daoexception>
#include<cmath>
#include<iomanip>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
void getLine(int size,char m)
{
for(int i=0;i<size;i++) cout<<m;
cout<<endl;
}
void addCompany()
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
cout<<"------------------Banking & GST------------------"<<endl;
cout<<"Enter UPI ID: ";
getline(cin,UPIID);
cout<<"Enter GST Number: ";
getline(cin,GSTNumber);
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
companyManager.addCompany(&company);
cout<<"Company added with code: "<<company.getCode()<<endl;
cout<<"Remember this code for future reference."<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void editCompany()
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
int code;
cout<<"Enter code: ";
cin>>code;
cin.ignore(1000,'\n');

cout<<"Enter Company Name: ";
getline(cin,name);
cout<<"Enter Email: ";
getline(cin,email);
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
}
void removeCompany()
{
Company company;
CompanyManager companyManager;
string email;
string password;
cout<<"Enter email: ";
getline(cin,email);
cout<<"Enter password: ";
getline(cin,password);
try
{
companyManager.removeCompany(email,password);
cout<<"Company removed"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}

}
void viewCompany()
{
cout<<"Functionality not written yet, To be implement"<<endl;
}
void getAllCompany()
{
CompanyManager companyManager;
abc::ICompany *company;
forward_list<abc::ICompany *> *companyList;
forward_list<abc::ICompany *>::iterator i;
try
{
companyList=companyManager.getAllCompany();
getLine(140,'_');
cout<<"List of all Company with thier details"<<endl;
getLine(140,'_');
for(i=companyList->begin();i!=companyList->end();++i)
{
company=*i;
cout<<"----------Company Login Details----------"<<endl;
printf("Company Name: %-80s    Company Code: %-15d\n",company->getName().c_str(),company->getCode());
printf("Email: %-80s           Contact Number: %-15s\n\n",company->getEmail().c_str(),company->getContactNumber().c_str());

cout<<"----------Company Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",company->getStreet().c_str(),company->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",company->getState().c_str(),company->getCountry().c_str());
printf("Pin Code: %-15d\n\n",company->getPinCode());

cout<<"----------Bank Detail----------"<<endl;
printf("GST Number: %-50s UPIID: %-50s\n",company->getGSTNumber().c_str(),company->getUPIID().c_str());
getLine(140,'_');
cout<<endl;
getLine(140,'_');
delete company;
}
companyList->clear();
delete companyList;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void getCompany()
{
CompanyManager companyManager;
abc::ICompany *company;
cout<<"Enter email: ";
string email;
getline(cin,email);
try
{
company=companyManager.getCompanyByEmail(email);
getLine(140,'_');
cout<<"----------Company Login Details----------"<<endl;
printf("Company Name: %-80s    Company Code: %-15d\n",company->getName().c_str(),company->getCode());
printf("Email: %-80s           Contact Number: %-15s\n\n",company->getEmail().c_str(),company->getContactNumber().c_str());
cout<<"----------Company Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",company->getStreet().c_str(),company->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",company->getState().c_str(),company->getCountry().c_str());
printf("Pin Code: %-15d\n\n",company->getPinCode());
cout<<"----------Bank Detail----------"<<endl;
printf("GST Number: %-50s UPIID: %-50s\n",company->getGSTNumber().c_str(),company->getUPIID().c_str());
getLine(140,'_');
cout<<endl;
delete company;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}

}
void resetPasswordFree()
{
cout<<"Functionality not written yet, To be implement"<<endl;
}
void getAllInvoice()
{
InvoiceManager invoiceManager;
CustomerManager customerManager;
CompanyManager companyManager;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IInvoice *> *invoiceList;
forward_list<abc::IItem *> *itemList;
forward_list<abc::IInvoice *>::iterator invoiceListIterator;
forward_list<abc::IItem *>::iterator itemListIterator;
try
{
invoiceList=invoiceManager.getAllInvoice();
getLine(140,'_');
cout<<"List of all Invoice with thier details"<<endl;
getLine(140,'_');
for(invoiceListIterator=invoiceList->begin();invoiceListIterator!=invoiceList->end();++invoiceListIterator)
{
invoice=*invoiceListIterator;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
companyManager.showProfile(invoice->getCompanyEmail());
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
customerManager.showCustomerProfile(invoice->getCompanyEmail(),invoice->getCustomerEmail());
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
time_t t;
t=invoice->getDate();
struct tm *now;
now=localtime(&t);
char date[10];
//sprintf(date,"%d-%d-%d\n",now->tm_mday,now->tm_mon+1,now->tm_year+1900);
cout<<"Invoice Code: "<<invoice->getInvoiceCode()<<"                Date: "<<date<<endl;

itemList=invoice->getItemList();
cout<<"--------------------------------------------------------Item List-----------------------------------------------"<<endl;
char sentence[1000];
sprintf(sentence,"| %-5s | %-50s | %-10s | %-10s | %-10s | %-15s |\n","S.No","Item Name","Item Code","Quantity","Price","Total Price");
cout<<sentence;
int x=1;
double totalPrice=0;
double totalAmount=0;
for(itemListIterator=itemList->begin();itemListIterator!=itemList->end();itemListIterator++,x++)
{
item=*itemListIterator;
totalPrice=item->getNetRate()*item->getQuantity();
totalAmount+=totalPrice;
sprintf(sentence,"| %-5d | %-50s | %-10d | %-10d | %-10.2lf | %-15.2lf |\n",x,item->getItemName().c_str(),item->getItemCode(),item->getQuantity(),item->getNetRate(),totalPrice);
cout<<sentence;
delete item;
}
itemList->clear();
delete itemList;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Total Amount: "<<totalAmount<<endl;
double taxAmount=totalAmount*invoice->getTax();
cout<<"Tax Applied: "<<invoice->getTax()*100<<" Percent                  Tax Amount: "<<taxAmount<<endl;
double discountAmount=totalAmount*invoice->getDiscount();
cout<<"Discount applied: "<<invoice->getDiscount()*100<<" Percent              Discount Amount: "<<discountAmount<<endl;
cout<<"Final Amount: "<<totalAmount+taxAmount-discountAmount<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Amount paid: "<<invoice->getAmountPaid()<<endl;
cout<<"Amount Due: "<<invoice->getAmountDue()<<endl;
getLine(140,'_');
delete invoice;
}
invoiceList->clear();
delete invoiceList;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void editCompanyAddress(string &email)
{
abc::ICompany *company2;
Company company;
int code;
string password;
string street;
string city;
int pinCode;
string state;
string country;
string UPIID;
string GSTNumber;
CompanyManager companyManager;
try
{
company2=companyManager.getCompanyByEmail(email);
code=company2->getCode();
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
return ;
}
cout<<"------------------Detail------------------"<<endl;
cout<<"Enter Password: ";
getline(cin,password);
 

cout<<"------------------Address------------------"<<endl;
cout<<"Enter Street: ";
getline(cin,street);
 
cout<<"Enter City: ";
getline(cin,city);
cout<<"Enter State: ";
getline(cin,state);
cout<<"Enter Country: ";
getline(cin,country);
cout<<"Enter Pincode: ";
cin>>pinCode;
cin.ignore(100,'\n');

company.setCode(code);
company.setPassword(password);
company.setStreet(street);
company.setCity(city);
company.setPinCode(pinCode);
company.setState(state);
company.setCountry(country);
try
{
companyManager.updateCompanyAddressByCode(&company);
cout<<"Company Address updated"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void showCompanyProfile(string email)
{
CompanyManager companyManager;
companyManager.showProfile(email);
}
void addCustomer(string &companyEmail)
{
Customer customer;
string customerName;
string customerEmail;
string contactNumber;
string street;
string city;
int pinCode;
string state;
string country;

cout<<"------------------Detail------------------"<<endl;
cout<<"Enter Customer Name: ";
getline(cin,customerName);
 
cout<<"Enter Customer Email: ";
getline(cin,customerEmail);
 
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
customer.setCompanyEmail(companyEmail);
customer.setCustomerName(customerName);
customer.setCustomerEmail(customerEmail);
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
}
void editCustomer(string &companyEmail)
{
Customer customer;
string customerName;
string customerEmail;
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

cout<<"Enter Customer Email: ";
getline(cin,customerEmail);


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
customer.setCustomerEmail(customerEmail);
customer.setCompanyEmail(companyEmail);
customer.setContactNumber(contactNumber);
customer.setStreet(street);
customer.setCity(city);
customer.setPinCode(pinCode);
customer.setState(state);
customer.setCountry(country);

CustomerManager customerManager;
customerManager.updateCustomer(&customer);
cout<<"Customer updated"<<endl;
}
void editCustomerAddress(string &companyEmail)
{
Customer customer;
string customerEmail;
string street;
string city;
int pinCode;
string state;
string country;
cout<<"Enter Customer Email: ";
getline(cin,customerEmail);

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

customer.setCompanyEmail(companyEmail);
customer.setCustomerEmail(customerEmail);
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
}
void removeCustomer(string &companyEmail)
{
Customer customer;
CustomerManager customerManager;
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);
try
{
customerManager.removeCustomer(companyEmail,customerEmail);
cout<<"Customer removed"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void viewCustomer(string &companyEmail)
{
cout<<"To be implement"<<endl;
}
void getAllCustomersOfCompany(string &companyEmail)	//To be done later
{
cout<<"To be implement"<<endl;
}
void getAllCustomers()			
{
CustomerManager customerManager;
abc::ICustomer *customer;
forward_list<abc::ICustomer *> *customerList;
forward_list<abc::ICustomer *>::iterator i;
try
{
customerList=customerManager.getAllCustomer();
getLine(140,'_');
cout<<"List of all Customer with thier details"<<endl;
getLine(140,'_');
for(i=customerList->begin();i!=customerList->end();++i)
{
customer=*i;
cout<<"----------Customer Login Details----------"<<endl;
printf("Customer Name: %-80s    Customer Code: %-15d\n",customer->getCustomerName().c_str(),customer->getCustomerCode());
printf("Customer Email: %-80s           Contact Number: %-15s\n\n",customer->getCustomerEmail().c_str(),customer->getContactNumber().c_str());

cout<<"----------Customer Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",customer->getStreet().c_str(),customer->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",customer->getState().c_str(),customer->getCountry().c_str());
printf("Pin Code: %-15d\n\n",customer->getPinCode());

getLine(140,'_');
cout<<endl;
getLine(140,'_');
delete customer;
}
customerList->clear();
delete customerList;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void getCustomer(string &companyEmail)
{
abc::ICustomer *customer;
CustomerManager customerManager;
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);
try
{
customer=customerManager.getCustomerByEmail(companyEmail,customerEmail);
cout<<"----------Customer Login Details----------"<<endl;
printf("Customer Name: %-80s    Customer Code: %-15d\n",customer->getCustomerName().c_str(),customer->getCustomerCode());
printf("Customer Email: %-80s           Contact Number: %-15s\n\n",customer->getCustomerEmail().c_str(),customer->getContactNumber().c_str());

cout<<"----------Customer Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",customer->getStreet().c_str(),customer->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",customer->getState().c_str(),customer->getCountry().c_str());
printf("Pin Code: %-15d\n\n",customer->getPinCode());
getLine(140,'_');
cout<<endl;
getLine(140,'_');
delete customer;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void getAllCustomerInvoice(string &companyEmail)
{
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);
InvoiceManager invoiceManager;
CustomerManager customerManager;
CompanyManager companyManager;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IInvoice *> *invoiceList;
forward_list<abc::IItem *> *itemList;
forward_list<abc::IInvoice *>::iterator invoiceListIterator;
forward_list<abc::IItem *>::iterator itemListIterator;
try
{
invoiceList=invoiceManager.getInvoiceByCustomerEmail(companyEmail,customerEmail);
getLine(140,'_');

cout<<"List of All Invoices of Customer with email "<<customerEmail<<endl;
getLine(140,'_');
companyManager.showProfile(invoice->getCompanyEmail());
getLine(140,'_');
customerManager.showCustomerProfile(companyEmail,customerEmail);
getLine(140,'_');
invoiceListIterator=invoiceList->begin();
if(invoiceListIterator==invoiceList->end())
{
invoiceList->clear();
delete invoiceList;
cout<<"Customer has zero invoice"<<endl;
getLine(140,'_');
return ;
}
for(;invoiceListIterator!=invoiceList->end();++invoiceListIterator)
{
invoice=*invoiceListIterator;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
time_t t;
t=invoice->getDate();
struct tm *now;
now=localtime(&t);
char date[10];
//sprintf(date,"%d-%d-%d\n",now->tm_mday,now->tm_mon+1,now->tm_year+1900);
cout<<"Invoice Code: "<<invoice->getInvoiceCode()<<"                Date: "<<date<<endl;

itemList=invoice->getItemList();
cout<<"--------------------------------------------------------Item List-----------------------------------------------"<<endl;
char sentence[1000];
sprintf(sentence,"| %-5s | %-50s | %-10s | %-10s | %-10s | %-15s |\n","S.No","Item Name","Item Code","Quantity","Price","Total Price");
cout<<sentence;
int x=1;
double totalPrice=0;
double totalAmount=0;
for(itemListIterator=itemList->begin();itemListIterator!=itemList->end();itemListIterator++,x++)
{
item=*itemListIterator;
totalPrice=item->getNetRate()*item->getQuantity();
totalAmount+=totalPrice;
sprintf(sentence,"| %-5d | %-50s | %-10d | %-10d | %-10.2lf | %-15.2lf |\n",x,item->getItemName().c_str(),item->getItemCode(),item->getQuantity(),item->getNetRate(),totalPrice);
cout<<sentence;
delete item;
}
itemList->clear();
delete itemList;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Total Amount: "<<totalAmount<<endl;
double taxAmount=totalAmount*invoice->getTax();
cout<<"Tax Applied: "<<invoice->getTax()*100<<" Percent                  Tax Amount: "<<taxAmount<<endl;
double discountAmount=totalAmount*invoice->getDiscount();
cout<<"Discount applied: "<<invoice->getDiscount()*100<<" Percent              Discount Amount: "<<discountAmount<<endl;
cout<<"Final Amount: "<<totalAmount+taxAmount-discountAmount<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Amount paid: "<<invoice->getAmountPaid()<<endl;
cout<<"Amount Due: "<<invoice->getAmountDue()<<endl;
getLine(140,'_');
delete invoice;
}
invoiceList->clear();
delete invoiceList;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void RemoveCustomerInvoice(string &companyEmail)
{
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);
InvoiceManager invoiceManager;
try
{
invoiceManager.removeInvoiceByCustomerEmail(companyEmail,customerEmail);
cout<<"All invoice of customer with email "<<customerEmail<<" are removed"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void removeInvoiceByInvoiceCode()
{
int invoiceCode;
cout<<"Enter invoice code: ";
cin>>invoiceCode;
cin.ignore(2000,'\n');
InvoiceManager invoiceManager;
try
{
invoiceManager.removeInvoiceByInvoiceCode(invoiceCode);
cout<<"Invoice removed with invoice code "<<invoiceCode<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void isCustomerInvoiceExist(string &companyEmail)
{
InvoiceManager invoiceManager;
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);

int exist;
try
{
exist=invoiceManager.isInvoiceWithCustomerEmailExist(companyEmail,customerEmail);
if(exist) cout<<"Invoice with given customer email are exist"<<endl;
else cout<<"Invoice with given customer email are not exist"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void isInvoiceCodeExist()
{
InvoiceManager invoiceManager;
int invoiceCode;
cout<<"Enter invoice code: ";
cin>>invoiceCode;
cin.ignore(1000,'\n');
int exist;
try
{
exist=invoiceManager.isInvoiceWithInvoiceCodeExist(invoiceCode);
if(exist) cout<<"Invoice with given invoice code are exist"<<endl;
else cout<<"Invoice with given invoice code are not exist"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void createInvoice(string &companyEmail)
{
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);
abc::IItem *item;
string itemName;
int itemCode;
int quantity;
double netRate;
forward_list<abc::IItem *> list;
forward_list<abc::IItem *>::iterator i=list.before_begin();
char m;
double totalAmount=0;
while(1)
{
cout<<"Enter item name: ";
getline(cin,itemName);
cout<<"Enter item code: ";
cin>>itemCode;
cin.ignore(1000,'\n');
cout<<"Enter quantity: ";
cin>>quantity;
cin.ignore(1000,'\n');
cout<<"Enter net rate: ";
cin>>netRate;
cin.ignore(1000,'\n');
item=new Item;
item->setItemName(itemName);
item->setItemCode(itemCode);
item->setQuantity(quantity);
item->setNetRate(netRate);
i=list.insert_after(i,item);
totalAmount+=quantity*netRate;
cout<<"More item to add in cart (Y/N): ";
cin>>m;
cin.ignore(1000,'\n');
if(m!='Y' && m!='y') break;
}
double tax;
cout<<"Enter tax(Enter '0' for default): ";
cin>>tax;
cin.ignore(1000,'\n');

double discount;
cout<<"Enter discount(Enter '0' for default): ";
cin>>discount;
cin.ignore(1000,'\n');

Invoice invoice;
invoice.setCompanyEmail(companyEmail);
invoice.setCustomerEmail(customerEmail);
invoice.setTax(tax);
invoice.setDiscount(discount);
invoice.setItemList(list);

if(tax<=0) tax=TAX_DEFAULT;
if(discount<=0) discount=DISCOUNT_DEFAULT;

cout<<"Total Amount: "<<totalAmount<<endl;
double taxAmount=totalAmount*tax;
cout<<"Tax Applied: "<<tax*100<<" Percent                  Tax Amount: "<<taxAmount<<endl;
double discountAmount=totalAmount*discount;
cout<<"Discount applied: "<<discount*100<<" Percent              Discount Amount: "<<discountAmount<<endl;
totalAmount=(totalAmount+taxAmount-discountAmount);
totalAmount=round(totalAmount*100.0)/100.0;

cout<<"Final Amount: "<<totalAmount<<endl;

double amountPaid;
cout<<"Enter amount paid: ";
cin>>amountPaid;
cin.ignore(1000,'\n');

invoice.setAmountPaid(amountPaid);

InvoiceManager invoiceManager;
try
{
invoiceManager.addInvoice(&invoice);
cout<<"Invoice added"<<endl;
cout<<"Invoice Code: "<<invoice.getInvoiceCode()<<endl;
cout<<"Amount due: "<<invoice.getAmountDue()<<endl;
cout<<"Remember this invoice code for future references"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
for(i=list.begin();i!=list.end();i++) delete (*i);
list.clear();
}
void editInvoice()
{
int invoiceCode;
cout<<"Enter invoice code: ";
cin>>invoiceCode;
cin.ignore(1000,'\n');

cout<<"InvoiceCOde: "<<invoiceCode<<endl;
string companyEmail;
cout<<"Enter company email: ";
getline(cin,companyEmail);

string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);
abc::IItem *item;
string itemName;
int itemCode;
int quantity;
double netRate;
forward_list<abc::IItem *> list;
forward_list<abc::IItem *>::iterator i=list.before_begin();
char m;
double totalAmount=0;
while(1)
{
cout<<"Enter item name: ";
getline(cin,itemName);
cout<<"Enter item code: ";
cin>>itemCode;
cin.ignore(1000,'\n');
cout<<"Enter quantity: ";
cin>>quantity;
cin.ignore(1000,'\n');
cout<<"Enter net rate: ";
cin>>netRate;
cin.ignore(1000,'\n');
item=new Item;
item->setItemName(itemName);
item->setItemCode(itemCode);
item->setQuantity(quantity);
item->setNetRate(netRate);
i=list.insert_after(i,item);
totalAmount+=quantity*netRate;
cout<<"More item to add in cart (Y/N): ";
cin>>m;
cin.ignore(1000,'\n');
if(m!='Y' && m!='y') break;
}
double tax;
cout<<"Enter tax(Enter '0' for default): ";
cin>>tax;
cin.ignore(1000,'\n');

double discount;
cout<<"Enter discount(Enter '0' for default): ";
cin>>discount;
cin.ignore(1000,'\n');

Invoice invoice;
invoice.setCompanyEmail(companyEmail);
invoice.setCustomerEmail(customerEmail);
invoice.setTax(tax);
invoice.setDiscount(discount);
invoice.setItemList(list);
invoice.setInvoiceCode(invoiceCode);
if(tax<=0) tax=TAX_DEFAULT;
if(discount<=0) discount=DISCOUNT_DEFAULT;

cout<<"Total Amount: "<<totalAmount<<endl;
double taxAmount=totalAmount*tax;
cout<<"Tax Applied: "<<tax*100<<" Percent                  Tax Amount: "<<taxAmount<<endl;
double discountAmount=totalAmount*discount;
cout<<"Discount applied: "<<discount*100<<" Percent              Discount Amount: "<<discountAmount<<endl;
cout<<"Final Amount: "<<totalAmount+taxAmount-discountAmount<<endl;

double amountPaid;
cout<<"Enter amount paid: ";
cin>>amountPaid;
cin.ignore(1000,'\n');
invoice.setAmountPaid(amountPaid);
InvoiceManager invoiceManager;
try
{
invoiceManager.updateInvoiceByInvoiceCode(&invoice);
cout<<"Invoice updated"<<endl;
cout<<"Amount due: "<<invoice.getAmountDue()<<endl;
cout<<"Remember this invoice code for future references"<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
for(i=list.begin();i!=list.end();i++) delete (*i);
list.clear();
}
void getAllCompanyInvoice(string &companyEmail)
{
InvoiceManager invoiceManager;
CustomerManager customerManager;
CompanyManager companyManager;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IInvoice *> *invoiceList;
forward_list<abc::IItem *> *itemList;
forward_list<abc::IInvoice *>::iterator invoiceListIterator;
forward_list<abc::IItem *>::iterator itemListIterator;
try
{
invoiceList=invoiceManager.getInvoiceByCompanyEmail(companyEmail);
getLine(140,'_');
cout<<"List of All Invoices of Company with email "<<companyEmail<<endl;
getLine(140,'_');
companyManager.showProfile(companyEmail);
getLine(140,'_');
invoiceListIterator=invoiceList->begin();
if(invoiceListIterator==invoiceList->end())
{
invoiceList->clear();
delete invoiceList;
cout<<"Company has zero invoice"<<endl;
getLine(140,'_');
return;
}
for(;invoiceListIterator!=invoiceList->end();++invoiceListIterator)
{
invoice=*invoiceListIterator;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
customerManager.showCustomerProfile(companyEmail,invoice->getCustomerEmail());
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
time_t t;
t=invoice->getDate();
struct tm *now;
now=localtime(&t);
char date[10];
//sprintf(date,"%d-%d-%d\n",now->tm_mday,now->tm_mon+1,now->tm_year+1900);
cout<<"Invoice Code: "<<invoice->getInvoiceCode()<<"                Date: "<<date<<endl;

itemList=invoice->getItemList();
cout<<"--------------------------------------------------------Item List-----------------------------------------------"<<endl;
char sentence[1000];
sprintf(sentence,"| %-5s | %-50s | %-10s | %-10s | %-10s | %-15s |\n","S.No","Item Name","Item Code","Quantity","Price","Total Price");
cout<<sentence;
int x=1;
double totalPrice=0;
double totalAmount=0;
for(itemListIterator=itemList->begin();itemListIterator!=itemList->end();itemListIterator++,x++)
{
item=*itemListIterator;
totalPrice=item->getNetRate()*item->getQuantity();
totalAmount+=totalPrice;
sprintf(sentence,"| %-5d | %-50s | %-10d | %-10d | %-10.2lf | %-15.2lf |\n",x,item->getItemName().c_str(),item->getItemCode(),item->getQuantity(),item->getNetRate(),totalPrice);
cout<<sentence;
delete item;
}
itemList->clear();
delete itemList;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Total Amount: "<<totalAmount<<endl;
double taxAmount=totalAmount*invoice->getTax();
cout<<"Tax Applied: "<<invoice->getTax()*100<<" Percent                  Tax Amount: "<<taxAmount<<endl;
double discountAmount=totalAmount*invoice->getDiscount();
cout<<"Discount applied: "<<invoice->getDiscount()*100<<" Percent              Discount Amount: "<<discountAmount<<endl;
cout<<"Final Amount: "<<totalAmount+taxAmount-discountAmount<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Amount paid: "<<invoice->getAmountPaid()<<endl;
cout<<"Amount Due: "<<invoice->getAmountDue()<<endl;
getLine(140,'_');
delete invoice;
}
invoiceList->clear();
delete invoiceList;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void getInvoiceViaInvoiceCode()
{
int invoiceCode;
cout<<"Enter Invoice code: ";
cin>>invoiceCode;
cin.ignore(100,'\n');
InvoiceManager invoiceManager;
CustomerManager customerManager;
CompanyManager companyManager;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IItem *> *itemList;
forward_list<abc::IItem *>::iterator itemListIterator;

try
{
invoice=invoiceManager.getInvoiceByInvoiceCode(invoiceCode);
getLine(140,'_');
companyManager.showProfile(invoice->getCompanyEmail());
getLine(140,'_');
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
customerManager.showCustomerProfile(invoice->getCompanyEmail(),invoice->getCustomerEmail());
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
time_t t;
t=invoice->getDate();
struct tm *now;
now=localtime(&t);
char date[10];
//sprintf(date,"%d-%d-%d\n",now->tm_mday,now->tm_mon+1,now->tm_year+1900);
cout<<"Invoice Code: "<<invoice->getInvoiceCode()<<"                Date: "<<date<<endl;

itemList=invoice->getItemList();
cout<<"--------------------------------------------------------Item List-----------------------------------------------"<<endl;
char sentence[1000];
sprintf(sentence,"| %-5s | %-50s | %-10s | %-10s | %-10s | %-15s |\n","S.No","Item Name","Item Code","Quantity","Price","Total Price");
cout<<sentence;
int x=1;
double totalPrice=0;
double totalAmount=0;
for(itemListIterator=itemList->begin();itemListIterator!=itemList->end();itemListIterator++,x++)
{
item=*itemListIterator;
totalPrice=item->getNetRate()*item->getQuantity();
totalAmount+=totalPrice;
sprintf(sentence,"| %-5d | %-50s | %-10d | %-10d | %-10.2lf | %-15.2lf |\n",x,item->getItemName().c_str(),item->getItemCode(),item->getQuantity(),item->getNetRate(),totalPrice);
cout<<sentence;
delete item;
}
itemList->clear();
delete itemList;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Total Amount: "<<totalAmount<<endl;
double taxAmount=totalAmount*invoice->getTax();
cout<<"Tax Applied: "<<invoice->getTax()*100<<" Percent                  Tax Amount: "<<taxAmount<<endl;
double discountAmount=totalAmount*invoice->getDiscount();
cout<<"Discount applied: "<<invoice->getDiscount()*100<<" Percent              Discount Amount: "<<discountAmount<<endl;
cout<<"Final Amount: "<<totalAmount+taxAmount-discountAmount<<endl;
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
cout<<"Amount paid: "<<invoice->getAmountPaid()<<endl;
cout<<"Amount Due: "<<invoice->getAmountDue()<<endl;
getLine(140,'_');
delete invoice;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void removeCompanyInvoice(string &companyEmail)
{
InvoiceManager invoiceManager;
try
{
invoiceManager.removeInvoiceByCompanyEmail(companyEmail);
cout<<"All invoice of company with email "<<companyEmail<<" are removed"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
void isCompanyInvoiceExist(string companyEmail)
{
InvoiceManager invoiceManager;
int exist;
try
{
exist=invoiceManager.isInvoiceWithCompanyEmailExist(companyEmail);
if(exist) cout<<"Invoice with given company email are exist"<<endl;
else cout<<"Invoice with given company email are not exist"<<endl;
}catch(DAOException &daoException)
{
throw daoException;
}
}
void manageCompany(string &companyEmail)
{
int ch;
while(true)
{
cout<<"----------------------------[Company-Management]----------------------------"<<endl;
cout<<"1) Show profile"<<endl;
cout<<"2) Edit company address only"<<endl;
cout<<"3) Exit"<<endl;
cout<<"Enter your choice: ";
cin>>ch;
cin.ignore(1000,'\n');
if(ch==3) break;
try
{
switch(ch)
{
case 1 :
showCompanyProfile(companyEmail);
break;
case 2 : 
editCompanyAddress(companyEmail);
break;
default: 
cout<<"Invalid choice"<<endl;
}
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
}
void manageCustomer(string &companyEmail)
{
int ch;
while(true)
{
cout<<"----------------------------[Customer-Management]----------------------------"<<endl;
cout<<"1) Add customer"<<endl;
cout<<"2) Edit customer"<<endl;
cout<<"3) Edit customer address only"<<endl;
cout<<"4) Remove Customer"<<endl;
cout<<"5) View customer (Short detail)(NOT WORK FOR NOW)"<<endl;
cout<<"6) Get All customers (Complete detail)"<<endl;
cout<<"7) Get specific customer detail"<<endl;
cout<<"8) Get all customer invoice"<<endl;
cout<<"9) Remove all customer invoice"<<endl;
cout<<"10) Is customer invoice exist"<<endl;
cout<<"11) Exit"<<endl;
cout<<"Enter your choice: ";
cin>>ch;
cin.ignore(1000,'\n');
if(ch==11) break;
try
{
switch(ch)
{
case 1 :
addCustomer(companyEmail);
break;
case 2 : 
editCustomer(companyEmail);
break;
case 3 :
editCustomerAddress(companyEmail);
break;
case 4 :
removeCustomer(companyEmail);
break;
case 5 :
viewCustomer(companyEmail);
break;
case 6 :
getAllCustomersOfCompany(companyEmail);	//To be done later
break;
case 7 :
getCustomer(companyEmail);
break;
case 8 :
getAllCustomerInvoice(companyEmail);
break;
case 9 :
RemoveCustomerInvoice(companyEmail);
break;
case 10 :
isCustomerInvoiceExist(companyEmail);
break;
default: 
cout<<"Invalid choice"<<endl;
}
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
}
void manageInvoice(string &companyEmail)
{
int ch;
while(true)
{
cout<<"----------------------------[Invoice-Management]----------------------------"<<endl;
cout<<"1) Create Invoice"<<endl;
cout<<"2) Edit Invoice"<<endl;
cout<<"3) Get All Company Invoice"<<endl;
cout<<"4) Get invoice via invoice code"<<endl;
cout<<"5) Remove All Company Invoice"<<endl;
cout<<"6) Remove invoice via invoice code"<<endl;
cout<<"7) is Company Invoice exist"<<endl;
cout<<"8) is Invoice code exist"<<endl;
cout<<"9) Exit"<<endl;
cout<<"Enter your choice: ";
cin>>ch;
cin.ignore(1000,'\n');
if(ch==9) break;
try
{
switch(ch)
{
case 1 :
createInvoice(companyEmail);
break;
case 2 : 
editInvoice();
break;
case 3 :
getAllCompanyInvoice(companyEmail);
break;
case 4 :
getInvoiceViaInvoiceCode();
break;
case 5 :
removeCompanyInvoice(companyEmail);
break;
case 6 :
removeInvoiceByInvoiceCode();
break;
case 7 :
isCompanyInvoiceExist(companyEmail);
break;
case 8 :
isInvoiceCodeExist();
break;
default: 
cout<<"Invalid choice"<<endl;
}
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
}
}
void companyMenu()
{
string companyEmail;
string companyPassword;
cout<<"Enter Company email: ";
getline(cin,companyEmail);
cout<<"Enter password: ";
getline(cin,companyPassword);
CompanyManager companyManager;
try
{
int verification=companyManager.verification(companyEmail,companyPassword);
if(verification) cout<<"Verification complete"<<endl;
else cout<<"Invalid email or password"<<endl;
}catch(DAOException daoException)
{
throw daoException;
}
int ch;
while(true)
{
cout<<"----------------------------[Company-Menu]----------------------------"<<endl;
cout<<"1) Manage Company"<<endl;
cout<<"2) Manage Customer"<<endl;
cout<<"3) Manage Invoice"<<endl;
cout<<"4) Logout"<<endl;
cout<<"Enter your choice: ";
cin>>ch;
cin.ignore(1000,'\n');
if(ch==4) break;
try
{
switch(ch)
{
case 1 :
manageCompany(companyEmail);
break;
case 2 :
manageCustomer(companyEmail);
break;
case 3 :
manageInvoice(companyEmail);
break;
default :
cout<<"Invalid choice"<<endl;
}
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
}
}
void adminMenu()
{
string adminEmail;
string adminPassword;
cout<<"Enter Admin Email: ";
getline(cin,adminEmail);
cout<<"Enter password: ";
getline(cin,adminPassword);
AdminManager adminManager;
try
{
int verification=adminManager.verification(adminEmail,adminPassword);
if(!verification) cout<<"Invalid email or password"<<endl;
else cout<<"Varification complete"<<endl;
}catch(DAOException daoException)
{
throw daoException;
}
int ch;
while(true)
{
cout<<"----------------------------[Admin-Menu]----------------------------"<<endl;
cout<<"1) Add Company"<<endl;
cout<<"2) Edit COmpany Detail"<<endl;
cout<<"3) Remove company"<<endl;
cout<<"4) View company (Short Detail)(NOT WORK FOR NOW)"<<endl;
cout<<"5) Get All Company Detail (Complete detail)"<<endl;
cout<<"6) Get Specific Company detail"<<endl;
cout<<"7) Reset Password (Without enter previous password)(NOT WORK FOR NOW)"<<endl;
cout<<"8) Show all customer"<<endl;
cout<<"9) Show all invoice"<<endl;
cout<<"10) Logout"<<endl;
cout<<"Enter your choice: ";
cin>>ch;
cin.ignore(1000,'\n');
if(ch==10) break;
switch(ch)
{
case 1 :
addCompany();
break;
case 2 : 
editCompany();
break;
case 3 :
removeCompany();
break;
case 4 :
viewCompany();
break;
case 5 :
getAllCompany();
break;
case 6 :
getCompany();
break;
case 7 :
resetPasswordFree();
break;
case 8 :
getAllCustomers();
break;
case 9 : 
getAllInvoice();
break;
default: 
cout<<"Invalid choice"<<endl;
}
}
}
void loginMenu()
{
int ch;
while(true)
{
cout<<"----------------------------LOGIN MENU----------------------------"<<endl;
cout<<"1) Admin Login"<<endl;
cout<<"2) Company login"<<endl;
cout<<"3) Exit"<<endl;
cout<<"Enter your choice: ";
cin>>ch;
cin.ignore(1000.,'\n');
if(ch==3) break;
try
{
switch(ch)
{
case 1 :
adminMenu();
 break;
case 2 :
companyMenu();
break;
default : 
cout<<"Invalid choice"<<endl;
}
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
}
}
int main()
{
cout<<fixed;
cout<<setprecision(2);
cout<<"----------------------------[Wel-Come]----------------------------"<<endl;
loginMenu();
cout<<"----------------------------[Good-Bye]----------------------------"<<endl;
return 0;
}
