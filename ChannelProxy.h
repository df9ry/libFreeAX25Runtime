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

#ifndef FREEAX25_RUNTIME_CHANNELPROXY_H_
#define FREEAX25_RUNTIME_CHANNELPROXY_H_

#include <JsonXValue.h>

#include <memory>

namespace FreeAX25 {
	namespace Runtime {

		/**
		 * Message priority.
		 */
		enum class MessagePriority {
			ROUTINE,//!< ROUTINE  Routine delivery
			PRIORITY//!< PRIORITY Express delivery
		};

		class Channel;
		class SessionBase;

		/**
		 * ServerProxies can be used to publish servers. If all
		 * ServerProxies are deleted then the server will be
		 * deleted.
		 */
		class ChannelProxy {
			friend class Channel;

		public:
			/**
			 * Default constructor.
			 */
			ChannelProxy();

			/**
			 * Destructor.
			 */
			~ChannelProxy();

			/**
			 * Test if the server proxy is set.
			 */
			explicit operator bool() const noexcept{ return m_channel; }

			/**
			 * Connect to the channel.
			 * @param backlink ChannelProxy for backlink.
			 * @param parameter Parameter for connect.
			 * @return ServerProxy where subsequent requests can be sent to.
			 */
			ChannelProxy connect(ChannelProxy backlink, std::unique_ptr<JsonX::Object>&& parameter);

			/**
			 * Connect to the channel.
			 * @param backlink ChannelProxy for backlink.
			 * @return ServerProxy where subsequent requests can be sent to.
			 */
			ChannelProxy connect(ChannelProxy backlink) {
				return connect(backlink, JsonX::Object::make());
			}

			/**
			 * Connect to the channel.
			 * @param parameter Parameter for connect.
			 * @return ChannelProxy where subsequent requests can be sent to.
			 */
			ChannelProxy connect(std::unique_ptr<JsonX::Object>&& parameter) {
				return connect(ChannelProxy(), move(parameter));
			}

			/**
			 * Connect to the channel.
			 * @return ChannelProxy where subsequent requests can be sent to.
			 */
			ChannelProxy connect() {
				return connect(ChannelProxy(), JsonX::Object::make());
			}

			/**
			 * Open connection to channel. This should be the first call after
			 * a connect.
			 * @param parameter Parameter for open.
			 */
			void open(std::unique_ptr<JsonX::Object>&& parameter);

			/**
			 * Open connection to channel. This should be the first call after
			 * a connect.
			 */
			void open() {
				open(JsonX::Object::make());
			}

			/**
			 * Close connection to channel. This should be the last call.
			 * @param parameter Parameter for close.
			 */
			void close(std::unique_ptr<JsonX::Object>&& parameter);

			/**
			 * Close connection to channel. This should be the last call.
			 */
			void close() {
				close(JsonX::Object::make());
			}

			/**
			 * Send a message to the channel.
			 * @param message Message to send.
			 * @param priority Message priority.
			 */
			void send(std::unique_ptr<JsonX::Object>&& message,
					MessagePriority priority = MessagePriority::ROUTINE);

			/**
			 * Send a request to the channel.
			 * @param request Request to send.
			 * @return Response from server.
			 */
			std::unique_ptr<JsonX::Object> ctrl(std::unique_ptr<JsonX::Object>&& request);

			/**
			 * Get session id.
			 * @return Session id.
			 */
			const std::string& id() const;

			/**
			 * Get numerical address of the underlying channel. For debugging purposes.
			 * @return Numerical address of the underlying channel.
			 */
			uint64_t addr() const { return (uint64_t)m_channel; }

		private:
			ChannelProxy(Channel* channel);
			void reset();

			Channel*			         m_channel;
			std::shared_ptr<SessionBase> m_session;
		};

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_CHANNELPROXY_H_ */
