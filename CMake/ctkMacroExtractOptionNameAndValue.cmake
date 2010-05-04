
#
#
#

MACRO(ctkMacroExtractOptionNameAndValue my_opt var_opt_name var_opt_value)

 # Make sure option is correctly formated
  IF(NOT "${my_opt}" MATCHES "^[/A-Za-z0-9.]+:(ON|OFF)")
    MESSAGE(FATAL_ERROR "Option ${my_opt} is incorrect. Options should be specified using the following format OPT1:[ON|OFF]. For example OPT1:OFF or OPT2:ON")
  ENDIF()

  # Extract option name and option default value
  STRING(REPLACE ":" "\\;" my_opt_list ${my_opt})
  SET(my_opt_list ${my_opt_list})
  LIST(GET my_opt_list 0 ${var_opt_name})
  LIST(GET my_opt_list 1 ${var_opt_value})
ENDMACRO()

#
# Test - Use cmake -DMACRO_TESTING:BOOL=ON -P ctkMacroExtractOptionNameAndValue.cmake
#
IF(MACRO_TESTING)

  MESSAGE("Testing ctkMacroExtractOptionNameAndValue ...")
  #
  # Test1
  #
  SET(test1 "john:ON")
  ctkMacroExtractOptionNameAndValue(${test1} test1_name test1_value)
  
  IF(NOT test1_name STREQUAL "john")
    MESSAGE(FATAL_ERROR "test1_name:${test1_name} - Expected:john")
  ENDIF()
  
  IF(NOT test1_value STREQUAL "ON")
    MESSAGE(FATAL_ERROR "test1_value:${test1_value} - Expected:ON")
  ENDIF()

  #
  # Test2
  #
  SET(test2 "doe/john:OFF")
  ctkMacroExtractOptionNameAndValue(${test2} test2_name test2_value)
  
  IF(NOT test2_name STREQUAL "doe/john")
    MESSAGE(FATAL_ERROR "test1_name:${test2_name} - Expected:doe/john")
  ENDIF()
  
  IF(NOT test2_value STREQUAL "OFF")
    MESSAGE(FATAL_ERROR "test2_value:${test2_value} - Expected:OFF")
  ENDIF()
  
ENDIF()
