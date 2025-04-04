#include<dl/daoexception>
using namespace invoicegenerator;
using namespace data_layer;
DAOException::DAOException()
{
this->messege="";
}
DAOException::DAOException(const DAOException &other)
{
this->messege=other.messege;
}
DAOException::DAOException(string messege)
{
this->messege=messege;
}
DAOException& DAOException::operator=(const DAOException &other)
{
this->messege=other.messege;
return *this;
}
const char * DAOException::what() const throw()
{
return this->messege.c_str();
}
DAOException::~DAOException() throw()
{
// do nothing
}

