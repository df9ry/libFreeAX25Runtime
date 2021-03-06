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

#include "Timer.h"
#include "TimerManager.h"
#include "Environment.h"

#include <cassert>

using namespace std;
using namespace std::chrono;

namespace FreeAX25 {
	namespace Runtime {

		Timer::Timer(
				const std::string& id,
				const std::chrono::steady_clock::duration& d,
				std::function<void()> f) :
			m_id{id},
			m_stdDuration{d},
			m_function{f},
			m_iterator{env().timerManager.m_activeTimers.end()}
		{
			assert(f != nullptr);
		}

		Timer::~Timer() {
			lock_guard<mutex> lock(m_mutex);
			if (m_running) _stop();
		}

		void Timer::_start(const steady_clock::duration& d) {
			//m_environment->logDebug("Start timer " + m_id);
			// Lock the manager:
			lock_guard<mutex> lock(env().timerManager.m_mutex);
			assert(m_iterator == env().timerManager.m_activeTimers.end());
			m_deadline = steady_clock::now() + d;
			m_iterator = env().timerManager.m_activeTimers.insert(
					pair<steady_clock::time_point, Timer&>(m_deadline, *this));
			m_running = true;
		}

		void Timer::_stop() {
			//m_environment->logDebug("Stop timer " + m_id);
			// Lock the manager:
			lock_guard<mutex> lock(env().timerManager.m_mutex);
			m_running = false;
			if (m_iterator == env().timerManager.m_activeTimers.end()) return;
			env().timerManager.m_activeTimers.erase(m_iterator);
			m_iterator = env().timerManager.m_activeTimers.end();
		}

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */
