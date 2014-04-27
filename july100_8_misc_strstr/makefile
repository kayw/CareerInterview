CC = g++ #clang++
WARNING := -Wall -Wextra
CFLAGS := -std=c++11 -MMD -MP $(WARNING) #-Wstrict-prototypes

TARGET = template
LDFLAGS := -shared -Wl,-soname=$(TARGET)
DBGFLAG := -g
RELFLAG :=

SRC_SUFFIX = cc
SRC := $(wildcard *.$(SRC_SUFFIX))
HEADER := $(shell find . -type f -name "*.h")

DBG_OBJs := $(patsubst %.$(SRC_SUFFIX), obj/debug/%.o,$(SRC))
REL_OBJs := $(patsubst %.$(SRC_SUFFIX), obj/release/%.o,$(SRC))

Include = -I ../
IglooInclude = -I ../../../igloo
LIBS :=  #-stdlib=libstdc++ libc++
OUT := bin/debug bin/release obj/debug obj/release
PROGRAM_DBG = bin/debug/$(TARGET)d
PROGRAM_REL = bin/release/$(TARGET)

.PHONY: all debug release clean dirs

all: dirs clean debug release

dirs:
	@mkdir -p $(OUT)

debug: dirs $(PROGRAM_DBG)

release: dirs $(PROGRAM_REL)


$(PROGRAM_DBG): $(DBG_OBJs)
	$(CC) $(DBG_OBJs) $(LIBS) -o $(PROGRAM_DBG)
	@echo "---- debug build ----"

$(PROGRAM_REL):$(REL_OBJs)
	$(CC) $(REL_OBJs) $(LIBS) -o $(PROGRAM_REL)
	strip $(PROGRAM_REL)
	@echo "---- release build ----"



obj/debug/%.o: %.cc
#$(DBG_OBJs):  $(SRC)
	$(CC) $(CMDFLAG) $(CFLAGS)  $(DBGFLAG) $(Include) $(IglooInclude) -MF $(patsubst obj/debug/%.o,obj/%.d,$@) -c $< -o $@

obj/release/%.o: %.cc
	$(CC) $(CFLAGS)  $(RELFLAG) $(Include) $(IglooInclude) -MF $(patsubst obj/release/%.o,obj/%.d,$@) -c $< -o $@


clean:
	rm -f $(DBG_OBJs) $(REL_OBJs) $(UT_OBJs) $(DEPs) *~

#http://unix.stackexchange.com/questions/37313/how-do-i-grep-for-multiple-patterns
#http://wiki.osdev.org/Makefile
#http://stackoverflow.com/questions/6153334/making-a-better-makefile
#http://damienradtke.org/a-generic-cc-linux-project-makefile/
#https://github.com/loarabia/Clang-tutorial/blob/master/makefile

#makefile usage
#http://stackoverflow.com/questions/7402205/remove-item-from-a-makefile-variable-gnu-make   ($(a:b=))

#least important
#http://stackoverflow.com/questions/16770751/clang-3-2-linker-not-finding-c-stdlib
#http://stackoverflow.com/questions/172587/what-is-the-difference-between-g-and-gcc
