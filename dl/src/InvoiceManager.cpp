#include<dl/icustomer>
#include<dl/customer>
#include<dl/icustomermanager>
#include<dl/customermanager>
#include<dl/daoexception>
#include<dl/icompany>
#include<dl/company>
#include<dl/icompanymanager>
#include<dl/companymanager>
#include<dl/invoice>
#include<dl/iinvoice>
#include<dl/iinvoicemanager>
#include<dl/invoicemanager>
#include<fstream>
#include<string.h>
#include<forward_list>
#include<common/stringutils>
#include<cmath>
using namespace stringutils;
using namespace invoicegenerator;
using namespace data_layer;
void InvoiceManager::addInvoice(abc::IInvoice *invoice) noexcept(false)
{
if(invoice==NULL) throw DAOException("Required invoice data, NULL encountered");
if(invoice->getInvoiceCode()!=0) throw DAOException("Required: Code should be zero");
string companyEmail=validateEmail(invoice->getCompanyEmail());
if(companyEmail.size()==0 || companyEmail.size()>80) throw DAOException("Invalid Company Email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");
string customerEmail=validateEmail(invoice->getCustomerEmail());
if(customerEmail.size()==0 || customerEmail.size()>80) throw DAOException("Invalid Customer Email");
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(companyEmail,customerEmail);
if(!exist) throw DAOException("Customer with given email is not exist, First to add customer");
time_t t;
forward_list<abc::IItem *> *itemList;
itemList=invoice->getItemList();
if(itemList==NULL) throw DAOException("Required item list");
forward_list<abc::IItem *>::iterator i=itemList->begin();
if(i==itemList->end()) throw DAOException("Required items, Invoice with zero items are not allowed");
//Variables declared
int numberOfItems=0;
double totalAmount=0;
abc::IItem *item;
string itemName;
int itemCode;
double netRate;
int quantity;
for(;i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
int size=itemName.size();
if(size==0 ) throw DAOException("Item name Required");
if(size>150) throw DAOException("Item name size cannot exceed 150 characters");
itemCode=item->getItemCode();
if(itemCode<=0) throw DAOException(string("Invalid item code Against item:")+itemName);
netRate=item->getNetRate();
if(netRate<=0) throw DAOException(itemName+string(" item rate can never be zero or negative"));
quantity=item->getQuantity();
if(quantity<=0) throw DAOException(itemName+string(" quantity cannot be zero or negative"));
if(quantity>ITEM_MAX_QUANTITY) throw DAOException(itemName+string(" item max quantity (50) reached"));
totalAmount+=(item->getNetRate()*item->getQuantity());
numberOfItems++;
}
double discount=invoice->getDiscount();
double tax=invoice->getTax();
if(tax<=0) tax=TAX_DEFAULT;	
else if(tax>=1) throw DAOException("Tax (in %) can never be more than equal to 1");
if(discount<=0) discount=DISCOUNT_DEFAULT;
else if(discount>=1) throw DAOException("Discount (in %) can never be more than equal to 1");
double amountPaid=invoice->getAmountPaid();
double amountDue=0;
double taxAmount=totalAmount*tax;
double discountAmount=totalAmount*discount;
totalAmount=totalAmount+taxAmount-discountAmount;
totalAmount=round(totalAmount*100.0)/100.0;
if(amountPaid<0) throw DAOException("Paid amount can never be negative");
if(amountPaid>totalAmount) 
{
char amount[10];
//sprintf(amount,"%f rs",amountPaid-totalAmount);
throw DAOException("You paid extra money of amount "+string(amount)+" more than total amount");
}
InvoiceManager::Header header;
_Invoice _invoice;
_Item _item;
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
ofstream dFile(INVOICE_FILE_NAME,ios::app | ios::binary);
header.numberOfRecords=1;
header.lastGeneratedInvoiceCode=1;
_invoice.invoiceCode=1;
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=(totalAmount-amountPaid);
_invoice.amountDue=(amountDue);
_invoice.numberOfItems=numberOfItems;
dFile.write((char *)&header,sizeof(Header));
dFile.write((char *)&_invoice,sizeof(_Invoice));
for(i=itemList->begin();i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
strcpy(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
dFile.write((char *)&_item,sizeof(_Item));
}
dFile.close();
invoice->setInvoiceCode(header.lastGeneratedInvoiceCode);
invoice->setAmountDue(amountDue);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.seekp(0,ios::beg);
header.numberOfRecords=1;
header.lastGeneratedInvoiceCode=1;
_invoice.invoiceCode=1;
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=totalAmount-amountPaid;
_invoice.amountDue=amountDue;
_invoice.numberOfItems=numberOfItems;
dataFile.write((char *)&header,sizeof(Header));
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(i=itemList->begin();i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
strcpy(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
dataFile.write((char *)&_item,sizeof(_Item));
}
dataFile.close();
invoice->setInvoiceCode(header.lastGeneratedInvoiceCode);
invoice->setAmountDue(amountDue);
return;
}
dataFile.clear();
dataFile.seekp(0,ios::end);
header.lastGeneratedInvoiceCode++;
header.numberOfRecords++;
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
_invoice.invoiceCode=header.lastGeneratedInvoiceCode;
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=totalAmount-amountPaid;
_invoice.amountDue=amountDue;
_invoice.numberOfItems=numberOfItems;
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(i=itemList->begin();i!=itemList->end();++i)
{
item=*i;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
strcpy(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
dataFile.write((char *)&_item,sizeof(_Item));
}
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close();
invoice->setInvoiceCode(header.lastGeneratedInvoiceCode);
invoice->setAmountDue(amountDue);
}
void InvoiceManager::updateInvoiceByInvoiceCode(abc::IInvoice *invoice) noexcept(false)
{
if(invoice==NULL) throw DAOException("Required invoice data, NULL encountered");
int invoiceCode=invoice->getInvoiceCode();
if(invoiceCode<=0) throw DAOException("Invalid invoice code");
string companyEmail=validateEmail(invoice->getCompanyEmail());
if(companyEmail.size()==0 || companyEmail.size()>80) throw DAOException("Invalid Company Email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email is not exist");
string customerEmail=validateEmail(invoice->getCustomerEmail());
if(customerEmail.size()==0 || customerEmail.size()>80) throw DAOException("Invalid Customer Email");
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(companyEmail,customerEmail);
if(!exist) throw DAOException("Customer with given email is not exist, First to add customer");
time_t t;
forward_list<abc::IItem *> *itemList;
itemList=invoice->getItemList();
if(itemList==NULL) throw DAOException("Required item list");
forward_list<abc::IItem *>::iterator ii=itemList->begin();
if(ii==itemList->end()) throw DAOException("Required items, Invoice with zero items are not allowed");
//Variables declared
int numberOfItems=0;
double totalAmount=0;
abc::IItem *item;
string itemName;
int itemCode;
double netRate;
int quantity;
for(;ii!=itemList->end();++ii)
{
item=*ii;
itemName=item->getItemName();
int size=itemName.size();
if(size==0 ) throw DAOException("Item name Required");
if(size>150) throw DAOException("Item name size cannot exceed 150 characters");
itemCode=item->getItemCode();
if(itemCode<=0) throw DAOException(string("Invalid item code Against item:")+itemName);
netRate=item->getNetRate();
if(netRate<=0) throw DAOException(itemName+string(" item rate can never be zero or negative"));
quantity=item->getQuantity();
if(quantity<=0) throw DAOException(itemName+string(" quantity cannot be zero or negative"));
if(quantity>ITEM_MAX_QUANTITY) throw DAOException(itemName+string(" item max quantity (50) reached"));
totalAmount+=(item->getNetRate()*item->getQuantity());
numberOfItems++;
}
double discount=invoice->getDiscount();
double tax=invoice->getTax();
if(tax<=0) tax=TAX_DEFAULT;	
else if(tax>=1) throw DAOException("Tax (in %) can never be more than equal to 1");
if(discount<=0) discount=DISCOUNT_DEFAULT;
else if(discount>=1) throw DAOException("Discount (in %) can never be more than equal to 1");
double amountPaid=invoice->getAmountPaid();
double amountDue=0;
double taxAmount=totalAmount*tax;
double discountAmount=totalAmount*discount;
totalAmount=totalAmount+taxAmount-discountAmount;
totalAmount=round(totalAmount*100.0)/100.0;
if(amountPaid<0) throw DAOException("Paid amount can never be negative");
if(amountPaid>totalAmount) 
{
char amount[10];
//sprintf(amount,"%lf rs",amountPaid-totalAmount);
throw DAOException("You paid extra money of amount "+string(amount)+" more than total amount");
}
InvoiceManager::Header header;
_Invoice _invoice;
_Item _item;
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid invoice code");
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
dataFile.clear();
dataFile.seekg(sizeof(Header),ios::beg);
int found=0;
while(1)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode==invoiceCode)
{
found=1;
break;
}
dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(!found)
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
dataFile.clear();
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
if(tmpFile.fail()) 
{
dataFile.close();
throw DAOException("Unable to open file");
}
tmpFile.write((char *)&header,sizeof(Header));
dataFile.seekp(sizeof(Header),ios::beg);
while(1)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode!=invoiceCode)
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
strcpy(_invoice.companyEmail,companyEmail.c_str());
strcpy(_invoice.customerEmail,customerEmail.c_str());
time(&t);
_invoice.date=t;
_invoice.amountPaid=amountPaid;
_invoice.tax=tax;
_invoice.discount=discount;
amountDue=totalAmount-amountPaid;
_invoice.amountDue=amountDue;
_invoice.numberOfItems=numberOfItems;
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(ii=itemList->begin();ii!=itemList->end();++ii)
{
item=*ii;
itemName=item->getItemName();
itemCode=item->getItemCode();
netRate=item->getNetRate();
quantity=item->getQuantity();
strcpy(_item.itemName,itemName.c_str());
_item.itemCode=itemCode;
_item.quantity=quantity;
_item.netRate=netRate;
tmpFile.write((char *)&_item,sizeof(_Item));
}
invoice->setAmountDue(amountDue);
}
if(dataFile.fail()) break;
}
tmpFile.clear();
dataFile.clear();
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
tmpFile.open("tmp.tmp",ios::in | ios::binary);
tmpFile.seekp(0,ios::beg);
dataFile.seekg(0,ios::beg);
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: Unable to read");
dataFile.write((char *)&header,sizeof(Header));
while(1)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
void InvoiceManager::removeInvoiceByInvoiceCode(int invoiceCode) noexcept(false)
{
if(invoiceCode<=0) throw DAOException("Invalid invoice code");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid invoice code");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
if(header.numberOfRecords==0 || invoiceCode>header.lastGeneratedInvoiceCode)
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
header.numberOfRecords--;
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode!=invoiceCode)
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
}
if(dataFile.fail()) break;
}
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
if(dataFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.open("tmp.tmp",ios::in | ios::binary);
if(tmpFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
void InvoiceManager::removeInvoiceByCustomerEmail(string &vCompanyEmail,string &vCustomerEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()<=0 || companyEmail.size()>81) throw DAOException("Invalid company email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email does not exist");

string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()<=0 || customerEmail.size()>81) throw DAOException("Invalid email");
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(companyEmail,customerEmail);
if(!exist) throw DAOException("Customer with given email does not exist");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invoice not available");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invoice not available");
}
if(header.numberOfRecords==0 )
{
dataFile.close();
throw DAOException("Invoice not available");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(!(compareStringIgnoreCase(_invoice.customerEmail,customerEmail.c_str())==0 && compareStringIgnoreCase(_invoice.companyEmail,companyEmail.c_str())==0))
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
header.numberOfRecords--;
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
}
if(dataFile.fail()) break;
}
tmpFile.clear();
tmpFile.seekp(0,ios::beg);
tmpFile.write((char *)&header,sizeof(Header));
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
if(dataFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.open("tmp.tmp",ios::in | ios::binary);
if(tmpFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
void InvoiceManager::removeInvoiceByCompanyEmail(string &vCompanyEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()<=0 || companyEmail.size()>81) throw DAOException("Invalid company email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email does not exist");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invoice not available");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invoice not available");
}
if(header.numberOfRecords==0 )
{
dataFile.close();
throw DAOException("Invoice not available");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
fstream tmpFile("tmp.tmp",ios::out | ios::binary);
tmpFile.write((char *)&header,sizeof(Header));
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_invoice.companyEmail,companyEmail.c_str())!=0)
{
tmpFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
tmpFile.write((char *)&_item,sizeof(_Item));
}
}
else
{
header.numberOfRecords--;
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
}
if(dataFile.fail()) break;
}
tmpFile.clear();
tmpFile.seekp(0,ios::beg);
tmpFile.write((char *)&header,sizeof(Header));
dataFile.close();
tmpFile.close();
dataFile.open(INVOICE_FILE_NAME,ios::out | ios::binary);
if(dataFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.open("tmp.tmp",ios::in | ios::binary);
if(tmpFile.fail()) throw DAOException("ERROR: failed to open file");
tmpFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);	
tmpFile.read((char *)&header,sizeof(Header));
if(tmpFile.fail()) throw DAOException("ERROR: failed to read header");
dataFile.write((char *)&header,sizeof(Header));
while(true)
{
tmpFile.read((char *)&_invoice,sizeof(_Invoice));
if(tmpFile.fail()) break;
dataFile.write((char *)&_invoice,sizeof(_Invoice));
for(int i=0;i<_invoice.numberOfItems;i++)
{
tmpFile.read((char *)&_item,sizeof(_Item));
if(tmpFile.fail()) break;
dataFile.write((char *)&_item,sizeof(_Item));
}
if(tmpFile.fail()) break;
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::out | ios::binary);
tmpFile.close();
}
forward_list<abc::IInvoice *> *InvoiceManager::getAllInvoice() noexcept(false)
{
Header header;
ifstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail()) throw DAOException("Zero invoice added");
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail()) 
{
dataFile.close();
throw DAOException("Zero Invoice exist");
}
if(header.numberOfRecords==0) 
{
dataFile.close();
throw DAOException("Zero Invoice exist");
}
_Invoice _invoice;
_Item _item;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IInvoice *> *invoiceList;
invoiceList=new forward_list<abc::IInvoice *>;
forward_list<abc::IInvoice *>::iterator invoiceListIterator=invoiceList->before_begin();
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
int numberOfItems;
invoice=new Invoice;
invoice->setInvoiceCode(_invoice.invoiceCode);
invoice->setCustomerEmail(string(_invoice.customerEmail));
invoice->setCompanyEmail(string(_invoice.companyEmail));
invoice->setDate(_invoice.date);
invoice->setTax(_invoice.tax);
invoice->setDiscount(_invoice.discount);
numberOfItems=_invoice.numberOfItems;
invoice->setNumberOfItems(numberOfItems);
invoice->setAmountPaid(_invoice.amountPaid);
invoice->setAmountDue(_invoice.amountDue);

forward_list<abc::IItem *> itemList;
forward_list<abc::IItem *>::iterator itemListIterator=itemList.before_begin();
for(int i=0;i<numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
item=new Item;
item->setItemName(_item.itemName);
item->setItemCode(_item.itemCode);
item->setQuantity(_item.quantity);
item->setNetRate(_item.netRate);
itemListIterator=itemList.insert_after(itemListIterator,item);
}
invoice->setItemList(itemList);
for(itemListIterator=itemList.begin();itemListIterator!=itemList.end();++itemListIterator) delete *itemListIterator;
itemList.clear();
invoiceListIterator=invoiceList->insert_after(invoiceListIterator,invoice);
}
dataFile.close();
return invoiceList;
}
forward_list<abc::IInvoice *> * InvoiceManager::getInvoiceByCustomerEmail(string &vCompanyEmail,string &vCustomerEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()<=0 || companyEmail.size()>81) throw DAOException("Invalid company email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email does not exist");

string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()<=0 || customerEmail.size()>81) throw DAOException("Invalid email");
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(companyEmail,customerEmail);
if(!exist) throw DAOException("Customer with given email does not exist");

fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invoice not available");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invoice not available");
}
if(header.numberOfRecords==0 )
{
dataFile.close();
throw DAOException("Invoice not available");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IInvoice *> *invoiceList;
invoiceList=new forward_list<abc::IInvoice *>;
forward_list<abc::IInvoice *>::iterator invoiceListIterator=invoiceList->before_begin();
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_invoice.customerEmail,customerEmail.c_str())==0 && compareStringIgnoreCase(_invoice.companyEmail,companyEmail.c_str())==0)
{
int numberOfItems;
invoice=new Invoice;
invoice->setInvoiceCode(_invoice.invoiceCode);
invoice->setCustomerEmail(string(_invoice.customerEmail));
invoice->setCompanyEmail(string(_invoice.companyEmail));
invoice->setDate(_invoice.date);
invoice->setTax(_invoice.tax);
invoice->setDiscount(_invoice.discount);
numberOfItems=_invoice.numberOfItems;
invoice->setNumberOfItems(numberOfItems);
invoice->setAmountPaid(_invoice.amountPaid);
invoice->setAmountDue(_invoice.amountDue);
forward_list<abc::IItem *> itemList;
forward_list<abc::IItem *>::iterator itemListIterator=itemList.before_begin();
for(int i=0;i<numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
item=new Item;
item->setItemName(_item.itemName);
item->setItemCode(_item.itemCode);
item->setQuantity(_item.quantity);
item->setNetRate(_item.netRate);
itemListIterator=itemList.insert_after(itemListIterator,item);
}
invoice->setItemList(itemList);
for(itemListIterator=itemList.begin();itemListIterator!=itemList.end();++itemListIterator) delete *itemListIterator;
itemList.clear();
invoiceListIterator=invoiceList->insert_after(invoiceListIterator,invoice);
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
//dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(dataFile.fail()) break;
}
dataFile.close();
return invoiceList;
}
forward_list<abc::IInvoice *> * InvoiceManager::getInvoiceByCompanyEmail(string &vCompanyEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()<=0 || companyEmail.size()>81) throw DAOException("Invalid company email");
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) throw DAOException("Company with given email does not exist");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invoice not available");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invoice not available");
}
if(header.numberOfRecords==0 )
{
dataFile.close();
throw DAOException("Invoice not available");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
abc::IInvoice *invoice;
abc::IItem *item;
forward_list<abc::IInvoice *> *invoiceList;
invoiceList=new forward_list<abc::IInvoice *>;
forward_list<abc::IInvoice *>::iterator invoiceListIterator=invoiceList->before_begin();
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_invoice.companyEmail,companyEmail.c_str())==0)
{
int numberOfItems;
invoice=new Invoice;
invoice->setInvoiceCode(_invoice.invoiceCode);
invoice->setCustomerEmail(string(_invoice.customerEmail));
invoice->setCompanyEmail(string(_invoice.companyEmail));
invoice->setDate(_invoice.date);
invoice->setTax(_invoice.tax);
invoice->setDiscount(_invoice.discount);
numberOfItems=_invoice.numberOfItems;
invoice->setNumberOfItems(numberOfItems);
invoice->setAmountPaid(_invoice.amountPaid);
invoice->setAmountDue(_invoice.amountDue);
forward_list<abc::IItem *> itemList;
forward_list<abc::IItem *>::iterator itemListIterator=itemList.before_begin();
for(int i=0;i<numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
item=new Item;
item->setItemName(_item.itemName);
item->setItemCode(_item.itemCode);
item->setQuantity(_item.quantity);
item->setNetRate(_item.netRate);
itemListIterator=itemList.insert_after(itemListIterator,item);
}
invoice->setItemList(itemList);
for(itemListIterator=itemList.begin();itemListIterator!=itemList.end();++itemListIterator) delete *itemListIterator;
itemList.clear();
invoiceListIterator=invoiceList->insert_after(invoiceListIterator,invoice);
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
//dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(dataFile.fail()) break;
}
dataFile.close();
return invoiceList;
}
abc::IInvoice * InvoiceManager::getInvoiceByInvoiceCode(int invoiceCode) noexcept(false)
{
if(invoiceCode<=0) throw DAOException("Invalid Invoice code");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
throw DAOException("Invalid invoice code");
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Invalid invoice code");
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
abc::IInvoice *invoice;
abc::IItem *item;
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode==invoiceCode)
{
int numberOfItems;
invoice=new Invoice;
invoice->setInvoiceCode(_invoice.invoiceCode);
invoice->setCustomerEmail(string(_invoice.customerEmail));
invoice->setCompanyEmail(string(_invoice.companyEmail));
invoice->setDate(_invoice.date);
invoice->setTax(_invoice.tax);
invoice->setDiscount(_invoice.discount);
numberOfItems=_invoice.numberOfItems;
invoice->setNumberOfItems(numberOfItems);
invoice->setAmountPaid(_invoice.amountPaid);
invoice->setAmountDue(_invoice.amountDue);
forward_list<abc::IItem *> itemList;
forward_list<abc::IItem *>::iterator itemListIterator=itemList.before_begin();
for(int i=0;i<numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
item=new Item;
item->setItemName(_item.itemName);
item->setItemCode(_item.itemCode);
item->setQuantity(_item.quantity);
item->setNetRate(_item.netRate);
itemListIterator=itemList.insert_after(itemListIterator,item);
}
invoice->setItemList(itemList);
for(itemListIterator=itemList.begin();itemListIterator!=itemList.end();++itemListIterator) delete *itemListIterator;
itemList.clear();
dataFile.close();
return invoice;
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
//dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(dataFile.fail()) break;
}
dataFile.close();
throw DAOException("Invalid invoice code");
}
int InvoiceManager::isInvoiceWithCompanyEmailExist(const string &vCompanyEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()<=0 || companyEmail.size()>81) return 0;
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) return 0;
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
if(header.numberOfRecords==0 )
{
dataFile.close();
return 0;
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_invoice.companyEmail,companyEmail.c_str())==0)
{
dataFile.close();
return 1;
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
//dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(dataFile.fail()) break;
}
dataFile.close();
return 0;
}
int InvoiceManager::isInvoiceWithCustomerEmailExist(const string &vCompanyEmail,const string &vCustomerEmail) noexcept(false)
{
string companyEmail=validateEmail(vCompanyEmail);
if(companyEmail.size()<=0 || companyEmail.size()>81) return 0;
int exist;
CompanyManager companyManager;
exist=companyManager.isCompanyWithEmailExist(companyEmail);
if(!exist) return 0;
string customerEmail=validateEmail(vCustomerEmail);
if(customerEmail.size()<=0 || customerEmail.size()>81) return 0;
CustomerManager customerManager;
exist=customerManager.isCustomerWithEmailExist(companyEmail,customerEmail);
if(!exist) return 0;
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
InvoiceManager::Header header;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
if(header.numberOfRecords==0 )
{
dataFile.close();
return 0;
}
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_invoice.customerEmail,customerEmail.c_str())==0 && compareStringIgnoreCase(_invoice.companyEmail,companyEmail.c_str())==0)
{
dataFile.close();
return 1;
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
//dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(dataFile.fail()) break;
}
dataFile.close();
return 0;
}
int InvoiceManager::isInvoiceWithInvoiceCodeExist(const int invoiceCode) noexcept(false)
{
if(invoiceCode<=0) throw DAOException("Invalid Invoice code");
fstream dataFile(INVOICE_FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())
{
return 0;
}
InvoiceManager::Header header;
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
dataFile.clear();
dataFile.seekg(sizeof(header),ios::beg);
_Item _item;
_Invoice _invoice;
while(true)
{
dataFile.read((char *)&_invoice,sizeof(_Invoice));
if(dataFile.fail()) break;
if(_invoice.invoiceCode==invoiceCode)
{
dataFile.close();
return 1;
}
else
{
for(int i=0;i<_invoice.numberOfItems;i++)
{
dataFile.read((char *)&_item,sizeof(_Item));
if(dataFile.fail()) break;
}
//dataFile.seekg(sizeof(_Item)*_invoice.numberOfItems,ios::cur);
}
if(dataFile.fail()) break;
}
dataFile.close();
return 0;
}
