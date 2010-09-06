Q=@
E=$(Q)echo

CC=clang
LUA=lua
OUT=dynasm_test
CCOPTS=-Wall -Werror -std=c99
CCOPTS+=-g -O0 -DDEBUG
#CCOPTS+=-O2 -DNDEBUG

all:
	$(E) dynasm backend.dasc
	$(Q)$(LUA) ./dynasm/dynasm.lua -c ./backend.dasc > backend.h
	$(E) $(CC) main.c
	$(Q)$(CC) $(CCOPTS) -o $(OUT) main.c
clean:
	$(Q)rm -rf $(OUT) *.o *~ backend.h *.dSYM debug.out
