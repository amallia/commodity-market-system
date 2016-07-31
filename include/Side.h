#pragma once

#include <boost/preprocessor/seq/enum.hpp>
#include <enum.h>


#define SIDES_TYPES (BUY)(SELL)
BETTER_ENUM(SIDES_TYPES_ENUM, int, BOOST_PP_SEQ_ENUM(SIDES_TYPES))