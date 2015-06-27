/*
    Project FreeAX25
    Copyright (C) 2015  tania@df9ry.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/** @file */

#ifndef FREEAX25_RUNTIME_ENVIRONMENT_H_
#define FREEAX25_RUNTIME_ENVIRONMENT_H_

#include "ChannelProxy.h"
#include "ChannelProxy.h"
#include "Logger.h"
#include "TimerManager.h"
#include "Configuration.h"
#include "SharedPointerDict.h"

/**
 * All components of the FreeAX25 projects are located in this namespace.
 */
namespace FreeAX25 {

	/**
	 * All components of the common FreeAX25 runtime are located in this namespace.
	 */
	namespace Runtime {

		/**
		 * The class Environment provides a single distribution point
		 * for "global" data structures.
		 */
		class Environment {
		public:

			/**
			 * Constructor.
			 */
			Environment();

			/**
			 * Destructor.
			 */
			~Environment();

			/**
			 * Environment can not be copied.
			 * @param other Not used.
			 */
			Environment(const Environment& other) = delete;

			/**
			 * Environment can not be moved.
			 * @param other Not used.
			 */
			Environment(Environment&& other) = delete;

			/**
			 * Environment can not be copy assigned.
			 * @param other Not used.
			 * @return Not used.
			 */
			Environment& operator=(const Environment& other) = delete;

			/**
			 * Environment can not be move assigned.
			 * @param other Not used.
			 * @return Not used.
			 */
			Environment& operator=(Environment&& other) = delete;

			/**
			 * Logger service.
			 */
			Logger logger{};

			/**
			 * Timer service.
			 */
			TimerManager timerManager{};

			/**
			 * Configuration info.
			 */
			Configuration configuration{};

			/**
			 * Server proxies.
			 */
			SharedPointerDict<ChannelProxy> serverProxies{};


			/**
			 * Write a DEBUG log message
			 * @param msg The message to log
			 */
			inline void logDebug(const std::string& msg) {
				logger.log(LogLevel::DEBUG, msg);
			}

			/**
			 * Write a INFO log message
			 * @param msg The message to log
			 */
			inline void logInfo(const std::string& msg) {
				logger.log(LogLevel::INFO, msg);
			}

			/**
			 * Write a WARNING log message
			 * @param msg The message to log
			 */
			inline void logWarning(const std::string& msg) {
				logger.log(LogLevel::WARNING, msg);
			}

			/**
			 * Write a ERROR log message
			 * @param msg The message to log
			 */
			void logError(const std::string& msg) {
				logger.log(LogLevel::ERROR, msg);
			}
		};

		/**
		 * Get global environment.
		 */
		Environment& env();

		/**
		 * Set global environment. Can only done once.
		 * @param e Pointer to new global environment.
		 */
		void env(Environment* e);

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_ENVIRONMENT_H_ */
