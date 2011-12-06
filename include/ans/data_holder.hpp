#if !defined(__DATA_HOLDER_HPP_20111119143224__)
#define __DATA_HOLDER_HPP_20111119143224__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-11-19
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <stdexcept>

#include <boost/utility/declval.hpp>
#include <boost/assert.hpp>
#include <boost/any.hpp>
#include <boost/dynamic_any.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>

namespace ans
{
    /**
     *  Default impl, use dynamic_cast.
     *  
     *  This class should be specialized by client.
     */
    template<class T>
    struct data_holder_type_erase_policy
    {
        typedef T erased_type;

        template<class U>
        static const U* cast(const erased_type *p)
        {
            return dynamic_cast<const U*>(p);
        }

        /// @param data connot be rvalue
        template<class U>
        static erased_type & erase(U &data) { return data; }
    };

    template<>
    struct data_holder_type_erase_policy<boost::any>
    {
        typedef boost::any erased_type;

        template<class T>
        static decltype(boost::any_cast<T>((const erased_type*)0)) cast(const erased_type *p)
        {
            return boost::any_cast<T>(p);
        }

        template<class U>
        static erased_type erase(const U &data) { return data; }
    };

    template<>
    struct data_holder_type_erase_policy<boost::dynamic_any>
    {
        typedef boost::dynamic_any erased_type;

        template<class T>
        static decltype(boost::dynamic_any_cast<T>((const erased_type*)0)) cast(const erased_type *p)
        {
            return boost::dynamic_any_cast<T>(p);
        }

        template<class U>
        static erased_type erase(const U &data) { return data; }
    };

    namespace data_holder_detail
    {
        /// this class is used to test whether need to disable specialization
        template<class Concrete, class Erased>
        struct legal : boost::mpl::not_<boost::mpl::or_<
            boost::is_same<Concrete, Erased>,
            boost::is_const<Concrete>,
            boost::is_reference<Concrete>
            > > {};
    }
        
    /**
     *  This class is used to hold a concrete type and provide both concrete
     *  and type-erased getter/setter.
     *  
     *  Setter methods provide additional param to specify a before/after action
     *  to keep track of the old and new value.
     *  The before method should return a bool value to indicate whether the
     *  value should be updated.
     *  
     *  Getter methods also provide additional param to specify a before action
     *  to check whether the value is valid.
     */
    template<
        class ConcreteType,
        class ErasedType = boost::dynamic_any
        >
    class data_holder
    {
        static_assert(data_holder_detail::legal<ConcreteType, ErasedType>::value, "Illegal concrete type.");

    private:
        typedef data_holder_type_erase_policy<ErasedType> policy;

    public:
        typedef data_holder this_type;
        typedef ConcreteType concrete_type;
        typedef typename policy::erased_type erased_type;

    public:
        data_holder() : m_data() {}

        explicit data_holder(const concrete_type &data) : m_data(data) {}

        explicit data_holder(concrete_type &&data) : m_data(std::move(data)) {}

        explicit data_holder(const erased_type &data) : m_data(checked_cast(data)) {}

    public:
        struct donothing_t
        {
            template<class T>
            bool operator ()(T) const { return true; }

            template<class T1, class T2>
            bool operator ()(T1, T2) const { return true; }
        };

        static const donothing_t donothing;

    public:
        const concrete_type & concrete() const
        {
            return concrete(donothing);
        }

        template<class Before>
        const concrete_type & concrete(const Before &before = donothing) const
        {
            before(m_data);
            return m_data;
        }

        concrete_type & concrete()
        {
            return concrete(donothing);
        }

        template<class Before>
        concrete_type & concrete(const Before &before = donothing)
        {
            return const_cast<concrete_type&>(
                static_cast<const this_type*>(this)->concrete(before)
                );
        }

        /// @return may be reference or value, depend on policy
        auto erased() const ->
            decltype(policy::erase(boost::declval<const concrete_type&>()))
        {
            return erased(donothing);
        }

        /// @return may be reference or value, depend on policy
        template<class Before>
        auto erased(const Before &before) const ->
            decltype(policy::erase(boost::declval<const concrete_type&>()))
        {
            return policy::erase(concrete(before));
        }

        /// @return may be reference or value, depend on policy
        auto erased() ->
            decltype(policy::erase(boost::declval<concrete_type&>()))
        {
            return erased(donothing);
        }

        /// @return may be reference or value, depend on policy
        template<class Before>
        auto erased(const Before &before) ->
            decltype(policy::erase(boost::declval<concrete_type&>()))
        {
            return policy::erase(concrete(before));
        }

        void set(const concrete_type &data)
        {
            set(data, donothing, donothing);
        }

        template<class Before>
        void set(
            const concrete_type &data,
            const Before &before
            )
        {
            set(data, before, donothing);
        }

        template<class Before, class After>
        void set(
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

        /**
         *  @param data must be of concrete_type
         */
        void set(erased_type &&data)
        {
            set(std::forward<erased_type>(data), donothing, donothing);
        }

        /**
         *  @param data must be of concrete_type
         */
        template<class Before>
        void set(
            erased_type &&data,
            const Before &before
            )
        {
            set(std::forward<erased_type>(data), before, donothing);
        }

        template<class Before, class After>
        void set(
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

        /**
         *  @param data must be of concrete_type
         */
        void set(const erased_type &data)
        {
            set(data, donothing, donothing);
        }

        /**
         *  @param data must be of concrete_type
         */
        template<class Before>
        void set(
            const erased_type &data,
            const Before &before
            )
        {
            set(data, before, donothing);
        }

        /**
         *  @param data must be of concrete_type
         */
        template<class Before, class After>
        void set(
            const erased_type &data,
            const Before &before,
            const After &after
            )
        {
            set(checked_cast(data), before, after);
        }

    private:
        static auto checked_cast(const erased_type &data) ->
            decltype(*policy::cast<concrete_type>(&data))
        {
            auto p = policy::cast<concrete_type>(&data);
            // bug here, not a exception, so use assert
            BOOST_ASSERT_MSG(p, "Wrong data type.");
            return *p;
        }

    private:
        concrete_type m_data;
    };

    template<class ConcreteType, class ErasedType>
    const typename data_holder<ConcreteType, ErasedType>::donothing_t
        data_holder<ConcreteType, ErasedType>::donothing;
}

#endif // __DATA_HOLDER_HPP_20111119143224__
