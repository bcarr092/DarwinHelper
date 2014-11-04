#include "darwinhelper.h"

/** This code is taken from "Learning Core Audio - pg. 82"
 */
void
darwin_print_code (
                   CPC_LOG_LEVEL log_level,
                   OSStatus      code
                   )
{
  if( noErr != code )
  {
    char error_string[ 7 ] = { 0 };
    
    * ( UINT32 * ) ( error_string + 1 ) = CFSwapInt32HostToBig( code );
    if( isprint( error_string[ 1 ] ) && isprint( error_string[ 2 ] )
       && isprint( error_string[ 3 ] ) && isprint( error_string[ 4 ] ) )
    {
      error_string[ 0 ] = error_string[ 5 ] = '\'';
      error_string[ 6 ] = '\0';
      
      cpc_log( log_level, "Code: %s", error_string );
    }
  }
}

CHAR*
darwin_convert_cfstring_to_char_string(
                                       CFStringRef string_to_convert
                                       )
{
  if( NULL == string_to_convert )
  {
    return( NULL );
  }
  else
  {
    cpc_log (
             CPC_LOG_LEVEL_TRACE,
             "Converting string: %s",
             CFStringGetCStringPtr( string_to_convert, kCFStringEncodingASCII )
             );
    
    CFIndex string_length = CFStringGetLength( string_to_convert );
    CFIndex string_max_length =
      CFStringGetMaximumSizeForEncoding( string_length, kCFStringEncodingASCII );
    
    CHAR* c_string = ( CHAR* ) malloc( string_max_length + 1 );
    
    memset( c_string, 0, string_max_length + 1 );
    
    if( CFStringGetCString  (
                             string_to_convert,
                             c_string,
                             string_max_length + 1,
                             kCFStringEncodingASCII
                            )
       )
    {
      cpc_log( CPC_LOG_LEVEL_TRACE, "Converted string: %s", c_string );
      
      return( c_string );
    }
    else
    {
      cpc_log (
               CPC_LOG_LEVEL_ERROR,
               "Could not convert string %s",
               CFStringGetCStringPtr  (
                                       string_to_convert,
                                       kCFStringEncodingASCII
                                       )
               );
      
      return( NULL );
    }
  }
}
