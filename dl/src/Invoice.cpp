#include<iostream>
#include<dl/iinvoice>
#include<dl/invoice>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
Item::Item()
{
this->itemName="";
this->itemCode=0;
this->quantity=0;
this->netRate=0.00000;
}
Item::Item(const Item &other)
{
this->itemName=other.itemName;
this->itemCode=other.itemCode;
this->quantity=other.quantity;
this->netRate=other.netRate;
}
Item::Item(string itemName,int itemCode, int quantity, double netRate)
{
this->itemName=itemName;
this->itemCode=itemCode;
this->quantity=quantity;
this->netRate=netRate;
}
Item::~Item()
{
//Nothing to do
}
void Item::setItemName(string itemName)
{
this->itemName=itemName;
}
void Item::setItemCode(int itemCode)
{
this->itemCode=itemCode;
}
void Item::setQuantity(int quantity)
{
this->quantity=quantity;
}
void Item::setNetRate(double netRate)
{
this->netRate=netRate;
}
string Item::getItemName() const
{
return this->itemName;
}
int Item::getItemCode() const
{
return this->itemCode;
}
int Item::getQuantity() const
{
return this->quantity;
}
double Item::getNetRate() const
{
return this->netRate;
}
abc::IItem& Item::operator=(const abc::IItem &other)
{
this->itemName=other.getItemName();
this->itemCode=other.getItemCode();
this->quantity=other.getQuantity();
this->netRate=other.getNetRate();
return *this;
}
int Item::operator==(const abc::IItem &other)
{
return this->itemCode==other.getItemCode();
}
int Item::operator<=(const abc::IItem &other)
{
return this->itemCode<=other.getItemCode();
}
int Item::operator>=(const abc::IItem &other)
{
return this->itemCode>=other.getItemCode();
}
int Item::operator!=(const abc::IItem &other)
{
return this->itemCode!=other.getItemCode();
}
int Item::operator<(const abc::IItem &other)
{
return this->itemCode<other.getItemCode();
}
int Item::operator>(const abc::IItem &other)
{
return this->itemCode>other.getItemCode();
}
//======================================================

Invoice::Invoice()
{
this->invoiceCode=0;
this->companyEmail="";
this->customerEmail="";
this->date=0;
this->numberOfItems=0;
this->itemList=NULL;
this->amountPaid=0;
this->amountDue=0;
this->discount=0;
this->tax=0;
}
Invoice::Invoice(const Invoice &other)
{
this->invoiceCode=other.invoiceCode;
this->companyEmail=other.companyEmail;
this->customerEmail=other.customerEmail;
this->date=other.date;
this->numberOfItems=other.numberOfItems;
this->amountPaid=other.amountPaid;
this->amountDue=other.amountDue;
this->discount=other.discount;
this->tax=other.tax;
this->itemList=new forward_list<abc::IItem *>;
Item *item;
forward_list<abc::IItem *>::iterator j=this->itemList->before_begin();
for(forward_list<abc::IItem *>::iterator i=other.itemList->begin();i!=other.itemList->end();++i)
{
item=new Item;
item->setItemName((*i)->getItemName());
item->setItemCode((*i)->getItemCode());
item->setQuantity((*i)->getQuantity());
item->setNetRate((*i)->getNetRate());
j=this->itemList->insert_after(j,item);
}
}
Invoice::~Invoice()
{
abc::IItem *item;
for(forward_list<abc::IItem *>::iterator i=this->itemList->begin();i!=this->itemList->end();++i)
{
item=*i;
delete (item);
}
itemList->clear();
delete itemList;
}
void Invoice::setInvoiceCode(int invoiceCode)
{
this->invoiceCode=invoiceCode;
}
void Invoice::setCompanyEmail(string companyEmail)
{
this->companyEmail=companyEmail;
}
void Invoice::setCustomerEmail(string customerEmail)
{
this->customerEmail=customerEmail;
}
void Invoice::setDate(time_t date)
{
this->date=date;
}
void Invoice::setNumberOfItems(int numberOfItems)
{
this->numberOfItems=numberOfItems;
}
void Invoice::setItemList(forward_list<abc::IItem *> &itemList)
{
this->itemList=new forward_list<abc::IItem *>;
abc::IItem *item;
forward_list<abc::IItem *>::iterator j=this->itemList->before_begin();
for(forward_list<abc::IItem *>::iterator i=itemList.begin();i!=itemList.end();++i)
{
item=new Item;
item->setItemName((*i)->getItemName());
item->setItemCode((*i)->getItemCode());
item->setQuantity((*i)->getQuantity());
item->setNetRate((*i)->getNetRate());
j=this->itemList->insert_after(j,item);
}
}
void Invoice::setAmountPaid(double amountPaid)
{
this->amountPaid=amountPaid;
}
void Invoice::setAmountDue(double amountDue)
{
this->amountDue=amountDue;
}
void Invoice::setDiscount(double discount)
{
this->discount=discount;
}
void Invoice::setTax(double tax)
{
this->tax=tax;
}
int Invoice::getInvoiceCode() const
{
return this->invoiceCode;
}
string Invoice::getCustomerEmail() const
{
return this->customerEmail;
}
string Invoice::getCompanyEmail() const
{
return this->companyEmail;
}
time_t Invoice::getDate() const
{
return this->date;
}
int Invoice::getNumberOfItems() const
{
return this->numberOfItems;
}
forward_list<abc::IItem *> * Invoice::getItemList() const
{
return (this->itemList);
}
double Invoice::getAmountPaid() const
{
return this->amountPaid;
}
double Invoice::getAmountDue() const
{
return this->amountDue;
}
double Invoice::getDiscount() const
{
return this->discount;
}
double Invoice::getTax() const
{
return this->tax;
}
abc::IInvoice& Invoice::operator=(const abc::IInvoice &other)
{
this->invoiceCode=other.getInvoiceCode();
this->companyEmail=other.getCompanyEmail();
this->customerEmail=other.getCustomerEmail();
this->date=other.getDate();
this->numberOfItems=other.getNumberOfItems();
this->amountPaid=other.getAmountPaid();
this->amountDue=other.getAmountDue();
this->discount=other.getDiscount();
this->tax=other.getTax();
forward_list<abc::IItem *> *otherList;
otherList=other.getItemList();
this->itemList=new forward_list<abc::IItem *>;
abc::IItem *item;
forward_list<abc::IItem *>::iterator j=this->itemList->before_begin();
for(forward_list<abc::IItem *>::iterator i=otherList->begin();i!=otherList->end();++i)
{
item=new Item;
item->setItemName((*i)->getItemName());
item->setItemCode((*i)->getItemCode());
item->setQuantity((*i)->getQuantity());
item->setNetRate((*i)->getNetRate());
j=this->itemList->insert_after(j,item);
}
return *this;
}
int Invoice::operator==(const abc::IInvoice &other)
{
return this->invoiceCode==other.getInvoiceCode();
}
int Invoice::operator<=(const abc::IInvoice &other)
{
return this->invoiceCode<=other.getInvoiceCode();
}
int Invoice::operator>=(const abc::IInvoice &other)
{
return this->invoiceCode>=other.getInvoiceCode();
}
int Invoice::operator!=(const abc::IInvoice &other)
{
return this->invoiceCode!=other.getInvoiceCode();
}
int Invoice::operator<(const abc::IInvoice &other)
{
return this->invoiceCode<other.getInvoiceCode();
}
int Invoice::operator>(const abc::IInvoice &other)
{
return this->invoiceCode>other.getInvoiceCode();
}