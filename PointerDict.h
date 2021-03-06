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

#ifndef FREEAX25_RUNTIME_POINTERDICT_H_
#define FREEAX25_RUNTIME_POINTERDICT_H_

#include <map>
#include <string>
#include <memory>
#include <exception>

namespace FreeAX25 {
	namespace Runtime {

		/**
		 * Typename for base class.
		 */
		template <typename T, typename P>
		using PointerDictBase = ::std::map < const std::string, P > ;

		/**
		 * Typename for pairs.
		 */
		template <typename T, typename P>
		using PointerDictPair = ::std::pair < const std::string, P > ;

		/**
		 * Typename for iterator.
		 */
		template <typename T, typename P>
		using PointerDictIterator = typename PointerDictBase<T, P>::iterator;

		/**
		 * Typename for const
		 */
		template <typename T, typename P>
		using PointerDictConstIterator = typename PointerDictBase<T, P>::const_iterator;

		/**
		 * Template for hashed maps with string keys and smart pointer support.
		 */
		template <typename T, typename P>
		class PointerDict : public PointerDictBase < T, P > {
		public:

			/**
			 * Constructor
			 */
			PointerDict() {}

			/**
			 * Disallow copy.
			 */
			PointerDict(const PointerDict& other) = delete;

			/**
			 * Disallow move.
			 */
			PointerDict(PointerDict&& other) = delete;

			/**
			 * Destructor
			 */
			~PointerDict() {}

			/**
			 * Disallow assingment.
			 */
			PointerDict& operator=(const PointerDict& other) = delete;

			/**
			 * Disallow assingment.
			 */
			PointerDict& operator=(PointerDict&& other) = delete;

			/**
			 * Insert a value into the map with copy.
			 * @param key Key of the entry.
			 * @param value Value of the entry.
			 * @return Iterator.
			 */
			PointerDictIterator<T, P> insertCopy(const std::string& key, const T& value)
			{
				auto result = PointerDictBase<T, P>::insert(
					PointerDictPair < T, P > {key, P{ new T(value) }});
				if (!result.second)
					throw std::invalid_argument("Double key: " + key);
				return result.first;
			}

			/**
			 * Insert a value into the map with move.
			 * @param key Key of the entry.
			 * @param value Value to move in.
			 * @return Iterator.
			 */
			PointerDictIterator<T, P> insertMove(const std::string& key, T&& value)
			{
				auto result = PointerDictBase<T, P>::insert(
					PointerDictPair < T, P > {key, P{ new T(::std::move(value)) }});
				if (!result.second)
					throw std::invalid_argument("Double key: " + key);
				return result.first;
			}

			/**
			 * Insert a value into the map.
			 * @param key Key of the entry.
			 * @param value Pointer to the new value.
			 * @return Iterator.
			 */
			PointerDictIterator<T, P> insertNew(const std::string& key, T* value)
			{
				auto result = PointerDictBase<T, P>::insert(
					PointerDictPair < T, P > {key, P{ value }});
				if (!result.second)
					throw std::invalid_argument("Double key: " + key);
				return result.first;
			}

			/**
			 * Find entry with key
			 * @param key The key to lookup
			 * @return Value
			 */
			T findEntry(const std::string& key) {
				PointerDictConstIterator<T, P> x = PointerDictBase<T, P>::find(key);
				return (x == PointerDictBase<T, P>::end()) ? T() : T(*(x->second.get()));
			}

			/**
			 * Find entry with key
			 * @param key The key to lookup
			 * @return Value
			 */
			const T& findEntryConst(const std::string& key) const {
				PointerDictConstIterator<T, P> x = PointerDictBase<T, P>::find(key);
				return (x == PointerDictBase<T, P>::end()) ? m_empty : *(x->second.get());
			}

		private:
			const T m_empty{};
		};

	} /* end namespace Runtime */
} /* end namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_POINTERDICT_H_ */
