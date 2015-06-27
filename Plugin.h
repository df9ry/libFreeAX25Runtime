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

#ifndef FREEAX25_RUNTIME_PLUGIN_H_
#define FREEAX25_RUNTIME_PLUGIN_H_

#include "Instance.h"
#include "Setting.h"
#include "UniquePointerDict.h"
#include "LoadableObject.h"

#include <string>

namespace FreeAX25 {
	namespace Runtime {

		/**
		 * Configuration item that describes a plugin.
		 */
		class Plugin {
		public:
			/**
			 * Default constructor.
			 */
			Plugin();

			/**
			 * Constructor
			 * @param name Name of this plugin
			 * @param file Filename of the so to load.
			 */
			Plugin(const std::string& name, const std::string& file);

			/**
			 * You can not copy a plugin.
			 * @param other Not used.
			 */
			Plugin(const Plugin& other) = delete;

			/**
			 * You can not move a plugin.
			 * @param other not used.
			 */
			Plugin(Plugin&& other) = delete;

			/**
			 * You can not copy assign a Plugin.
			 * @param other Not used.
			 * @return Not used.
			 */
			Plugin& operator=(const Plugin& other) = delete;

			/**
			 * You can not move a plugin.
			 * @param other Not used.
			 * @return Not used.
			 */
			Plugin& operator=(Plugin&& other) = delete;

			/**
			 * Destructor
			 */
			~Plugin();

			/**
			 * Settings of this plugin
			 */
			UniquePointerDict<Setting> settings{};

			/**
			 * Instance of this plugin
			 */
			UniquePointerDict<Instance> instances{};

			/**
			 * Get the plugin name
			 * @return plugin name
			 */
			const std::string& getName() const { return m_name; }

			/**
			 * Get the plugin file
			 * @return plugin file
			 */
			const std::string& getFile() const { return m_file; }

			/**
			 * Load and link the shared object or builtin
			 */
			void load();

			/**
			 * Initialize this plugin.
			 */
			void init() {
				if (m_init) m_init(*this);
			}

			/**
			 * Start this plugin.
			 */
			void start() {
				if (m_start) m_start();
			}

		private:
			const std::string m_name;
			const std::string m_file;
			LoadableObject    m_lo;
			void(*m_init)(const Plugin& p){ nullptr };
			void(*m_start)(){ nullptr };
		};

	} /* end namespace Runtime */

} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_PLUGIN_H_ */
