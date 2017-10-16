/**
 * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 9/8/17 Carlos Brito *
 * * * * * * * * * * * * * * * * * * *
 * 
 * @file
 * @brief Contains class declarations.
 */
#ifndef SERVER_DB_GENERICDAO_HPP
#define SERVER_DB_GENERICDAO_HPP

#include <memory>
#include <string>
#include <vector>
#include <cppconn/connection.h>

namespace solarplant
{
namespace db
{
namespace dao
{
/**
 * @class   ClientDAO
 * @author  Carlos Brito (carlos.brito524@gmail.com)
 * @brief   No description available.
 * 
 * No full length description available.
 */
template < typename T, typename Key>
class GenericDAO
{
protected:
    const std::shared_ptr<sql::Connection> conn; ///< Connection object used to communicate with db
public:
    typedef Key key_type;
    GenericDAO(const std::shared_ptr<sql::Connection> conn) : conn( conn )
    {}
    virtual T get(const Key & id) = 0;
    virtual void save(const T& object) = 0;
};
}
}
}


#endif //SERVER_GENERICDAO_HPP