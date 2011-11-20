#pragma once

/*
--------------------------------------------------------------------------------
@author: Answeror
@description:

用类作为函数, 以限制类型定义的作用域, 以及保存副产品.
用法:

struct foo : fn<int>
{
    foo(int param)
    {
        ...
    }
};

int a = foo(param);
int b = foo(param).result;
--------------------------------------------------------------------------------
*/

namespace ans
{
    template<class Result>
    struct fn
    {
        typedef Result result_type;

        result_type result;

        fn() {}

        fn(const result_type &res) : result(res) {}

        operator const result_type &() const
        {
            return result;
        }
    };
}