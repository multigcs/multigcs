
#include <all.h>

#if defined USE_VLC

#define WIDTH 640
#define HEIGHT 480
#define VIDEOWIDTH WIDTH
#define VIDEOHEIGHT HEIGHT
#define mask32(BYTE) (*(uint32_t *)(uint8_t [4]){ [BYTE] = 0xff })

struct ctx {
	SDL_Surface *surf;
	SDL_mutex *mutex;
};

static struct ctx ctx;
static libvlc_instance_t *libvlc;
static libvlc_event_manager_t *evtman;
static libvlc_media_t *m;
static libvlc_media_player_t *mp;
static SDL_Surface *data_sf = NULL;
static uint8_t playing = 0;

static void *lock(void *data, void **p_pixels) {
	struct ctx *ctx = data;
	SDL_LockMutex(ctx->mutex);
	SDL_LockSurface(ctx->surf);
	*p_pixels = ctx->surf->pixels;
	return NULL;
}

static void unlock(void *data, void *id, void *const *p_pixels) {
	struct ctx *ctx = data;
	SDL_UnlockSurface(ctx->surf);
	SDL_UnlockMutex(ctx->mutex);
	assert(id == NULL);
}

static void display(void *data, void *id) {
	(void) data;
	assert(id == NULL);
}

void on_error_vlc(const libvlc_event_t *event, void *data) {
	SDL_Log("vlc: error\n");
}

void on_end_vlc(const libvlc_event_t *event, void *data) {
	SDL_Log("vlc: end of stream\n");
	playing = 0;
}

void vlc_init(char *url) {
	playing = 1;
	char location[1024];
	char const *vlc_argv[] = {
		"--no-xlib",
		"--no-osd",
		//		"--input-repeat=-1",
	};
	data_sf = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOWIDTH, VIDEOHEIGHT, 24, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);
	ctx.surf = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOWIDTH, VIDEOHEIGHT, 24, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);
	ctx.mutex = SDL_CreateMutex();
	int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);
	libvlc = libvlc_new(vlc_argc, vlc_argv);
	sprintf(location, "v4l2://%s", url);
	m = libvlc_media_new_location(libvlc, location);
	mp = libvlc_media_player_new_from_media(m);
	evtman = libvlc_media_player_event_manager(mp);
	libvlc_event_attach(evtman, libvlc_MediaPlayerEndReached, on_end_vlc, NULL);
	libvlc_event_attach(evtman, libvlc_MediaPlayerEncounteredError, on_error_vlc, NULL);
	libvlc_media_release(m);
	libvlc_video_set_callbacks(mp, lock, unlock, display, &ctx);
	libvlc_video_set_format(mp, "RV24", VIDEOWIDTH, VIDEOHEIGHT, VIDEOWIDTH * 3);
	libvlc_media_player_play(mp);
}

void vlc_exit(void) {
	libvlc_event_detach(evtman, libvlc_MediaPlayerEncounteredError, on_error_vlc, NULL);
	libvlc_event_detach(evtman, libvlc_MediaPlayerEndReached, on_end_vlc, NULL);
	libvlc_media_player_stop(mp);
	libvlc_media_player_release(mp);
	libvlc_release(libvlc);
	SDL_DestroyMutex(ctx.mutex);
	SDL_FreeSurface(ctx.surf);
	SDL_FreeSurface(data_sf);
}

SDL_Surface *vlc_update(void) {
	SDL_LockMutex(ctx.mutex);
	SDL_BlitSurface(ctx.surf, NULL, data_sf, NULL);
	SDL_UnlockMutex(ctx.mutex);
	return data_sf;
}

uint8_t vlc_is_playing(void) {
	return playing;
}

#endif
