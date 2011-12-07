#if !defined(__DATA_HOLDER_IMPL_HPP_20111206180923__)
#define __DATA_HOLDER_IMPL_HPP_20111206180923__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-06
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <boost/assert.hpp>

#include <ans/data_holder.hpp>

namespace ans
{
    template<class Concrete, class Erased>
    data_holder<Concrete, Erased>::data_holder() : m_data() {}

    template<class Concrete, class Erased>
    data_holder<Concrete, Erased>::data_holder(
        const concrete_type &data) : m_data(data) {}

    template<class Concrete, class Erased>
    data_holder<Concrete, Erased>::data_holder(
        concrete_type &&data) : m_data(std::move(data)) {}

    template<class Concrete, class Erased>
    data_holder<Concrete, Erased>::data_holder(
        const erased_type &data) : m_data(checked_cast(data)) {}

    template<class Concrete, class Erased>
    inline const typename data_holder<Concrete, Erased>::concrete_type&
        data_holder<Concrete, Erased>::concrete() const
    {
        return concrete(donothing);
    }

    template<class Concrete, class Erased>
    inline typename data_holder<Concrete, Erased>::concrete_type&
        data_holder<Concrete, Erased>::concrete()
    {
        return concrete(donothing);
    }

    template<class Concrete, class Erased>
    template<class Before>
    inline const typename data_holder<Concrete, Erased>::concrete_type&
        data_holder<Concrete, Erased>::concrete(const Before &before) const
    {
        before(m_data);
        return m_data;
    }

    template<class Concrete, class Erased>
    template<class Before>
    inline typename data_holder<Concrete, Erased>::concrete_type&
        data_holder<Concrete, Erased>::concrete(const Before &before)
    {
        return const_cast<concrete_type&>(
            static_cast<const this_type*>(this)->concrete(before)
            );
    }

    template<class Concrete, class Erased>
    inline auto data_holder<Concrete, Erased>::erased() const ->
        decltype(policy::erase(boost::declval<const concrete_type&>()))
    {
        return erased(donothing);
    }

    template<class Concrete, class Erased>
    template<class Before>
    inline auto data_holder<Concrete, Erased>::erased(const Before &before) const ->
        decltype(policy::erase(boost::declval<const concrete_type&>()))
    {
        return policy::erase(concrete(before));
    }

    template<class Concrete, class Erased>
    inline auto data_holder<Concrete, Erased>::erased() ->
        decltype(policy::erase(boost::declval<concrete_type&>()))
    {
        return erased(donothing);
    }

    template<class Concrete, class Erased>
    template<class Before>
    inline auto data_holder<Concrete, Erased>::erased(const Before &before) ->
        decltype(policy::erase(boost::declval<concrete_type&>()))
    {
        return policy::erase(concrete(before));
    }

    template<class Concrete, class Erased>
    inline void data_holder<Concrete, Erased>::set(const concrete_type &data)
    {
        set(data, donothing, donothing);
    }

    template<class Concrete, class Erased>
    template<class Before, class After>
    inline void data_holder<Concrete, Erased>::set(
        const concrete_type &data,
        const Before &before,
        const After &after
        )
    {
        if (before(m_data, data)) {
            m_data = data;
        }
        after(m_data);
    }

    template<class Concrete, class Erased>
    void data_holder<Concrete, Erased>::set(erased_type &&data)
    {
        set(std::forward<erased_type>(data), donothing, donothing);
    }

    template<class Concrete, class Erased>
    template<class Before, class After>
    void data_holder<Concrete, Erased>::set(
        concrete_type &&data,
        const Before &before,
        const After &after
        )
    {
        // use std::forward to keep rvalue
        if (before(m_data, std::forward<concrete_type>(data))) {
            m_data = std::move(data);
        }
        after(m_data);
    }

    template<class Concrete, class Erased>
    void data_holder<Concrete, Erased>::set(const erased_type &data)
    {
        set(data, donothing, donothing);
    }

    template<class Concrete, class Erased>
    template<class Before, class After>
    void data_holder<Concrete, Erased>::set(
        const erased_type &data,
        const Before &before,
        const After &after
        )
    {
        set(checked_cast(data), before, after);
    }

    template<class Concrete, class Erased>
    auto data_holder<Concrete, Erased>::checked_cast(const erased_type &data) ->
        decltype(*policy::cast<concrete_type>(&data))
    {
        auto p = policy::cast<concrete_type>(&data);
        // bug here, not a exception, so use assert
        BOOST_ASSERT_MSG(p, "Wrong data type.");
        return *p;
    }

    template<class ConcreteType, class ErasedType>
    const typename data_holder_detail::donothing_t
        data_holder<ConcreteType, ErasedType>::donothing;
}

#endif // __DATA_HOLDER_IMPL_HPP_20111206180923__
