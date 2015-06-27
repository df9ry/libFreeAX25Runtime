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

#ifndef FREEAX25_RUNTIME_CLIENTENDPOINT_H_
#define FREEAX25_RUNTIME_CLIENTENDPOINT_H_

#include <string>

namespace FreeAX25 {
	namespace Runtime {

		/**
		 * Client endpoint descriptor, that can be connected to a server
		 * endpoint descriptor, if the URLs matches.
		 */
		class ClientEndPoint {
		public:
			/**
			 * Default constructor.
			 */
			ClientEndPoint() :
				m_name( "" ), m_url( "" ) {}

			/**
			 * Constructor
			 * @param name Name of this ClientEndPoint.
			 * @param url Url of this ClientEndPoint.
			 */
			ClientEndPoint(const std::string& name, const std::string& url) :
				m_name( name ), m_url( url ) {};

			/**
			 * Copy constructor.
			 * @param other Object to copy from.
			 */
			ClientEndPoint(const ClientEndPoint& other) :
				m_name( other.m_name ), m_url( other.m_url ) {}

			/**
			 * Move constructor.
			 * @param other Object to move from.
			 */
			ClientEndPoint(ClientEndPoint&& other) :
				m_name( "" ), m_url( "" )
			{
				std::swap(m_name, other.m_name);
				std::swap(m_url, other.m_url);
			}

			/**
			 * Copy assignment.
			 * @param other Object to copy from.
			 * @return Reference to this.
			 */
			ClientEndPoint& operator=(const ClientEndPoint& other) {
				m_name = other.m_name;
				m_url = other.m_url;
				return *this;
			}

			/**
			 * Move assignment.
			 * @param other Object to move from.
			 * @return Reference to this.
			 */
			ClientEndPoint& operator=(ClientEndPoint&& other) {
				std::swap(m_name, other.m_name);
				std::swap(m_url, other.m_url);
				return *this;
			}

			/**
			 * Destructor
			 */
			~ClientEndPoint() {};

			/**
			 * Get the setting name
			 * @return setting name
			 */
			const std::string getName() const { return m_name; }

			/**
			 * Get the setting name
			 * @return setting name
			 */
			const std::string getUrl() const { return m_url; }

		private:
			std::string m_name;
			std::string m_url;
		};

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_CLIENTENDPOINT_H_ */
