CC=g++
CFLAGS=-g -std=c++11

Repcrec: main.cpp main.cpp Transactions/Commands/CmdType.h Transactions/TxnType.h Locking/LockType.h Deadlocks/DeadlockManager.cpp Deadlocks/DeadlockManager.h DataTypes/Variable.cpp DataTypes/Variable.h Locking/Lock.cpp Locking/Lock.h Transactions/Transaction.cpp Transactions/Transaction.h Transactions/Commands/Command.h Locking/LockManager.cpp Locking/LockManager.h Sites/Site.cpp Sites/Site.h Sites/SiteManager.cpp Sites/SiteManager.h Transactions/TransactionManager.cpp Transactions/TransactionManager.h Driver/Driver.cpp Driver/Driver.h Sites/SiteStatus.h Clock/GlobalClock.cpp Clock/GlobalClock.h Locking/LockCodes.h
	$(CC) $(CFLAGS) main.cpp -o Repcrec Deadlocks/DeadlockManager.cpp DataTypes/Variable.cpp Locking/Lock.cpp Transactions/Transaction.cpp Locking/LockManager.cpp Sites/Site.cpp Sites/SiteManager.cpp Transactions/TransactionManager.cpp Driver/Driver.cpp Clock/GlobalClock.cpp

clean:
	rm -rf Repcrec