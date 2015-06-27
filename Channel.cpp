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

#include "Channel.h"
#include "Environment.h"

#include <stdexcept>
#include <string>

using namespace std;

namespace FreeAX25 {
	namespace Runtime {

		void Channel::connect(ChannelProxy target, std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (m_remote) throw runtime_error("Already connected");
			m_remote = target.connect(getLocalProxy(), move(parameter));
		}

		void Channel::open(std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!m_remote) throw runtime_error("Not connected");
			m_remote.open(move(parameter));
		}

		void Channel::close(std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!m_remote) throw runtime_error("Not connected");
			m_remote.close(move(parameter));
			m_remote.reset();
		}

		void Channel::send(std::unique_ptr<JsonX::Object>&& message, MessagePriority priority)
		{
			if (!m_remote) throw runtime_error("Not connected");
			m_remote.send(move(message), priority);
		}

		std::unique_ptr<JsonX::Object> Channel::ctrl(std::unique_ptr<JsonX::Object>&& request)
		{
			if (!m_remote) throw runtime_error("Not connected");
			return m_remote.ctrl(move(request));
		}

		ChannelProxy Channel::onRemoteConnect(ChannelProxy backlink, std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!connectFunction) throw runtime_error("Connect not supported");
			return connectFunction(backlink, move(parameter));
		}

		void Channel::onRemoteOpen(std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!openFunction) throw runtime_error("Open not supported");
			openFunction(move(parameter));
		}

		void Channel::onRemoteClose(std::unique_ptr<JsonX::Object>&& parameter)
		{
			if (!closeFunction) throw runtime_error("Close not supported");
			closeFunction(move(parameter));
		}

		void Channel::onRemoteSend(std::unique_ptr<JsonX::Object>&& message, MessagePriority priority)
		{
			if (!receiveFunction) throw runtime_error("Receive not supported");
			receiveFunction(move(message), priority);
		}

		std::unique_ptr<JsonX::Object> Channel::onRemoteCtrl(std::unique_ptr<JsonX::Object>&& request)
		{
			if (!ctrlFunction) throw runtime_error("Control not supported");
			return ctrlFunction(move(request));
		}

	} /* end namespace Runtime */
} /* namespace FreeAX25 */
