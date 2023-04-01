#include <gtest/gtest.h>
#include "DBManager.h"

using namespace JMLib::DBLib;

TEST( DBLibTest, Connect )
{
    CDBManager & aDM = CDBManager::GetInstance();
    string aAddr = L"127.0.0.1";
    string aUser = L"TestUser";
    string aPass = L"TestPass";

    EXPECT_TRUE( aDM.Connect( aAddr, aUser, aPass ) );
}