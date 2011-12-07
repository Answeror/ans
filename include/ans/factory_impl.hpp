#if !defined(__FACTORY_IMPL_HPP_20111206163226__)
#define __FACTORY_IMPL_HPP_20111206163226__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-06
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <memory>

//#include <boost/shared_ptr.hpp>
//#include <boost/make_shared.hpp>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/singleton.hpp>
//#include <boost/function_types/result_type.hpp>
//#include <boost/function_types/parameter_types.hpp>
//#include <boost/function_types/function_type.hpp>
//#include <boost/mpl/push_front.hpp>
#include <boost/functional/forward_adapter.hpp>
#include <boost/functional/factory.hpp>
#include <boost/format.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>

#include <ans/b4main.hpp>
#include <ans/factory.hpp>

namespace ans
{
    template<class Signature, class Identifier>
    template<class Product>
    struct factory<Signature, Identifier>::product_traits
    {
        /// get the identifier of the product type
        static identifier_type identifier() { return Product::identifier(); }
    };

    template<class Signature, class Identifier>
    inline factory<Signature, Identifier>& factory<Signature, Identifier>::instance()
    {
         return boost::serialization::singleton<factory>::get_mutable_instance(); 
    }

    template<class Signature, class Identifier>
    inline const typename factory<Signature, Identifier>::maker_type&
        factory<Signature, Identifier>::make(const identifier_type &id)
    {
        return instance()[id];
    }

    template<class Signature, class Identifier>
    inline void factory<Signature, Identifier>::register_product(
        const identifier_type &id, const maker_type &maker)
    {
        return instance()._register_product(id, maker);
    }

    template<class Signature, class Identifier>
    template<class Product>
    void factory<Signature, Identifier>::register_product()
    {
        struct auto_register_product
        {
            typedef auto_register_product this_type;
            typedef Product product_type;
            struct failed;
            typedef typename
                boost::mpl::eval_if<
                    boost::is_convertible<std::unique_ptr<product_type>, result_type>,
                    boost::mpl::identity<std::unique_ptr<product_type> >,
                    boost::mpl::eval_if<
                        boost::is_convertible<boost::shared_ptr<product_type>, result_type>,
                        boost::mpl::identity<boost::shared_ptr<product_type> >,
                        boost::mpl::eval_if<
                            boost::is_convertible<product_type*, result_type>,
                            boost::mpl::identity<product_type*>,
                            failed
                            >
                        >
                    >::type product_ptr;
            typedef boost::forward_adapter<boost::factory<product_ptr> > maker;

            /// a simple wrapper of factory::add
            static void execute()
            {
                factory::instance().register_product(
                    product_traits<product_type>::identifier(),
                    maker()
                    );
            }
        };
        b4main<&auto_register_product::execute>();
    }

    template<class Signature, class Identifier>
    inline factory<Signature, Identifier>::factory() {}

    template<class Signature, class Identifier>
    inline void factory<Signature, Identifier>::_register_product(
        const identifier_type &id, const maker_type &maker)
    {
        auto i = m_makers.find(id);
        //if (i == m_makers.end()) {
        //    m_makers[id] = maker;
        //} else {
        //    //throw std::runtime_error((boost::format("Product id '%1%' already registered.") % id).str());
        //    BOOST_ASSERT_MSG(false, (boost::format(
        //        "Product id '%1%' already registered.") % id).str().c_str());
        //}
        BOOST_ASSERT_MSG(i == m_makers.end(), (boost::format(
            "Product id '%1%' already registered.") % id).str().c_str());
        m_makers[id] = maker;
    }

    template<class Signature, class Identifier>
    inline const typename factory<Signature, Identifier>::maker_type&
        factory<Signature, Identifier>::operator [](
            const identifier_type &id) const
    {
        auto i = m_makers.find(id);
        //if (i == m_makers.end()) {
        //    //throw std::runtime_error((boost::format("Product id '%1%' haven't been registered.") % id).str());
        //    BOOST_ASSERT_MSG(false, (boost::format(
        //        "Product id '%1%' haven't been registered.") % id).str().c_str());
        //} else {
        //    return i->second;
        //}
        BOOST_ASSERT_MSG(i != m_makers.end(), (boost::format(
            "Product id '%1%' haven't been registered.") % id).str().c_str());
        return i->second;
    }
}

#endif // __FACTORY_IMPL_HPP_20111206163226__
