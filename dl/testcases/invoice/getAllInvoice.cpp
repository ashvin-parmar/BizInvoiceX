#include<iostream>
#include<dl/company>
#include<dl/companymanager>
#include<dl/customer>
#include<dl/customermanager>
#include<dl/invoice>
#include<dl/invoicemanager>
#include<iomanip>
using namespace invoicegenerator;
using namespace data_layer;
void getLine(int size,char m)
{
for(int i=0;i<size;i++) cout<<m;
cout<<endl;
}
int main()
{
cout<<fixed;
cout<<setprecision(2);
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
customerManager.showCustomerProfile(invoice->getCustomerEmail());
cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
time_t t;
t=invoice->getDate();
struct tm *now;
now=localtime(&t);
char date[10];
sprintf(date,"%d/%d/%d\n",now->tm_mday,now->tm_mon+1,now->tm_year+1900);
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
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}