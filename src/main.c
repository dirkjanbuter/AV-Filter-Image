#include <math.h>
#include <stdarg.h>

#include "imgbuffer.h"

static int _w = 0;
static int _h = 0;
static int _framecount = 0;
static int _fps = 0;

static int _s = 0;
static int _sizebytes = 0;

static IMGBUFFER _backbuffer;
static IMGBUFFER _img;
static int first = 1;

BOOL video(char *text)
{
    int x, y;
    unsigned char cr; unsigned char cg; unsigned char cb; unsigned char alpha;

    if(first)
    {
        if(imgbuffer_load(&_img, text) == CFAILED)
        {
            return FALSE;
        }
    
        first = 0;
    }

    imgbuffer_clear(&_backbuffer);

    for(y=0; y < _h; y++) for(x=0; x < _w; x++)  
    {
        imgbuffer_getpixel(&_img, x, y, &cr, &cg, &cb, &alpha);
        imgbuffer_setpixelblend(&_backbuffer, x, y, cr, cg, cb, 0xff);
    }  
    return TRUE;
}

int filtercreate(int fps)
{
      _fps = fps;
      imgbuffer_create(&_img);
      return TRUE;
}

void filterdestroy()
{
      imgbuffer_destroy(&_img);
}


int filtervideo(unsigned char *buffer, int w, int h, unsigned int color, char *text, int64_t framecount)
{
    _w = w;
    _h = h;
    _framecount = framecount;

    _s = _w * _h;
    _sizebytes = _s * 4;

    _backbuffer.data = buffer;
    _backbuffer.w = _w;
    _backbuffer.h = _h;
    _backbuffer.s = _sizebytes;

    return video(text);
}

int filteraudio(float *frame, int64_t framecount, float elapsed)
{

	return TRUE;
}

