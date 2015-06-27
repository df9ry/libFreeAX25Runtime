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

#ifndef FREEAX25_RUNTIME_UNIQUEPOINTERDICT_H_
#define FREEAX25_RUNTIME_UNIQUEPOINTERDICT_H_

#include "PointerDict.h"

namespace FreeAX25 {
	namespace Runtime {

		/**
		 * Typename for pointer.
		 */
		template <typename T>
		using UniquePointer = ::std::unique_ptr < T > ;

		/**
		 * Typename for base class.
		 */
		template <typename T>
		using UniquePointerDictBase = PointerDictBase < T, UniquePointer<T> > ;

		/**
		 * Typename for pairs.
		 */
		template <typename T>
		using UniquePointerDictPair = PointerDictPair < T, UniquePointer<T> > ;

		/**
		 * Typename for iterator.
		 */
		template <typename T>
		using UniquePointerDictIterator = PointerDictIterator < T, UniquePointer<T> > ;

		/**
		 * Typename for const iterator
		 */
		template <typename T>
		using UniquePointerDictConstIterator = PointerDictConstIterator < T, UniquePointer<T> > ;

		/**
		 * Template for hashed maps with string keys and unique_ptr support.
		 */
		template <typename T>
		using UniquePointerDict = class PointerDict < T, UniquePointer<T> >;

	} /* end namespace Runtime */
} /* namespace FreeAX25 */

#endif /* FREEAX25_RUNTIME_UNIQUEPOINTERDICT_H_ */
