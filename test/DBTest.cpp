#include <gtest/gtest.h>
#include "DBManager.h"

using namespace JMLib::DBLib;

TEST( DBLibTest, Connect )
{
    CDBManager & aDM = CDBManager::GetInstance();
    JMLib::string aAddr = L"tcp://192.168.35.203:3306";
    JMLib::string aUser = L"db_master";
    JMLib::string aPass = L"master";
    JMLib::string aDBName = L"world";

    EXPECT_TRUE( aDM.Connect( aAddr, aUser, aPass, aDBName ) );
    EXPECT_TRUE( aDM.Close() );
    EXPECT_TRUE( aDM.Connect( aAddr, aUser, aPass, aDBName ) );
    EXPECT_TRUE( aDM.Close() );
    EXPECT_TRUE( aDM.Connect( aAddr, aUser, aPass, aDBName ) );
    EXPECT_TRUE( aDM.Close() );
}

TEST( DBLibTest, ResultSet ) 
{
    CDBManager & aDM = CDBManager::GetInstance();
    JMLib::string aAddr = L"tcp://192.168.35.203:3306";
    JMLib::string aUser = L"db_master";
    JMLib::string aPass = L"master";
    JMLib::string aDBName = L"world";

    EXPECT_TRUE( aDM.Connect( aAddr, aUser, aPass, aDBName ) );
    JMLib::string aQueryBase = L"SELECT COUNT(*) FROM city ";

    JMLib::string aQuery;
    aQuery << aQueryBase ;
    {
        result aRet = aDM.ExecuteStatement( aQuery );
        while( aRet->FetchNext() ) 
        {
            JMLib::uint32 aCount = aRet->GetUInt( 1 );
            EXPECT_EQ( aCount, 4079 );
        }
    }
    aQueryBase = L"SELECT ID, Name, CountryCode, District, Population FROM city ";
    JMLib::string aQueryWhere = L"WHERE ID = 1";
    aQuery.Clear();
    aQuery << aQueryBase << aQueryBase;
    {
        result aRet = aDM.ExecuteStatement( aQuery );
        while( aRet->FetchNext() ) 
        {
            JMLib::uint32 aID = aRet->GetUInt( L"ID" );
            JMLib::string aName = aRet->GetString( L"Name" );
            JMLib::string aCountryCode = aRet->GetString( L"CountryCode" );
            JMLib::string aDistrict = aRet->GetString( L"District" );
            JMLib::uint32 aPop = aRet->GetUInt( L"Population" );
            EXPECT_EQ( aID, 1 );
            EXPECT_STREQ( aName.c_str(), L"Kabul" );
            EXPECT_STREQ( aCountryCode.c_str(), L"AFG" );
            EXPECT_STREQ( aDistrict.c_str(), L"Kabol");
            EXPECT_EQ( aPop, 1780000 );
        }
    }
    aQueryBase = L"SELECT Name, CountryCode FROM city ";
    aQueryWhere = L"WHERE ID >= 1 AND ID <= 10";
    aQuery.Clear();
    aQuery << aQueryBase << aQueryWhere;
    {
        result aRet = aDM.ExecuteStatement( aQuery );
        JMLib::string aName[10] = { L"Kabul", L"Qandahar", L"Herat", 
            L"Mazar-e-Sharif", L"Amsterdam", L"Rotterdam", 
            L"Haag", L"Utrecht", L"Eindhoven", L"Tilburg"};
        JMLib::string aCountryCode[10] = { L"AFG", L"AFG", L"AFG", L"AFG",
            L"NLD", L"NLD", L"NLD", L"NLD", L"NLD", L"NLD" };
        JMLib::uint32 i = 0;
        while( aRet->FetchNext() )
        {
            JMLib::string aStr = aRet->GetString( 1 );
            EXPECT_STREQ( aStr.c_str(), aName[i].c_str() );
            JMLib::string aStr2 = aRet->GetString( 2 );
            EXPECT_STREQ( aStr2.c_str(), aCountryCode[i].c_str() );
            i++;
        }
        EXPECT_EQ( i, 10 );
    }

    EXPECT_TRUE( aDM.Close() );
}