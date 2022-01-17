#include <stdio.h>
#include <wayland-client.h>
#include <stdlib.h>

struct wl_display *display;

int main ( )
{
    display = wl_display_connect ( 0 );
    if ( !display )
    {
	fprintf ( stderr, "Can't connect to display\n" );
	exit ( 1 );
    }

    printf ( "connected to display\n" );
    wl_display_disconnect ( display );
    printf ( "disconnected from display\n" );

	return 0;
}
