#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>


struct wl_display *display       = 0;
struct wl_compositor *compositor = 0;


static void global_rgistry_handler ( void *data,
									struct wl_registry *registry,
									uint32_t id,
									const char *interface,
									uint32_t version )
{
	printf ( "Got a registry event for %s id %d\n", interface, id );
	if ( !strcmp ( interface, "wl_compositor" ) )
	{
		compositor = wl_registry_bind ( registry,
										id,
										&wl_compositor_interface,
										1 );
	}
}

static void global_rgistry_remover ( void *data, struct wl_registry *registry, uint32_t id )
{
	printf ( "Got a registry losing event for %d\n", id );
}

static const struct wl_registry_listener registry_listener =
{
     global_rgistry_handler,
	 global_rgistry_remover
};


int main ( int argc, char **argv )
{
	display = wl_display_connect ( 0 );
	if ( !display )
	{
		fprintf ( stderr, "Can't connect to display!\n" );
		exit ( 1 );
	}


	printf ( "connected to display\n" );

	struct wl_registry *registry = wl_display_get_registry ( display );
	wl_registry_add_listener ( registry, &registry_listener, 0 );

	wl_display_dispatch  ( display );
	wl_display_roundtrip ( display );

	if ( !compositor )
	{
		fprintf ( stderr, "Can't find compositor\n" );
		exit ( 1 );
	}
	else
	{
		fprintf ( stderr, "Found compositor\n" );
	}

	wl_display_disconnect ( display );
	printf ( "disconnected from display\n" );

	return 0;
}
