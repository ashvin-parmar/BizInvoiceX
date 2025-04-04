#include<iostream>
#include<dl/invoice>
#include<dl/invoicemanager>
using namespace invoicegenerator;
using namespace data_layer;
int main()
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
return 0;
}