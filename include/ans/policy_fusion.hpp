#pragma once

/*
--------------------------------------------------------------------------------
@author: Answeror
@description: policy_chain的方便接口.
--------------------------------------------------------------------------------
*/

#include "policy_chain.hpp"

namespace ans
{
    template<class T1, class T2 = void, class T3 = void, class T4 = void>
    struct policy_fusion;

    template<class T1>
    struct policy_fusion<T1> : policy_chain<T1> {};

    template<class T1, class T2>
    struct policy_fusion<T1, T2> : policy_chain<T1, policy_chain<T2> > {};

    template<class T1, class T2, class T3>
    struct policy_fusion<T1, T2, T3> : policy_chain<T1, policy_chain<T2, policy_chain<T3> > > {};

    template<class T1, class T2, class T3, class T4>
    struct policy_fusion : policy_chain<T1, policy_chain<T2, policy_chain<T3, policy_chain<T4> > > > {};
}