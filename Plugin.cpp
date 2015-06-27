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

#include "Plugin.h"
#include "Environment.h"

#include <cassert>

using namespace std;

namespace FreeAX25 {
	namespace Runtime {

		Plugin::Plugin() : m_name(""), m_file("") {}

		Plugin::Plugin(const std::string& name, const std::string& file) :
			m_name(name), m_file(file) {}

		Plugin::~Plugin() {
		}

		void Plugin::load() {
			env().logInfo("Loading plugin \"" + m_name + "\"");
			unique_ptr<vector<void*>> pointers =
					m_lo.load(m_file, { "init", "start" });
			vector<void*> _pointers{ *pointers.get() };
			assert(_pointers.size() == 2);
			m_init = (void(*)(const Plugin&)) _pointers[0];
			m_start = (void(*)()) _pointers[1];
		}

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */
