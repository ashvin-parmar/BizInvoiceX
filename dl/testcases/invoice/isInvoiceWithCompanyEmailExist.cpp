#include<iostream>
#include<dl/invoice>
#include<dl/invoicemanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
InvoiceManager invoiceManager;
string companyEmail;
cout<<"Enter company email: ";
getline(cin,companyEmail);

int exist;
try
{
exist=invoiceManager.isInvoiceWithCompanyEmailExist(companyEmail);
if(exist) cout<<"Invoice with given company email are exist"<<endl;
else cout<<"Invoice with given company email are not exist"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}