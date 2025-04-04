#include<iostream>
#include<dl/company>
#include<dl/companymanager>
#include<forward_list>
using namespace invoicegenerator;
using namespace data_layer;
void getLine(int size,char m)
{
for(int i=0;i<size;i++) cout<<m;
cout<<endl;
}
int main()
{
CompanyManager companyManager;
abc::ICompany *company;
forward_list<abc::ICompany *> *companyList;
forward_list<abc::ICompany *>::iterator i;

try
{
companyList=companyManager.getAllCompany();
getLine(140,'_');
cout<<"List of all Company with thier details"<<endl;
getLine(140,'_');
for(i=companyList->begin();i!=companyList->end();++i)
{
company=*i;
cout<<"----------Company Login Details----------"<<endl;
printf("Company Name: %-80s    Company Code: %-15d\n",company->getName().c_str(),company->getCode());
printf("Email: %-80s           Contact Number: %-15s\n\n",company->getEmail().c_str(),company->getContactNumber().c_str());

cout<<"----------Company Address----------"<<endl;
printf("Street:  %-50s    City   : %-50s\n",company->getStreet().c_str(),company->getCity().c_str());
printf("State :  %-50s    Country: %-50s\n",company->getState().c_str(),company->getCountry().c_str());
printf("Pin Code: %-15d\n\n",company->getPinCode());

cout<<"----------Bank Detail----------"<<endl;
printf("GST Number: %-50s UPIID: %-50s\n",company->getGSTNumber().c_str(),company->getUPIID().c_str());
getLine(140,'_');
cout<<endl;
getLine(140,'_');
delete company;
}
companyList->clear();
delete companyList;
}catch(DAOException daoException)
{
cout<<daoException.what()<<endl;
}
return 0;
}