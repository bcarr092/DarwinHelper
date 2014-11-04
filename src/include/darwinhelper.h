#ifndef __DARWIN_HELPER_H__
#define __DARWIN_HELPER_H__

#include <CoreFoundation/CoreFoundation.h>

#include <cpcommon.h>

void
darwin_print_code (
                   CPC_LOG_LEVEL log_level,
                   OSStatus      code
                   );

CHAR*
darwin_convert_cfstring_to_char_string (
                                        CFStringRef string_to_convert
                                        );

#endif /* __DARWIN_HELPER_H__ */
