#include<iostream>
#include<dl/customer>
#include<dl/customermanager>
using namespace std;
using namespace invoicegenerator;
using namespace data_layer;
int main()
{
Customer customer;
CustomerManager customerManager;
string email;
cout<<"Enter email: ";
getline(cin,email);
customer=customerManager.getCustomerByEmail(email);
cout<<"----------Customer Login Details----------"<<endl;
printf("Customer Name: %-80s    Customer Code: %-15d\n",customer->getCustomerName().c_str(),customer->getCustomerCode());
printf("Email: %-80s           Contact Number: %-15s\n\n",customer->getEmail().c_str(),customer->getContactNumber().c_str());

cout<<"----------Customer Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",customer->getStreet().c_str(),customer->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",customer->getState().c_str(),customer->getCountry().c_str());
printf("Pin Code: %-15d\n\n",customer->getPinCode());

getLine(140,'_');
cout<<endl;
getLine(140,'_');
delete customer;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}