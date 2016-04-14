CC = gcc
#CC = clang
#CMDFLAG = -x c++
#CXX = clang
WARNING := -Wall -Wextra
CFLAGS := -MMD -MP $(WARNING) #-Wstrict-prototypes
#CFLAGS := -w -MMD -MP  #-Wstrict-prototypes

TARGET = floodingislands
#TARGET := lib$(LIBNAME)
LDFLAGS := -shared -Wl,-soname=$(TARGET)
#CXXFLAGS := -Wall -Wstrict-prototypes
DBGFLAG := -g
RELFLAG :=

SRC := $(wildcard *.cpp)
HEADER := $(shell find . -type f -name "*.h")

DBG_OBJs := $(patsubst %.cpp,obj/debug/%.o,$(SRC))
REL_OBJs := $(patsubst %.cpp,obj/release/%.o,$(SRC))

Include = -I ../ -I ../../../mnb/
IglooInclude = -I ../../igloo
LIBS := -lstdc++ -lm #-std=c++11 -stdlib=libstdc++ libc++
OUT := bin/debug bin/release obj/debug obj/release obj/debug/mnb
PROGRAM_DBG = bin/debug/$(TARGET)d
PROGRAM_REL = bin/release/$(TARGET)

.PHONY: all debug release clean dirs

all: dirs clean debug release

dirs:
	@mkdir -p $(OUT)

debug: dirs $(PROGRAM_DBG)

release: dirs $(PROGRAM_REL)

MNB_SRC := $(wildcard ../../../mnb/*.cpp)
MNB_OBJs := $(patsubst ../../../mnb/%.cpp, obj/debug/%.o, $(MNB_SRC))

$(PROGRAM_DBG): $(DBG_OBJs) $(MNB_OBJs)
	$(CC) $(DBG_OBJs) $(MNB_OBJs) $(LIBS) -o $(PROGRAM_DBG)
	@echo "---- debug build ----"

$(PROGRAM_REL):$(REL_OBJs)
	$(CC) $(REL_OBJs) $(LIBS) -o $(PROGRAM_REL)
	strip $(PROGRAM_REL)
	@echo "---- release build ----"


obj/debug/%.o: %.cpp
#$(DBG_OBJs):  $(SRC)
	$(CC) $(CMDFLAG) $(CFLAGS)  $(DBGFLAG) $(Include) -MF $(patsubst obj/debug/%.o,obj/%.d,$@) -c $< -o $@

obj/debug/%.o: ../../../mnb/%.cpp
	$(CC) $(CMDFLAG) $(CFLAGS)  $(DBGFLAG) $(Include) -MF $(patsubst obj/debug/%.o,obj/%.d,$@) -c $< -o $@


obj/release/%.o: %.cpp
	$(CC) $(CFLAGS)  $(RELFLAG) $(Include) -MF $(patsubst obj/release/%.o,obj/%.d,$@) -c $< -o $@


PROGRAM_UT = bin/debug/ut_$(TARGET)
UT_SRC := $(wildcard unittest/*_test.cpp)
UT_OBJs := $(patsubst unittest/%.cpp,obj/debug/%.o,$(UT_SRC))

DEPs := $(patsubst %.cpp,obj/%.d,$(SRC) $(UT_SRC))
-include $(DEPs)

obj/debug/%_test.o: unittest/%_test.cpp
	@echo $(UT_SRC)
	$(CC) $(CMDFLAG) $(CFLAGS) $(DBGFLAG) $(Include) $(IglooInclude) -MF $(patsubst obj/debug/%.o,obj/%d,$@) -c $< -o $@

$(PROGRAM_UT): $(UT_OBJs) $(DBG_OBJs)
	$(CC) $(UT_OBJs) $(DBG_OBJs:obj/debug/mdriverstub.o=) $(LIBS) -o $(PROGRAM_UT)
	@echo "----- unittest build ----"

ut: dirs $(PROGRAM_UT)

clean:
	rm -f $(DBG_OBJs) $(REL_OBJs) $(UT_OBJs) $(DEPs) *~

ALL := $(SRC) $(HEADER) $(UT_SRC)

todo:
	-@for file in $(ALL:makefile=); do ack -H -i "TODO|FIXME" $$file; done; true

#http://stackoverflow.com/questions/4102469/makefile-to-put-object-files-from-source-files-different-directories-into-a-sing
#http://wiki.osdev.org/Makefile
#http://stackoverflow.com/questions/6153334/making-a-better-makefile
#http://damienradtke.org/a-generic-cc-linux-project-makefile/
#https://github.com/loarabia/Clang-tutorial/blob/master/makefile

#makefile usage
#http://stackoverflow.com/questions/7402205/remove-item-from-a-makefile-variable-gnu-make   ($(a:b=))

#least important
#http://stackoverflow.com/questions/16770751/clang-3-2-linker-not-finding-c-stdlib
#http://stackoverflow.com/questions/172587/what-is-the-difference-between-g-and-gcc
