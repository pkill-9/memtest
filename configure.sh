#!  /bin/bash
#
# Create empty depend files so that make can build the project. Because
# the depend file is included in the makefile, if depend does not exist,
# running make will result in an error. However, the depend file is
# automatically generated, and hence should not be placed under version
# control. This script is the solution.
#
# This script only needs to be run once, to create the initial depend
# files.

touch memtest/depend
touch tools/depend
make depend

# vim: ft=sh ts=4 sw=4 et
