Q=@
E=$(Q)echo

CC=clang
LUA=lua
OUT=dynasm_test
CCOPTS=-Wall -Werror -std=c99
CCOPTS+=-g -O0 -DDEBUG
#CCOPTS+=-O2 -DNDEBUG

OBJS = main.o bc.o vm.o recorder.o util.o compile.o

all: dynasm $(OBJS)
	$(E) "  " $(CC) $(OBJS) "->" $(OUT)
	$(Q)$(CC) $(CCOPTS) -o $(OUT) $(OBJS)

dynasm: backend.dasc
	$(E) "  DynASM" backend.dasc
	$(Q)$(LUA) ./dynasm/dynasm.lua -c ./backend.dasc > backend.h

%.o: %.c
	$(E) "  " $(CC) $< 
	$(Q)$(CC) $(CCOPTS) -c $< -o $@

clean:
	$(Q)rm -rf $(OUT) *.o *~ backend.h *.dSYM debug.out
