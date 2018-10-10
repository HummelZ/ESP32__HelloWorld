#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

CPPFLAGS += -D_GLIBCXX_USE_C99

#COMPONENT_ADD_LDFLAGS=-lstdc++ -l$(COMPONENT_NAME) 


COMPONENT_ADD_INCLUDEDIRS += ../components/bme280/
COMPONENT_ADD_INCLUDEDIRS += ../components/i2c/
COMPONENT_ADD_INCLUDEDIRS += ../components/sensor/
COMPONENT_ADD_INCLUDEDIRS += ../components/wifi/