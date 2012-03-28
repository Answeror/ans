#ifdef _MSC_VER
	#pragma once
#endif
#ifndef __MAIN_HPP_20111227105306__
#define __MAIN_HPP_20111227105306__

/**
 *  @file
 *  @author answeror <answeror@gmail.com>
 *  @date 2011-12-27
 *  
 *  @section DESCRIPTION
 *  
 *  
 */

#include <ans/alpha/pimpl.hpp>

class someclass
{
public:
    someclass();
    ~someclass();

public:
    int foo() const;

private:
    struct impl;
    ans::alpha::pimpl::unique<impl> self;
};

#endif // __MAIN_HPP_20111227105306__
