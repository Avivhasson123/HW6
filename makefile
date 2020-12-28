CC     = gcc
CCLINK = $(CC)
CFLAGS = -Wall -g -std=c99
OBJS   = functions.o ransom.o
EXEC   = prog.exe
RM     =  rm -rf *.o *.exe

all: $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

ransom.o: ransom.c functions.h
	$(CC) $(CFLAGS) -c ransom.c

clean:
	$(RM)