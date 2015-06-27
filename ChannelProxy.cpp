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

#include <stdexcept>

#include "Channel.h"
#include "ChannelProxy.h"
#include "SessionBase.h"

using namespace std;
using namespace JsonX;

namespace FreeAX25 {
	namespace Runtime {

		ChannelProxy::ChannelProxy():
				m_channel{ nullptr },
				m_session{ shared_ptr<SessionBase>{nullptr} }
		{
		}

		ChannelProxy::ChannelProxy(Channel* channel):
				m_channel{ channel },
				m_session{ channel->m_session }
		{
		}

		ChannelProxy::~ChannelProxy()
		{
		}

		ChannelProxy ChannelProxy::connect(ChannelProxy backlink, std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!m_channel) throw runtime_error("Connection closed");
			return m_channel->onRemoteConnect(backlink, move(parameter));
		}

		void ChannelProxy::open(std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!m_channel) throw runtime_error("Connection closed");
			m_channel->onRemoteOpen(move(parameter));
		}

		void ChannelProxy::close(std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!m_channel) throw runtime_error("Connection closed");
			m_channel->onRemoteClose(move(parameter));
		}

		void ChannelProxy::send(std::unique_ptr<JsonX::Object>&& message,
				MessagePriority priority)
		{
			if (!m_channel) throw runtime_error("Connection closed");
			m_channel->onRemoteSend(move(message), priority);
		}

		std::unique_ptr<JsonX::Object> ChannelProxy::ctrl(std::unique_ptr<JsonX::Object>&& request)
		{
			if (!m_channel) throw runtime_error("Connection closed");
			return m_channel->onRemoteCtrl(move(request));
		}

		void ChannelProxy::reset()
		{
			m_channel = nullptr;
			m_session.reset(); // This may call the destructor!
		}

		static const string nullId = "null";

		const std::string& ChannelProxy::id() const {
			return m_session ? m_session.get()->id() : nullId;
		}

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */
