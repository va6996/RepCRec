cmake_minimum_required(VERSION 3.20)
project(RepCRec)

set(CMAKE_CXX_STANDARD 14)

add_executable(RepCRec main.cpp Transactions/Commands/CmdType.h Transactions/TxnType.h Locking/LockType.h ErrorCodes.h Deadlocks/DeadlockManager.cpp Deadlocks/DeadlockManager.h DataTypes/Variable.cpp DataTypes/Variable.h Locking/Lock.cpp Locking/Lock.h Transactions/Transaction.cpp Transactions/Transaction.h Transactions/Commands/Command.cpp Transactions/Commands/Command.h Locking/LockManager.cpp Locking/LockManager.h Sites/Site.cpp Sites/Site.h Sites/SiteManager.cpp Sites/SiteManager.h Transactions/TransactionManager.cpp Transactions/TransactionManager.h Driver/Driver.cpp Driver/Driver.h Sites/SiteStatus.h Clock/GlobalClock.cpp Clock/GlobalClock.h Locking/LockCodes.h)
