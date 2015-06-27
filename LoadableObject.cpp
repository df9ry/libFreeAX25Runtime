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

#include "LoadableObject.h"

#include <dlfcn.h>

using namespace std;

namespace FreeAX25 {
	namespace Runtime {

		LoadableObject::LoadableObject() {
		}

		LoadableObject::~LoadableObject() {
			if (m_loaded)
				dlclose(m_handle);
		}

		std::unique_ptr<std::vector<void*>> LoadableObject::load(
			const std::string& filename,
			std::initializer_list<std::string> entries)

		{
			if (m_loaded) throw runtime_error("LoadableObject already loaded");
			char* error;
			m_handle = dlopen(filename.c_str(), RTLD_NOW);
			if (!m_handle) throw runtime_error(
				"Unable to load " + filename + "! Cause: " + dlerror());
			m_loaded = true;
			dlerror(); // Clear error messages
			unique_ptr<vector<void*>> pointers{ new vector<void*>(entries.size()) };
			int i = 0;
			vector<void*>& _pointers{ *pointers.get() };
			for(auto entry: entries) {
				_pointers[i++] = dlsym(m_handle, entry.c_str());
				error = dlerror();
				if (error != nullptr) throw runtime_error(
					"Unable to link \"" + entry + "\" from " + filename +
					"! Cause: " + error);
			} // end for //
			return move(pointers);
		}

	} /* namespace Runtime */
} /* namespace FreeAX25 */
