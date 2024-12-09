CC = gcc
SRCS = main.c imgbuffer.c matrix2d.c matrix3d.c vector2d.c vector3d.c pngformat.c 
FILES = $(addprefix src/, $(SRCS))
OBJS = $(FILES:.c=.o)
LIBS = -lm -lpng
CFLAGS = -I/home/dirkjan/ffmpeg_build/include/

%.o: %.c $(FILES)
	$(CC) -c -o $@ $< $(CFLAGS) -fPIC 

build: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -fPIC --shared -o ./../build/filter_image.so

dist: build
		rm $(OBJS)

clean:
		rm $(OBJS)
