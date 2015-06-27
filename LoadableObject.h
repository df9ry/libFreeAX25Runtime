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

#ifndef FREEAX25_RUNTIME_LOADABLEOBJECT_H_
#define FREEAX25_RUNTIME_LOADABLEOBJECT_H_

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

namespace FreeAX25 {
	namespace Runtime {

		/**
		 * RAII support for loadable objects (so).
		 */
		class LoadableObject {
		public:
			/**
			 * Constructor.
			 */
			LoadableObject();

			/**
			 * Destructor.
			 */
			~LoadableObject();

			/**
			 * Load the shared object. Can only called once.
			 * @param filename Name of the file to load.
			 * @param entries Name of entry points to resolve.
			 * @return Vector of entry points. Size and order of the
			 * 		   returned pointers corresponds to parameter
			 * 		   entries.
			 */
			std::unique_ptr<std::vector<void*>> load(
				const std::string& filename,
				std::initializer_list<std::string> entries);

		private:
			void* m_handle{ nullptr };
			bool  m_loaded{ false };
		};

	} /* namespace Runtime */

} /* namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_LOADABLEOBJECT_H_ */
