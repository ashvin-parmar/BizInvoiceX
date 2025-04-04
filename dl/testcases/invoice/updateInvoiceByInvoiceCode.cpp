#include<iostream>
#include<dl/invoice>
#include<dl/invoicemanager>
#include<forward_list>
using namespace invoicegenerator;
using namespace data_layer;
int main()
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
return 0;
}