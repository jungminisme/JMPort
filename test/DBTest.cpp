#include <gtest/gtest.h>
#include "DBManager.h"

using namespace JMLib::DBLib;

TEST( DBLibTest, Connect )
{
    CDBManager & aDM = CDBManager::GetInstance();
    JMLib::string aAddr = L"127.0.0.1";
    JMLib::string aUser = L"TestUser";
    JMLib::string aPass = L"TestPass";

    EXPECT_TRUE( aDM.Connect( aAddr, aUser, aPass ) );

    //! 우선 test case만을 작성해 놓음. db에 user 추가하고 privilige 설정해 놓아야 함. 

    //! 2023. 04. 01 TODO // CMakeLists.txt에. 파일 .. 다시 전체 목록으로 바꿔둔다. 
}