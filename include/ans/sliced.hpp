#ifndef ANS_SLICED_HPP
#define ANS_SLICED_HPP

/*
@author: Answeror
@description: 

Modified "boost/range/adaptor/sliced.hpp" to make it compatiable with InputRange
like boost::irange.
In the other word, make following code run correctly:

    distance(irange(0, 10) | sliced(0, 3))

The result order to be 3.

The reason boost::adaptor::sliced don't work is due to "u - boost::size(rng)"
in "boost\range\adaptor\sliced.hpp" line 37.
The underline boost::make_iterator_range use std::advance to make the end
iterator of input range go backward. However, irange(0, 10) is InputRange, so
std::advance can only go forward and leave the end iterator not changed.

In this file, I make it work with ForwardRange and other advanced category.

I just don't understand why make_range_impl in
"boost\range\iterator_range_core.hpp" make end iterator go backward rather than
make begin iterator go forward.
*/

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/size_type.hpp>
#include <boost/range/iterator_range.hpp>

namespace ans
{
    namespace adaptors
    {
        struct sliced
        {
            sliced(std::size_t t_, std::size_t u_)
                : t(t_), u(u_) {}
            std::size_t t;
            std::size_t u;
        };

		template< class ForwardRange >
		class sliced_range : public boost::iterator_range< BOOST_DEDUCED_TYPENAME boost::range_iterator<ForwardRange>::type >
		{
			typedef boost::iterator_range< BOOST_DEDUCED_TYPENAME boost::range_iterator<ForwardRange>::type > base_t;
		public:
			template<typename Rng, typename T, typename U>
			sliced_range(Rng& rng, T t, U u)
				: base_t(make_range(rng, t, u/* - boost::size(rng)*/))
			{
			}
			
			template< class Range >
            inline boost::iterator_range< BOOST_DEDUCED_TYPENAME boost::range_iterator<Range>::type >
            make_range( Range& r,
                             BOOST_DEDUCED_TYPENAME boost::range_difference<Range>::type advance_begin,
                             BOOST_DEDUCED_TYPENAME boost::range_difference<Range>::type advance_end )
            {
                BOOST_DEDUCED_TYPENAME boost::range_iterator<Range>::type
                    new_begin = boost::begin( r ),
                    new_end   = boost::begin( r );
                std::advance( new_begin, advance_begin );
                std::advance( new_end, advance_end );
                return boost::make_iterator_range( new_begin, new_end );
            }
		};

		template< class ForwardRange >
		inline sliced_range<ForwardRange>
		slice( ForwardRange& rng, std::size_t t, std::size_t u )
		{
			BOOST_ASSERT( t <= u && "error in slice indices" );
            BOOST_ASSERT( static_cast<std::size_t>(boost::distance(rng)) >= u &&
						  "second slice index out of bounds" );

			return sliced_range<ForwardRange>(rng, t, u);
		}

		template< class ForwardRange >
		inline boost::iterator_range< BOOST_DEDUCED_TYPENAME boost::range_iterator<const ForwardRange>::type >
		slice( const ForwardRange& rng, std::size_t t, std::size_t u )
		{
		    BOOST_ASSERT( t <= u && "error in slice indices" );
		    BOOST_ASSERT( static_cast<std::size_t>(boost::distance(rng)) >= u &&
		                  "second slice index out of bounds" );

            return sliced_range<const ForwardRange>(rng, t, u);
		}

		template< class ForwardRange >
		inline sliced_range<ForwardRange>
		operator|( ForwardRange& r, const sliced& f )
		{
			return sliced_range<ForwardRange>( r, f.t, f.u );
		}

		template< class ForwardRange >
		inline sliced_range<const ForwardRange>
		operator|( const ForwardRange& r, const sliced& f )
		{
			return sliced_range<const ForwardRange>( r, f.t, f.u );
		}

    } // namespace adaptors
} // namespace ans

#endif
