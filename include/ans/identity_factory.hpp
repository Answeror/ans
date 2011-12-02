#if !defined(__REPRESENTATION_FACTORY_HPP_20111201221514__)
#define __REPRESENTATION_FACTORY_HPP_20111201221514__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-01
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <boost/mpl/quote.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>

#include <boost/fusion/include/unfused.hpp>
#include <boost/fusion/include/invoke.hpp>
#include <boost/fusion/include/intrinsic.hpp>
#include <boost/fusion/include/pop_front.hpp>

#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/functional/forward_adapter.hpp>
#include <boost/functional/factory.hpp>
#include <boost/functional/value_factory.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "tag.hpp"

namespace ans
{
    namespace mpl = boost::mpl;
    namespace bf = boost::fusion;

    namespace tag_detail
    {
        template<class Tag>
        struct shared_if_noncopyable : boost::forward_adapter<
            typename mpl::if_<
                boost::is_base_of<boost::noncopyable, typename Tag::type>,
                boost::factory<boost::shared_ptr<typename Tag::type> >,
                boost::value_factory<typename Tag::type>
                >::type
            > {};

        struct default_factory_metafunction_class : mpl::quote1<shared_if_noncopyable> {};

        template<class FactoryMetafunctionClass>
        struct representation_factory_impl
        {
            typedef FactoryMetafunctionClass meta;

            template<class Seq>
            struct tag
            {
                typedef typename boost::remove_const<
                    typename boost::remove_reference<
                        typename bf::result_of::front<Seq>::type
                        >::type
                    >::type type;
            };

            template<class Seq>
            struct factory : mpl::apply<meta, typename tag<Seq>::type> {};

            template<class Seq>
            auto operator ()(const Seq &seq) const ->
                decltype(bf::invoke(typename factory<Seq>::type(), bf::pop_front(seq)))
            {
                return bf::invoke(typename factory<Seq>::type(), bf::pop_front(seq));
            }
        };
    }

    /**
     *  Factory used to create representation of tag, multi params constructor supported.
     *  
     *  Example:
     *  
     *  @code
     *  struct foo : tagged<foo>
     *  {
     *      foo(int) {}
     *  };
     *  struct bar : tagged<bar>
     *  {
     *      bar() {}
     *  };
     *  
     *  auto value = representation_factory<>()(foo::tag, 42);
     *  auto ptr = representation_factory<>()(bar::tag);
     *  @endcode
     */
    template<class FactoryMetafunctionClass = tag_detail::default_factory_metafunction_class>
    struct identity_factory :
        bf::unfused<tag_detail::representation_factory_impl<FactoryMetafunctionClass>, false>
    {};
}

#endif // __REPRESENTATION_FACTORY_HPP_20111201221514__
