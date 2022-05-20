# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = main.c timer.c keyboard.c mouse.c utils.c video_gr.c vbe.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic # S-D __LCOM_OPTIMIZED

# list of library dependen		cies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
