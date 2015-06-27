/*
    Project FreeAX25 Runtime
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

#ifndef FREEAX25_RUNTIME_CHANNEL_H_
#define FREEAX25_RUNTIME_CHANNEL_H_

#include "ChannelProxy.h"

#include <JsonXValue.h>

#include <memory>
#include <functional>

namespace FreeAX25 {
	namespace Runtime {

		class SessionBase;

		/**
		 * A Channel is a device to send and receive to other peers.
		 */
		class Channel {
			friend class SessionBase;
			friend class ChannelProxy;

		public:
			/**
			 * Default constructor;
			 */
			Channel() = delete;

			/**
			 * Constructor.
			 * @param session Session this channel is attached to.
			 */
			Channel(std::shared_ptr<SessionBase> session):
				m_session{session}, m_local{ChannelProxy(this)} {}

			/**
			 * Destructor.
			 */
			~Channel() {};

			/**
			 * Connect a channel.
			 * @param target ChannelProxy to send the connect to.
			 * @param parameter Parameter for connect.
			 */
			void connect(
					ChannelProxy target,
					std::unique_ptr<JsonX::Object>&& parameter);

			/**
			 * Connect a channel.
			 * @param target ChannelProxy to send the connect to.
			 */
			void connect(ChannelProxy target)
			{
				return connect(target, JsonX::Object::make());
			}

			/**
			 * Open connection. This should be the first call after
			 * a connect.
			 * @param parameter Parameter for open.
			 */
			void open(std::unique_ptr<JsonX::Object>&& parameter);

			/**
			 * Open connection. This should be the first call after
			 * a connect.
			 */
			void open() {
				open(JsonX::Object::make());
			}

			/**
			 * Close connection. This should be the last call.
			 * @param parameter Parameter for close.
			 */
			void close(std::unique_ptr<JsonX::Object>&& parameter);

			/**
			 * Close connection. This should be the last call.
			 */
			void close() {
				close(JsonX::Object::make());
			}

			/**
			 * Send a message.
			 * @param message Message to send.
			 * @param priority Message priority.
			 */
			void send(
					std::unique_ptr<JsonX::Object>&& message,
					MessagePriority priority = MessagePriority::ROUTINE);

			/**
			 * Send a request.
			 * @param request Request to send.
			 * @return Response received.
			 */
			std::unique_ptr<JsonX::Object> ctrl(
					std::unique_ptr<JsonX::Object>&& request);

			/**
			 * Set this function to receive connect requests.
			 */
			std::function<ChannelProxy(ChannelProxy, std::unique_ptr<JsonX::Object>&&)>
				connectFunction{};

			/**
			 * Set this function to receive open requests.
			 */
			std::function<void(std::unique_ptr<JsonX::Object>&&)>
				openFunction{};

			/**
			 * Set this function to receive close requests.
			 */
			std::function<void(std::unique_ptr<JsonX::Object>&&)>
				closeFunction{};

			/**
			 * Set this function to receive send requests.
			 */
			std::function<void(std::unique_ptr<JsonX::Object>&&, MessagePriority)>
				receiveFunction{};

			/**
			 * Set this function to receive control requests.
			 */
			std::function<std::unique_ptr<JsonX::Object>(std::unique_ptr<JsonX::Object>&&)>
				ctrlFunction{};

			/**
			 * Get a proxy to local channel.
			 * @return ChannelProxy.
			 */
			ChannelProxy getLocalProxy() { return m_local; }

			/**
			 * Get a proxy to remote channel.
			 * @return ChannelProxy.
			 */
			ChannelProxy getRemoteProxy() { return m_remote; }

			/**
			 * Reset the channel. It is not usable after that.
			 */
			void reset() {
				connectFunction = nullptr;
				openFunction = nullptr;
				closeFunction = nullptr;
				receiveFunction = nullptr;
				ctrlFunction = nullptr;
				m_session.reset();
				m_remote.reset();
				m_local.reset(); // Might call delete!
			}

		private:
			ChannelProxy onRemoteConnect(ChannelProxy backlink, std::unique_ptr<JsonX::Object>&& parameter);
			void onRemoteOpen(std::unique_ptr<JsonX::Object>&& parameter);
			void onRemoteClose(std::unique_ptr<JsonX::Object>&& parameter);
			void onRemoteSend(std::unique_ptr<JsonX::Object>&& message, MessagePriority priority);
			std::unique_ptr<JsonX::Object> onRemoteCtrl(std::unique_ptr<JsonX::Object>&& request);

			std::shared_ptr<SessionBase> m_session;
			ChannelProxy                 m_local;
			ChannelProxy                 m_remote{};
		};

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_CHANNEL_H_ */
