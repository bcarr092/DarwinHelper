#include "darwin_helper.h"

void
darwin_print_code (
                   CPC_LOG_LEVEL  in_log_level,
                   CHAR*          in_file,
                   INT32          in_line_number,
                   OSStatus       in_code
                   )
{
  if( noErr != in_code )
  {
    char error_string[ 7 ] = { 0 };
    
    * ( UINT32 * ) ( error_string + 1 ) = CFSwapInt32HostToBig( in_code );
    
    if( isprint( error_string[ 1 ] ) && isprint( error_string[ 2 ] )
       && isprint( error_string[ 3 ] ) && isprint( error_string[ 4 ] ) )
    {
      error_string[ 0 ] = error_string[ 5 ] = '\'';
      error_string[ 6 ] = '\0';
      
      cpc_log (
               in_log_level,
               in_file,
               in_line_number,
               "Code: %s",
               error_string
               );
    }
  }
}

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
