#pragma once
#ifndef MY_ASSERT_H
#define MY_ASSERT_H

#pragma warning(disable:4127)//conditional with constent (aka the while(0))

#include "LogManager.h"

#define ASSERT(x,...) do { if (!(x)) { LOG( MAX_SEVERITY, #x##__VA_ARGS__, 0); END_LOG; exit(-1); } } while(0);

#endif