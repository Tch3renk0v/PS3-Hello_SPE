CC         = gcc
CINCS      =
CLIBS      = -lspe2
CFLAGS     = -Wall

SPU_CC     = spu-gcc
SPU_CINCS  =
SPU_CLIBS  =
SPU_CFLAGS = -Wall

SPU_EMBED = embedspu

EXEC = Hello.exec

all: $(EXEC) hello_spe.elf

$(EXEC): hello_ppe.c embedded_spu.so
	$(CC) $(CFLAGS) $(CINCS) $(CLIBS) $^ -o $@

embedded_spu.so: hello_spe.elf
	$(SPU_EMBED) hello_spu_handle hello_spe.elf embedded_spu.so

hello_spe.elf: hello_spe.c
	$(SPU_CC) $(SPU_CFLAGS) $(SPU_CINCS) $(SPU_CLIBS) $^ -o $@

clean:
	rm -f *.elf *.so $(EXEC)
