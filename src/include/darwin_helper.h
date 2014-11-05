/*! \file   darwin_helper.h
    \brief  Darwin specific helper functions are defined in this library.
 */
#ifndef __DARWIN_HELPER_H__
#define __DARWIN_HELPER_H__

#include <CoreFoundation/CoreFoundation.h>

#include <cpcommon.h>

/*! \fn     void darwin_print_code (
              CPC_LOG_LEVEL in_log_level,
              OSStatus      in_code
            )
    \brief  Converts in_code to its string representation if possible and
            outputs it to the screen using the logger defined in cpcommon.
            Apple creates return codes (UINT32) that have four character
            representations in a lot of cases. This function will output
            the four character representation whenever possible, i.e. each
            character is printable.
 
    \note   This code is taken from "Learning Core Audio" by Adamson and Avila
            pg. 82
 
    \param  in_log_level  The log level to log the converted string
    \param  in_code       The code to convert to its four character string
                          representation.
 */
void
darwin_print_code (
                   CPC_LOG_LEVEL in_log_level,
                   OSStatus      in_code
                   );

/*! \fn     CHAR* darwin_convert_cfstring_to_char_string (
              CFStringRef in_string_to_convert
            )
    \brief  Helper function that creates a new c-style character string
            by converting in_string_to_convert to an ASCII formatted string.
            Note that the caller must free the return CHAR*.
 
    \param  in_string_to_convert  The CoreFoundation string to convert to a
                                  c-style string. The caller must free the
                                  returned string.
    \return A newly created c string that must be freed by the caller.
 */
CHAR*
darwin_convert_cfstring_to_char_string (
                                        CFStringRef in_string_to_convert
                                        );

#endif /* __DARWIN_HELPER_H__ */
