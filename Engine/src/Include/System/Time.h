#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_
//  System time access functions, you application has to be time aware as undelaying hardware
//  may vary or evan the clock spped can vary during execution.

#include "Types.h"

namespace sys 
{
    //  Time from application start.
    double      GetCurrentSec   ();
    uint32      GetCurrentMili  ();
} // namespace sys 

#endif // _SYS_TIME_H_
