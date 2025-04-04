#include<iostream>
#include<dl/invoice>
#include<dl/invoicemanager>
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);
InvoiceManager invoiceManager;
try
{
invoiceManager.removeInvoiceByCustomerEmail(customerEmail);
cout<<"All invoice of customer with email "<<customerEmail<<" are removed"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}