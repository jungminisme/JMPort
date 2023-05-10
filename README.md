# JMPort
JungMin's Project for Portfolio

포트폴리오를 위한 프로젝트 입니다. 
코드 작성 스타일, 기본적인 라이브러리 활용, 객체지향 구조 설계 방식 등을 보여주기 위해 작성되었습니다. 

1. 개발 환경
OS : ubuntu 22.04
compiler : g++ 11.3.0
db : mysql Ver 8.0.33 
tools : VSCode, CMake, WSL, gtest

2. 구현 내용
1) common 
string : std::wsstring을 사용상 편의를 위하여 wrapping 하였음. UNICODE 사용
file : fwstream을 wrapping하여 사용, Logger및 기본 입출력 용도
logger : console, file, null logger등을 구현. 

2) dblib
mysql cppconnector 사용
unicode 문자열을 이용한 입출력 구현

3) netlib
epoll 서버 구현 : epoll을 이용한 다중 접속 서버 구현. 
packet IO 구현 : 기본 데이터 처리를 위한 입출력 패킷 구현
callback 구조 도입 : lambda function을 인자로 받아 처리할수 잇는 기본 구조 구현

3. 미구현 내용
1) multi thread : network 자체 IO 및 contents와의 연결을 위하여 필요하지만 포트폴리오에서는 생략 
2) contents용 container : account 관리및 player관리 객체 역시 포트폴리오에서 생략 

4. 기타 
c++ 17 에 기반하여 작성을 하였습니다. 
테스트를 위한 client는 android 환경의 kotlin으로 작성한 app이 사용되었습니다. (코드를 포함하지는 않음) 
최종 수정일 : 2023. 05. 10
