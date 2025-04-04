#include<iostream>
#include<dl/invoice>
#include<dl/invoicemanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
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
return 0;
}