/*
  showfont:  An example of using the SDL_ttf library with 2D graphics.
  Copyright (C) 2001-2012 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* SaveSurf: an example on how to save a SDLSurface in PNG
   Copyright (C) 2006 Angelo "Encelo" Theodorou
 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
   NOTE: 
 
   This program is part of "Mars, Land of No Mercy" SDL examples, 
   you can find other examples on http://marsnomercy.org
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef HAVE_ICONV
#include <iconv.h>
#endif

#include <SDL.h>
#include <SDL_ttf.h>

#define DEFAULT_PTSIZE	23
#define DEFAULT_TEXT	"The quick brown fox jumped over the lazy dog"
#define NUM_COLORS      256

static char *Usage =
"Usage: %s [-solid] [-utf8|-unicode] [-b] [-i] [-u] [-s] [-outline size] [-hintlight|-hintmono|-hintnone] [-nokerning] [-fgcol r,g,b] [-bgcol r,g,b] <font>.ttf [ptsize] [text]\n";

static void cleanup(int exitcode) {
	TTF_Quit();
	SDL_Quit();
	exit(exitcode);
}


enum {
	SDL_EFFECTS_PIXEL_ALPHA_SHADE_H,
	SDL_EFFECTS_PIXEL_ALPHA_SHADE_H2,
	SDL_EFFECTS_PIXEL_ALPHA_SHADE_H3,
	SDL_EFFECTS_PIXEL_ALPHA_SHADE_V,
	SDL_EFFECTS_PIXEL_ALPHA_SHADE_V2,
	SDL_EFFECTS_PIXEL_ALPHA_SHADE_V3,
};


int png_save_surface(char *filename, SDL_Surface *surf);
void SDL_ShadePixelAlpha (SDL_Surface *Surface, int alpha, int mode);
void SDL_SetPixelAlpha (SDL_Surface *Surface, int surfaceAlpha);


int main(int argc, char *argv[]) {
	char *argv0 = argv[0];
	SDL_Surface *screen;
	TTF_Font *font;
	TTF_Font *font2;
	SDL_Surface *text, *temp;
	int ptsize;
	int ptsize2;
	int i, done;
	int effect = 0;
	int trans = 0;
	int rdiff, gdiff, bdiff;
	SDL_Color colors[NUM_COLORS];
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };
	SDL_Color black = { 0x00, 0x00, 0x00, 0 };

	SDL_Color green = { 0x00, 0xff, 0x00, 0 };
	SDL_Color pink = { 0xff, 0x33, 0xfc, 0 };

	SDL_Color *forecol;
	SDL_Color *backcol;
	SDL_Rect dstrect;
	SDL_Event event;
	int rendersolid;
	int renderstyle;
	int outline;
	int hinting;
	int kerning;
	int dump;
	int use_bg = 0;
	enum {
		RENDER_LATIN1,
		RENDER_UTF8,
		RENDER_UNICODE
	} rendertype;
	char *message, string[128];

	/* Look for special execution mode */
	dump = 0;
	/* Look for special rendering types */
	rendersolid = 0;
	renderstyle = TTF_STYLE_NORMAL;
	rendertype = RENDER_LATIN1;
	outline = 0;
	hinting = TTF_HINTING_NORMAL;
	kerning = 1;
	/* Default is black and white */
	forecol = &green;
	backcol = &white;
	for ( i=1; argv[i] && argv[i][0] == '-'; ++i ) {
		if ( strcmp(argv[i], "-solid") == 0 ) {
			rendersolid = 1;
		} else
		if ( strcmp(argv[i], "-utf8") == 0 ) {
			rendertype = RENDER_UTF8;
		} else
		if ( strcmp(argv[i], "-unicode") == 0 ) {
			rendertype = RENDER_UNICODE;
		} else
		if ( strcmp(argv[i], "-b") == 0 ) {
			renderstyle |= TTF_STYLE_BOLD;
		} else
		if ( strcmp(argv[i], "-i") == 0 ) {
			renderstyle |= TTF_STYLE_ITALIC;
		} else
		if ( strcmp(argv[i], "-u") == 0 ) {
			renderstyle |= TTF_STYLE_UNDERLINE;
		} else
		if ( strcmp(argv[i], "-s") == 0 ) {
			renderstyle |= TTF_STYLE_STRIKETHROUGH;
		} else
		if ( strcmp(argv[i], "-outline") == 0 ) {
			if ( sscanf (argv[++i], "%d", &outline) != 1 ) {
				fprintf(stderr, Usage, argv0);
				return(1);
			}
		} else
		if ( strcmp(argv[i], "-hintlight") == 0 ) {
			hinting = TTF_HINTING_LIGHT;
		} else
		if ( strcmp(argv[i], "-hintmono") == 0 ) {
			hinting = TTF_HINTING_MONO;
		} else
		if ( strcmp(argv[i], "-hintnone") == 0 ) {
			hinting = TTF_HINTING_NONE;
		} else
		if ( strcmp(argv[i], "-nokerning") == 0 ) {
			kerning = 0;
		} else
		if ( strcmp(argv[i], "-dump") == 0 ) {
			dump = 1;
		} else
		if ( strcmp(argv[i], "-effect") == 0 ) {
			effect = 1;
		} else
		if ( strcmp(argv[i], "-trans") == 0 ) {
			trans = 1;
		} else
		if ( strcmp(argv[i], "-fgcol") == 0 ) {
			int r, g, b;
			if ( sscanf (argv[++i], "%d,%d,%d", &r, &g, &b) != 3 ) {
				fprintf(stderr, Usage, argv0);
				return(1);
			}
			forecol->r = (Uint8)r;
			forecol->g = (Uint8)g;
			forecol->b = (Uint8)b;
		} else
		if ( strcmp(argv[i], "-bgcol") == 0 ) {
			int r, g, b;
			if ( sscanf (argv[++i], "%d,%d,%d", &r, &g, &b) != 3 ) {
				fprintf(stderr, Usage, argv0);
				return(1);
			}
			backcol->r = (Uint8)r;
			backcol->g = (Uint8)g;
			backcol->b = (Uint8)b;
			use_bg = 1;
		} else {
			fprintf(stderr, Usage, argv0);
			return(1);
		}
	}
	argv += i;
	argc -= i;

	/* Check usage */
	if ( ! argv[0] ) {
		fprintf(stderr, Usage, argv0);
		return(1);
	}

	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		return(2);
	}

	/* Initialize the TTF library */
	if ( TTF_Init() < 0 ) {
		fprintf(stderr, "Couldn't initialize TTF: %s\n",SDL_GetError());
		SDL_Quit();
		return(2);
	}
	ptsize = 0;
	if ( argc > 1 ) {
		ptsize = atoi(argv[1]);
	}
	if ( ptsize == 0 ) {
		i = 2;
		ptsize = DEFAULT_PTSIZE;
	} else {
		i = 3;
	}
	ptsize2 = ptsize + 1;

	font = TTF_OpenFont(argv[0], ptsize);
	if ( font == NULL ) {
		fprintf(stderr, "Couldn't load %d pt font from %s: %s\n", ptsize, argv[0], SDL_GetError());
		cleanup(2);
	}

	font2 = TTF_OpenFont(argv[0], ptsize);
	if ( font2 == NULL ) {
		fprintf(stderr, "Couldn't load %d pt font2 from %s: %s\n", ptsize2, argv[0], SDL_GetError());
		cleanup(2);
	}
	TTF_SetFontStyle(font, renderstyle);
	TTF_SetFontOutline(font, outline);
	TTF_SetFontKerning(font, kerning);
	TTF_SetFontHinting(font, hinting);

	TTF_SetFontStyle(font2, renderstyle);
	TTF_SetFontOutline(font2, outline);
	TTF_SetFontKerning(font2, kerning);
	TTF_SetFontHinting(font2, hinting);

//TTF_GetFontOutline(font);
//TTF_GetFontOutline(font2);

	screen = SDL_SetVideoMode(512, 512, 0, SDL_SWSURFACE);
	if ( screen == NULL ) {
		fprintf(stderr, "Couldn't set 512x512x8 video mode: %s\n", SDL_GetError());
		cleanup(2);
	}

	rdiff = backcol->r - forecol->r;
	gdiff = backcol->g - forecol->g;
	bdiff = backcol->b - forecol->b;
	for ( i=0; i<NUM_COLORS; ++i ) {
		colors[i].r = forecol->r + (i*rdiff)/4;
		colors[i].g = forecol->g + (i*gdiff)/4;
		colors[i].b = forecol->b + (i*bdiff)/4;
	}
//	SDL_SetColors(screen, colors, 0, NUM_COLORS);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_UpdateRect(screen, 0, 0, 0, 0);


	if ( argc > 2 ) {
		message = argv[2];
	} else {
		message = DEFAULT_TEXT;
	}


	Uint32 rmask, gmask, bmask, amask;
	char *input, *output, *str_ptr;
	int namelen;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
	#else
	rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
	#endif

	SDL_Surface *output_surf;
	output_surf = SDL_CreateRGBSurface(screen->flags, 512, 512, screen->format->BitsPerPixel, rmask, gmask, bmask, screen->format->BitsPerPixel<=24?0:amask);


	uint16_t char_num = 0;
	uint16_t x = 0;
	uint16_t y = 0;
	char tmp_str[2];
	for (char_num = 0; char_num <= 255; char_num++) {
		sprintf(tmp_str, "%c ", char_num);
		tmp_str[0] = char_num;
		tmp_str[1] = 0;
		if (use_bg == 1) {
			text = TTF_RenderText_Solid(font2, tmp_str, *backcol);
			if ( text != NULL ) {
				dstrect.w = text->w;
				dstrect.h = text->h;

				dstrect.x = x * (512 / 16) + 16 - text->w / 2 + 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2 + 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);

				dstrect.x = x * (512 / 16) + 16 - text->w / 2 - 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2 - 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);

				dstrect.x = x * (512 / 16) + 16 - text->w / 2 - 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2 + 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);

				dstrect.x = x * (512 / 16) + 16 - text->w / 2 + 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2 - 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);


				dstrect.x = x * (512 / 16) + 16 - text->w / 2 + 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);

				dstrect.x = x * (512 / 16) + 16 - text->w / 2 - 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);

				dstrect.x = x * (512 / 16) + 16 - text->w / 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2 + 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);

				dstrect.x = x * (512 / 16) + 16 - text->w / 2;
				dstrect.y = y * (512 / 16) + 16 - text->h / 2 - 2;
				SDL_BlitSurface(text, NULL, output_surf, &dstrect);
			}
		}
		text = TTF_RenderText_Solid(font2, tmp_str, black);
		if ( text != NULL ) {

			dstrect.w = text->w;
			dstrect.h = text->h;

			dstrect.x = x * (512 / 16) + 16 - text->w / 2 + 1;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2 + 1;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);

			dstrect.x = x * (512 / 16) + 16 - text->w / 2 - 1;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2 - 1;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);

			dstrect.x = x * (512 / 16) + 16 - text->w / 2 - 1;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2 + 1;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);

			dstrect.x = x * (512 / 16) + 16 - text->w / 2 + 1;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2 - 1;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);


			dstrect.x = x * (512 / 16) + 16 - text->w / 2 + 1;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);

			dstrect.x = x * (512 / 16) + 16 - text->w / 2 - 1;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);

			dstrect.x = x * (512 / 16) + 16 - text->w / 2;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2 + 1;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);

			dstrect.x = x * (512 / 16) + 16 - text->w / 2;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2 - 1;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);
		}

		text = TTF_RenderText_Blended(font, tmp_str, *forecol);
		if ( text != NULL ) {

			if (effect == 1) {
				SDL_ShadePixelAlpha(text, 255, SDL_EFFECTS_PIXEL_ALPHA_SHADE_H);
			}

			dstrect.x = x * (512 / 16) + 16 - text->w / 2;
			dstrect.y = y * (512 / 16) + 16 - text->h / 2;
			dstrect.w = text->w;
			dstrect.h = text->h;
			SDL_BlitSurface(text, NULL, output_surf, &dstrect);
		}

		if (x == 15) {
			x = 0;
			y++;
		} else {
			x++;
		}
	}

	if (trans == 1) {
		SDL_SetPixelAlpha(output_surf, 72);
	}

	SDL_BlitSurface(output_surf, NULL, screen, NULL);
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	png_save_surface("/tmp/font.png", output_surf);

	/* Set the text colorkey and convert to display format */
	if ( SDL_SetColorKey(text, SDL_SRCCOLORKEY|SDL_RLEACCEL, 0) < 0 ) {
		fprintf(stderr, "Warning: Couldn't set text colorkey: %s\n",
								SDL_GetError());
	}
	temp = SDL_DisplayFormat(text);
	if ( temp != NULL ) {
		SDL_FreeSurface(text);
		text = temp;
	}

	/* Wait for a keystroke, and blit text on mouse press */
	done = 0;

//	done = 1;

	while ( ! done ) {
		if ( SDL_WaitEvent(&event) < 0 ) {
			fprintf(stderr, "SDL_PullEvent() error: %s\n",
								SDL_GetError());
			done = 1;
			continue;
		}
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				dstrect.x = event.button.x - text->w/2;
				dstrect.y = event.button.y - text->h/2;
				dstrect.w = text->w;
				dstrect.h = text->h;
				if ( SDL_BlitSurface(text, NULL, screen, &dstrect) == 0 ) {
					SDL_UpdateRects(screen, 1, &dstrect);
				} else {
					fprintf(stderr, "Couldn't blit text to display: %s\n", SDL_GetError());
				}
				break;
			case SDL_KEYDOWN:
			case SDL_QUIT:
				done = 1;
				break;
			default:
				break;
		}
	}
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	cleanup(0);

	/* Not reached, but fixes compiler warnings */
	return 0;
}



/* SaveSurf: an example on how to save a SDLSurface in PNG
   Copyright (C) 2006 Angelo "Encelo" Theodorou
 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
   NOTE: 
 
   This program is part of "Mars, Land of No Mercy" SDL examples, 
   you can find other examples on http://marsnomercy.org
*/

#include <stdlib.h>
#include <png.h>
#include <SDL.h>


static int png_colortype_from_surface(SDL_Surface *surface) {
	int colortype = PNG_COLOR_MASK_COLOR;
	if (surface->format->palette)
		colortype |= PNG_COLOR_MASK_PALETTE;
	else if (surface->format->Amask)
		colortype |= PNG_COLOR_MASK_ALPHA;
	return colortype;
}

void png_user_warn(png_structp ctx, png_const_charp str) {
	fprintf(stderr, "libpng: warning: %s\n", str);
}

void png_user_error(png_structp ctx, png_const_charp str) {
	fprintf(stderr, "libpng: error: %s\n", str);
}

int png_save_surface(char *filename, SDL_Surface *surf) {
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	int i, colortype;
	png_bytep *row_pointers;
	/* Opening output file */
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		perror("fopen error");
		return -1;
	}
	/* Initializing png structures and callbacks */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 
		NULL, png_user_error, png_user_warn);
	if (png_ptr == NULL) {
		printf("png_create_write_struct error!\n");
		return -1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		printf("png_create_info_struct error!\n");
		exit(-1);
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		exit(-1);
	}
	png_init_io(png_ptr, fp);
	colortype = png_colortype_from_surface(surf);
	png_set_IHDR(png_ptr, info_ptr, surf->w, surf->h, 8, colortype,	PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	/* Writing the image */
	png_write_info(png_ptr, info_ptr);
	png_set_packing(png_ptr);
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*surf->h);
	for (i = 0; i < surf->h; i++)
		row_pointers[i] = (png_bytep)(Uint8 *)surf->pixels + i*surf->pitch;
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);
	/* Cleaning out... */
	free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return 0;
}

void SDL_ShadePixelAlpha (SDL_Surface *Surface, int alpha, int mode) {
	SDL_PixelFormat* format = Surface->format;
	Uint32 *pixels = (Uint32*)Surface->pixels;
	Uint32 RGBMask = format->Rmask | format->Gmask | format->Bmask;
	Uint32 alphaShift = format->Ashift;
	Uint32 alphaMask = format->Amask;
	Uint32 pitchPixels = Surface->pitch / 4;
	Uint32 pixel = 0;
	int surfaceAlpha = alpha;
	int pixelAlpha = 0;
	int ndx = 0;
	int w = 0;
	int h = 0;
	for (h = 0; h < Surface->h; h++) {
		ndx = (h * pitchPixels);
		for (w = 0; w < Surface->w; w++) {
			pixel = pixels[ndx];
			pixelAlpha = (pixel & alphaMask) >> alphaShift;
			if (pixelAlpha > 0) {
			        switch(mode) {
					case SDL_EFFECTS_PIXEL_ALPHA_SHADE_H:
						surfaceAlpha = (alpha + 255) * (Surface->h - h) / Surface->h;
surfaceAlpha = surfaceAlpha + 50;
						if (surfaceAlpha < 0) {
							surfaceAlpha = 0;
						} else if (surfaceAlpha > 255) {
							surfaceAlpha = 255;
						}
						break;
					case SDL_EFFECTS_PIXEL_ALPHA_SHADE_H2:
						surfaceAlpha = alpha * (Surface->h - (h * 1.1)) / (Surface->h);
						if (surfaceAlpha < 0) {
							surfaceAlpha = 0;
						} else if (surfaceAlpha > 255) {
							surfaceAlpha = 255;
						}
						break;
					case SDL_EFFECTS_PIXEL_ALPHA_SHADE_V:
						surfaceAlpha = alpha * (Surface->w - w) / Surface->w;
						if (surfaceAlpha < 0) {
							surfaceAlpha = 0;
						} else if (surfaceAlpha > 255) {
							surfaceAlpha = 255;
						}
						break;
					case SDL_EFFECTS_PIXEL_ALPHA_SHADE_V2:
						surfaceAlpha = alpha * (Surface->w - w) / Surface->w / 5;
						if (surfaceAlpha < 0) {
							surfaceAlpha = 0;
						} else if (surfaceAlpha > 255) {
							surfaceAlpha = 255;
						}
						break;
					case SDL_EFFECTS_PIXEL_ALPHA_SHADE_V3:
						if (w < Surface->w / 3) {
							surfaceAlpha = 100 + alpha * w / Surface->w * 3;
						} else if (w > Surface->w / 3 * 2) {
							surfaceAlpha = 100 + alpha * (Surface->w - w) / Surface->w * 3;
						} else {
							surfaceAlpha = 100 + alpha;
						}
						break;
				}
				if (surfaceAlpha < 5) {
					surfaceAlpha = 5;
				} else if (surfaceAlpha > 255) {
					surfaceAlpha = 255;
				}
				pixelAlpha = ((pixelAlpha * surfaceAlpha) / 255) << alphaShift;
				pixels[ndx] = (pixel & RGBMask) | pixelAlpha;  
			}
			ndx++;
		}
	}
}

void SDL_SetPixelAlpha (SDL_Surface *Surface, int surfaceAlpha) {
	SDL_PixelFormat* format = Surface->format;
	Uint32 *pixels = (Uint32*)Surface->pixels;
	Uint32 RGBMask = format->Rmask | format->Gmask | format->Bmask;
	Uint32 alphaShift = format->Ashift;
	Uint32 alphaMask = format->Amask;
	Uint32 pitchPixels = Surface->pitch / 4;
	Uint32 pixel = 0;
	int pixelAlpha = 0;
	int ndx = 0;
	int w = 0;
	int h = 0;
	for (h = 0; h < Surface->h; h++) {
		ndx = (h * pitchPixels);
		for (w = 0; w < Surface->w; w++) {
			pixel = pixels[ndx];
			pixelAlpha = (pixel & alphaMask) >> alphaShift;
			if (pixelAlpha > 0) {
				pixelAlpha = ((pixelAlpha * surfaceAlpha) / 255) << alphaShift;
				pixels[ndx] = (pixel & RGBMask) | pixelAlpha;  
			}
			ndx++;
		}
	}
}
