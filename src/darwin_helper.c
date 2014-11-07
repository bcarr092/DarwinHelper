#include "darwin_helper.h"

CHAR*
darwin_convert_cfstring_to_char_string(
                                       CFStringRef in_string_to_convert
                                       )
{
  if( NULL == in_string_to_convert )
  {
    return( NULL );
  }
  else
  {
    CPC_LOG (
             CPC_LOG_LEVEL_TRACE,
             "Converting string: %s",
             CFStringGetCStringPtr( in_string_to_convert, kCFStringEncodingASCII )
             );
    
    CFIndex string_length = CFStringGetLength( in_string_to_convert );
    CFIndex string_max_length =
      CFStringGetMaximumSizeForEncoding( string_length, kCFStringEncodingASCII );
    
    CHAR* c_string = ( CHAR* ) malloc( string_max_length + 1 );
    
    memset( c_string, 0, string_max_length + 1 );
    
    if( CFStringGetCString  (
                             in_string_to_convert,
                             c_string,
                             string_max_length + 1,
                             kCFStringEncodingASCII
                            )
       )
    {
      CPC_LOG( CPC_LOG_LEVEL_TRACE, "Converted string: %s", c_string );
      
      return( c_string );
    }
    else
    {
      CPC_ERROR (
                 "Could not convert string %s",
                 CFStringGetCStringPtr  (
                                         in_string_to_convert,
                                         kCFStringEncodingASCII
                                         )
                 );
      
      return( NULL );
    }
  }
}
