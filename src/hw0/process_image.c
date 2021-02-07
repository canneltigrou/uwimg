#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

// return the pixel value at column x, row y, and channel c.
float get_pixel(image im, int x, int y, int c)
{
    // en c++ : 
    //c = std::clamp(c, 0, im.c);
    //y = std::clamp(y, 0, im.h);
    //x = std::clamp(x, 0, im.w);
    
    if(c < 0)
        c = 0;
    else
    {
        if (c > im.c)
            c = im.c;
    }

    if(y < 0)
        y = 0;
    else
    {
        if (y > im.h)
            y = im.h;
    }
    
    if(x < 0)
        x = 0;
    else
    {
        if (x > im.w)
            x = im.w;
    }
    

    return (im.data)[c*(im.h * im.w) + y * im.w + x];
}

// set the pixel value at column x, row y, and channel, to the value v
void set_pixel(image im, int x, int y, int c, float v)
{
    (im.data)[c*(im.h * im.w) + y * im.w + x] = v;
}

// return a copy of the image
image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    copy.data = memcpy(copy.data, im.data, im.w * im.h * im.c);
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    for(int x = 0; x < gray.w; x++)
        for(int y = 0; y < gray.h; y++)
            set_pixel(gray, x, y, 0, 0.299 * get_pixel(im, x, y, 0) + 0.587 * get_pixel(im, x, y, 1) + 0.114 * get_pixel(im, x, y, 2));
    return gray;
}

// add v to every pixel in channel c in the image
void shift_image(image im, int c, float v)
{
    for(int x = 0; x < im.w; x++)
        for(int y = 0; y < im.h; y++)
            set_pixel(im, x, y, c, get_pixel(im, x, y, c) + v);
}

// maintain the value of data between 0 and 1. 
void clamp_image(image im)
{
    for(int x = 0; x < im.w; x++)
        for(int y = 0; y < im.h; y++)
            for(int c = 0; c < im.c; c++)
            {
                if(get_pixel(im, x, y, c) > 1)
                    set_pixel(im, x, y, c, 1);
                else if (get_pixel(im, x, y, c) < 0)
                    set_pixel(im, x, y, c, 0);
            }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
