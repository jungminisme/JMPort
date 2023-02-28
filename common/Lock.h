#pragma once
#include <mutex>

namespace JMLib
{
    /// @brief  stl의 mutex를 JMLib의 기본 Lock 객체로 사용
    typedef std::mutex lock;
    /// @brief  function scope 안에서만 lock이 걸리도록 lockguard를 정의
    typedef std::lock_guard<std::mutex> lockguard;
}