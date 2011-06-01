#pragma once

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: 链式继承策略.
--------------------------------------------------------------------------------
*/

#include <boost/type_traits/is_base_of.hpp>

namespace ans
{
    namespace detail
    //{
    //    struct crtp_policy {};

    //    /// 继承这个类, 使得policy继承自后续的policy.
    //    struct derive_from_tail {};

    //    template<
    //        class Policy, 
    //        class Derived,
    //        class Crtp = typename boost::is_base_of<crtp_policy, Policy>::type
    //    >
    //    struct eval_policy;

    //    template<class Policy, class Derived>
    //    struct eval_policy<Policy, Derived, boost::false_type>
    //    {
    //        typedef Policy type;
    //    };

    //    template<class Policy, class Derived>
    //    struct eval_policy<Policy, Derived, boost::true_type>
    //    {
    //        typedef typename Policy::template type<Derived> type;
    //    };

    //    struct policy_chain_tail {};

    //    template<class Policy, class Base, class Derived>
    //    struct policy_chain_node;

    //    template<class Policy, class Base, class Derived>
    //    struct policy_chain_node : eval_policy<Policy, Derived>::type, Base {};

    //    template<class Policy, class Derived>
    //    struct policy_chain_node<Policy, policy_chain_tail, Derived> : eval_policy<Policy, Derived>::type {};

    //    template<class Policy, class Base = policy_chain_tail>
    //    struct policy_chain : policy_chain_node<Policy, Base, policy_chain<Policy, Base> > {};
    //}
    {
        /// 继承这个类, 使得policy继承自后续的policy.
        struct derive_from_tail {};

        struct policy_chain_tail {};

        template<class Policy, class Base, class DeriveFromTail = typename boost::is_base_of<derive_from_tail, Policy>::type>
        struct policy_chain_node;

        template<class Policy, class Base>
        struct policy_chain_node<Policy, Base, boost::false_type> : Policy, Base {};

        template<class Policy, class Base>
        struct policy_chain_node<Policy, Base, boost::true_type> : Policy::template type<Base> {};

        template<class Policy, class Base = policy_chain_tail>
        struct policy_chain : policy_chain_node<Policy, Base> {};
    }

    //using detail::crtp_policy;
    using detail::derive_from_tail;
    using detail::policy_chain;
}