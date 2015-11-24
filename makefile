SRC_SUFFIX = cc
#SRC := $(wildcard *.$(SRC_SUFFIX))
SRC := $(shell find . -type f -name '*.'$(SRC_SUFFIX) -o -name '*.hpp' -o -name '*.h')

ALL := $(SRC)

todo:
	-@for file in $(ALL:makefile=); do ag -H -i "TODO|FIXME" $$file; done; true
