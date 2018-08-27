/*
 *
 * Copyright 2018 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ASYLO_PLATFORM_CORE_ATOMIC_H_
#define ASYLO_PLATFORM_CORE_ATOMIC_H_

#include <cstdlib>

namespace asylo {

// Atomically compare the value at `location` to `expected` and, if-and-only-if
// they match, replace the value at `location` with `desired`. Returns the value
// stored `location` prior to the attempted exchange.
template <typename T>
inline T CompareAndSwap(volatile T *location, T expected, T desired) {
  T previous = expected;
  __atomic_compare_exchange_n(location,
                              /*expected=*/&previous,
                              /*desired=*/desired,
                              /*weak=*/false,
                              /*success_memorder=*/__ATOMIC_SEQ_CST,
                              /*failure_memorder=*/__ATOMIC_SEQ_CST);
  return previous;
}

// Atomically decrements the value at `location`, returning the value at
// `location` prior to being decremented.
template <typename T>
inline T AtomicDecrement(volatile T *location) {
  return __atomic_fetch_sub(location, 1, __ATOMIC_SEQ_CST);
}

// Sets the value at location to zero using __ATOMIC_RELEASE memory ordering.
template <typename T>
inline void AtomicRelease(volatile T *location) {
  __atomic_clear(location, __ATOMIC_RELEASE);
}

// The size of an x86-64 cache line.
//
constexpr size_t kCacheLineSize = 64;

}  // namespace asylo

#endif  // ASYLO_PLATFORM_CORE_ATOMIC_H_
