#include<iostream>
#include<dl/invoice>
#include<dl/invoicemanager>
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
string companyEmail;
cout<<"Enter company email: ";
getline(cin,companyEmail);
InvoiceManager invoiceManager;
try
{
invoiceManager.removeInvoiceByCompanyEmail(companyEmail);
cout<<"All invoice of company with email "<<companyEmail<<" are removed"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}