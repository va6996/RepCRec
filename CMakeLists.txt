cmake_minimum_required(VERSION 3.20)
project(RepCRec)

set(CMAKE_CXX_STANDARD 14)

add_executable(RepCRec main.cpp CmdType.cpp CmdType.h TxnType.cpp TxnType.h LockType.cpp LockType.h ErrorCodes.cpp ErrorCodes.h Graph.cpp Graph.h DeadlockManager.cpp DeadlockManager.h Variable.cpp Variable.h Lock.cpp Lock.h Transaction.cpp Transaction.h Command.cpp Command.h LockManager.cpp LockManager.h Site.cpp Site.h SiteManager.cpp SiteManager.h TransactionManager.cpp TransactionManager.h Driver.cpp Driver.h)
