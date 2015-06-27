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

#ifndef FREEAX25_RUNTIME_SERVERBASE_H_
#define FREEAX25_RUNTIME_SERVERBASE_H_

#include "JsonXValue.h"
#include "Channel.h"
#include "ChannelProxy.h"
#include "UUID.h"

#include <memory>
#include <string>

namespace FreeAX25 {
	namespace Runtime {
		class Channel;

		/**
		 * All session objects have to derive from this class
		 */
		class SessionBase {

		public:

			/**
			 * You can not copy a session.
			 * @param other Not used.
			 */
			SessionBase(const SessionBase& other) = delete;

			/**
			 * You can not move a session.
			 * @param other Not used.
			 */
			SessionBase(SessionBase&& other) = delete;

			/**
			 * You can  not assign a session.
			 * @param other Not used.
			 * @return Not used.
			 */
			SessionBase& operator=(const SessionBase& other) = delete;

			/**
			 * You can  not assign a session.
			 * @param other Not used.
			 * @return Not used.
			 */
			SessionBase& operator=(SessionBase&& other) = delete;

			/**
			 * Destructor.
			 */
			virtual ~SessionBase() {}

			/**
			 * Get session id.
			 * @return Session id.
			 */
			const std::string& id() const { return m_id; }

		protected:

			/**
			 * Constructor.
			 */
			SessionBase(const std::string& id = FreeAX25::Runtime::newUUID()):
				m_pointer{std::shared_ptr<SessionBase>(this)}, m_id{id} {}

			/**
			 * Set the remote proxy for a channel.
			 * @param channel The channel to set the remote proxy.
			 * @param proxy The remote proxy.
			 */
			void setRemote(Channel& channel, ChannelProxy& proxy) {
				channel.m_remote = proxy;
			}

			/**
			 * Reset session. This may cause a destruction.
			 */
			virtual void reset()
			{
				m_pointer.reset();
			}

			/**
			 * Shared pointer to self. Used to hold object in memory even if no
			 * other object references it. Reset this pointer to allow deletion.
			 */
			std::shared_ptr<SessionBase> m_pointer;

			/**
			 * ID of this object.
			 */
			const std::string            m_id;
		};

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_SERVERBASE_H_ */
