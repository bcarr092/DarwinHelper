/*! \file   darwin_helper.h
    \brief  Darwin specific helper functions are defined in this library.
 */
#ifndef __DARWIN_HELPER_H__
#define __DARWIN_HELPER_H__

#include <CoreFoundation/CoreFoundation.h>

#include <cpcommon.h>

/*! \def    DARWIN_PRINT_CODE
    \brief  Wrapper to ensure the correct file and line are printed in the log
            message when displaying the Darwin-specific error code.
 */
#define DARWIN_PRINT_CODE( in_log_level, in_code ) \
 darwin_print_code( in_log_level, __FILE__, __LINE__, in_code )

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
    \param  in_file       The file name to display in the log
    \param  in_line_number  The line number to be displayed in the log
    \param  in_code       The code to convert to its four character string
                          representation.
 */
void
darwin_print_code (
                   CPC_LOG_LEVEL  in_log_level,
                   CHAR*          in_file,
                   INT32          in_line_number,
                   OSStatus       in_code
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
