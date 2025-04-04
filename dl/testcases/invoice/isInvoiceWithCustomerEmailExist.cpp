#include<iostream>
#include<dl/invoice>
#include<dl/invoicemanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
InvoiceManager invoiceManager;
string customerEmail;
cout<<"Enter customer email: ";
getline(cin,customerEmail);

int exist;
try
{
exist=invoiceManager.isInvoiceWithCustomerEmailExist(customerEmail);
if(exist) cout<<"Invoice with given customer email are exist"<<endl;
else cout<<"Invoice with given customer email are not exist"<<endl;
}catch(DAOException &daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}