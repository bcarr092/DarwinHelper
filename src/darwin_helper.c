#include "darwin_helper.h"

CHAR*
darwin_convert_code_to_cstring  (
                                 OSStatus in_code
                                 )
{
  CHAR* code = NULL;
  
  if( noErr != in_code )
  {
    code = ( CHAR* ) malloc( DARWIN_CODE_STRING_LENGTH * sizeof( CHAR ) );
    
    memset( code, 0, DARWIN_CODE_STRING_LENGTH * sizeof( CHAR ) );
    
    * ( UINT32 * ) ( code + 1 ) = CFSwapInt32HostToBig( in_code );
    
    if( isprint( code[ 1 ] ) && isprint( code[ 2 ] )
       && isprint( code[ 3 ] ) && isprint( code[ 4 ] ) )
    {
      code[ 0 ] = code[ 5 ] = '\'';
      code[ 6 ] = '\0';
    }
  }
  
  return( code );
}

void
darwin_print_code (
                   CPC_LOG_LEVEL  in_log_level,
                   CHAR*          in_file,
                   INT32          in_line_number,
                   OSStatus       in_code
                   )
{
  CHAR* cstring_code = darwin_convert_code_to_cstring( in_code );
  
  if( NULL != cstring_code )
  {
    cpc_log (
             in_log_level,
             in_file,
             in_line_number,
             "Code: %s",
             cstring_code
             );
    
    free( cstring_code );
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
