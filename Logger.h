/*
    Project FreeAX25_Runtime
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

#ifndef FREEAX25_RUNTIME_LOGGER_H_
#define FREEAX25_RUNTIME_LOGGER_H_

#include <string>

/**
 * Error logging macro.
 */
#define ERR(x) \
	if (::FreeAX25::Runtime::env().logger.getLevel() >= ::FreeAX25::Runtime::LogLevel::ERROR) \
		do { ::FreeAX25::Runtime::env().logger.log(::FreeAX25::Runtime::LogLevel::ERROR, x); } \
			while(false)

/**
 * Warning logging macro.
 */
#define WRN(x) \
	if (::FreeAX25::Runtime::env().logger.getLevel() >= ::FreeAX25::Runtime::LogLevel::WARNING) \
		do { ::FreeAX25::Runtime::env().logger.log(::FreeAX25::Runtime::LogLevel::WARNING, x); } \
			while(false)

/**
 * Info logging macro.
 */
#define INF(x) \
	if (::FreeAX25::Runtime::env().logger.getLevel() >= ::FreeAX25::Runtime::LogLevel::INFO) \
		do { ::FreeAX25::Runtime::env().logger.log(::FreeAX25::Runtime::LogLevel::INFO, x); } \
			while(false)

/**
 * Debug logging macro.
 */
#define DBG(x) \
	if (::FreeAX25::Runtime::env().logger.getLevel() >= ::FreeAX25::Runtime::LogLevel::DEBUG) \
		do { ::FreeAX25::Runtime::env().logger.log(::FreeAX25::Runtime::LogLevel::DEBUG, x); } \
			while(false)

namespace FreeAX25 {
	namespace Runtime {

		/**
		 * Specifies the weight of a log message.
		 */
		enum class LogLevel {
			NONE,   //!< NONE
			ERROR,  //!< ERROR
			WARNING,//!< WARNING
			INFO,   //!< INFO
			DEBUG   //!< DEBUG
		};

		/**
		 * Global logging utility.
		 */
		class Logger {
		public:

			/**
			 * Constructor
			 */
			Logger();

			/**
			 * You can not copy a Logger.
			 * @param other Not used.
			 */
			Logger(const Logger& other) = delete;

			/**
			 * You can not move a logger.
			 * @param other Not used.
			 */
			Logger(Logger&& other) = delete;

			/**
			 * You can not assign a Logger.
			 * @param other Not used.
			 * @return Not used.
			 */
			Logger& operator=(const Logger& other) = delete;

			/**
			 * You can not assign a Logger.
			 * @param other Not used.
			 * @return Not used.
			 */
			Logger& operator=(Logger&& other) = delete;

			/**
			 * Destructor
			 */
			~Logger();

			/**
			 * Initialize the Logger
			 */
			void init();

			/**
			 * Set the log level
			 */
			inline void setLevel(LogLevel l) {
				m_level = l;
			}

			/**
			 * Get the log level
			 */
			inline LogLevel getLevel() const {
				return m_level;
			}

			/**
			 * Log an error
			 */
			inline void logError(const std::string& msg) {
				log(LogLevel::ERROR, msg);
			}

			/**
			 * Log a warning
			 */
			inline void logWarning(const std::string& msg) {
				log(LogLevel::WARNING, msg);
			}

			/**
			 * Log an info
			 */
			inline void logInfo(const std::string& msg) {
				log(LogLevel::INFO, msg);
			}

			/**
			 * Log a debug
			 */
			inline void logDebug(const std::string& msg) {
				log(LogLevel::DEBUG, msg);
			}

			/**
			 * Write to log
			 */
			inline void log(LogLevel l, const std::string& msg) {
				if (l <= m_level) _log(l, msg);
			}

			/**
			 * Returns a log level corresponding to given string s. Throws
			 * exception when no log level matches.
			 * @param s The textual log level
			 * @return The decoded log level
			 */
			static LogLevel decode(const std::string& s);

		private:
			LogLevel m_level{ LogLevel::NONE };
			void _log(LogLevel l, const std::string& msg);
		};

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_LOGGER_H_ */
