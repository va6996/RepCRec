//
// Created by Vinayak Agarwal on 12/4/21.
//

#ifndef REPCREC_SITEMANAGER_H
#define REPCREC_SITEMANAGER_H

#include <map>
#include "Site.h"
#include <iterator>

/**
 * Class representing a site manager that maintains all site info and is the only way to communicate to
 * any site.
 */
class SiteManager {
		map<int, Site *> sites;
		map<int, set<string>> cfg;
		map<int, set<string>> soleOwner;
		map<string, set<int>> reverseCfg;
public:
		SiteManager(const map<int, set<string>> &cfg);

		/**
		 * Reads data for the given command
		 * @param cmd The command
		 * @return Pair containing the result and the site# from which the data was retrieved
		 */
		pair<string, int> read(Command *cmd);

		/**
		 * Acquires the lock required by the command.
		 * @param cmd The command
		 * @return LockCode indicating success/failure along with LockType
		 */
		LockCodes getWriteLock(Command *cmd);

		/**
		 * This is called when a read/write fails. Gives the list of transactions that have conflicting locks
		 * @param cmd The command
		 * @return The set of conflicting transactions
		 */
		set<string> getConflictingLocks(Command *cmd);

		/**
		 * Write data in a temporary storage
		 * @param cmd The command
		 * @return list of sites on which the data has been written
		 */
		vector<int> stage(Command *cmd);

		/**
		 * Release all the locks associated with the transaction
		 * @param txn The transaction
		 */
		void abort(Transaction *txn);

		/**
		 * Make the write permanent by moving staged data to permanent store for each given site
		 * @param var The variable to commit
		 * @param commitSites list of sites that contain the staged data
		 */
		void commit(set<int> commitSites, string var);

		/**
		 * Tells whether a given site was down after a given time
		 * @param sites list of sites to check
		 * @param time the given time
		 * @return whether any given site was down
		 */
		bool wasSiteDownAfter(set<int> sites, int time);

		/**
		 * Prints complete data stored on each site.
		 */
		void dump();

		/**
		 * Fails the given site. Makes lock manager lose all its data.
		 * @param nodeId the node to fail
		 */
		void fail(int nodeId);

		/**
		 * Recovers the given site. Re-initializes lock manager.
		 * @param nodeId the node to recover
		 */
		void recover(int nodeId);
};


#endif //REPCREC_SITEMANAGER_H
