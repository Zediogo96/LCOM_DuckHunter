# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/Devices

# source code files to be compiled
SRCS = main.c timer.c kbc.c mouse.c utils.c video_gr.c crosshair.c database.c Sprite.c hitboxes.c duck.c rtc.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D __LCOM_OPTIMIZED

# list of library dependen		cies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
