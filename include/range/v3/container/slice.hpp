// Range v3 library
//
//  Copyright Eric Niebler 2013-2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_CONTAINER_SLICE_HPP
#define RANGES_V3_CONTAINER_SLICE_HPP

#include <functional>
#include <range/v3/range_fwd.hpp>
#include <range/v3/container/action.hpp>
#include <range/v3/container/erase.hpp>
#include <range/v3/utility/functional.hpp>
#include <range/v3/utility/iterator_concepts.hpp>
#include <range/v3/utility/iterator_traits.hpp>

namespace ranges
{
    inline namespace v3
    {
        namespace cont
        {
            struct slice_fn
            {
            private:
                friend action_access;
                template<typename D, CONCEPT_REQUIRES_(Integral<D>())>
                static auto bind(slice_fn slice, D from, D to)
                RANGES_DECLTYPE_AUTO_RETURN
                (
                    std::bind(slice, std::placeholders::_1, from, to)
                )
            public:
                template<typename Rng, typename I = range_iterator_t<Rng>,
                    CONCEPT_REQUIRES_(Iterable<Rng &>() && EraseableIterable<Rng &, I, I>())>
                void operator()(Rng & rng, range_difference_t<Rng> from, range_difference_t<Rng> to) const
                {
                    RANGES_ASSERT(from <= to);
                    cont::erase(rng, next(begin(rng), to), end(rng));
                    cont::erase(rng, begin(rng), next(begin(rng), from));
                }
            };

            RANGES_CONSTEXPR action<slice_fn> slice{};
        }
    }
}

#endif
