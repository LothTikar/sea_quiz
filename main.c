#include <gtk/gtk.h>

struct Question
{
	char *question; /* ptr to header, do not free */
	char *answer; /* stores answer, free this when done */
}

struct Item
{
	int num_questions;
	int num_hints;
	int num_images;
	struct Question *questions;
	char **hints;
	char **images; /* image filenames, give to GTK for creating image widgets via filename */
}

int num_items;
struct Item *items;

char **header; /* only copy of header, do not free until program completion */

static void activate ( GtkApplication *app,
                       gpointer        user_data )
{
    GtkWidget *window;

    window = gtk_application_window_new ( app );
    gtk_window_set_title ( GTK_WINDOW ( window ), "Window" );
    gtk_window_set_default_size ( GTK_WINDOW ( window ), 200, 200 );
    gtk_widget_show_all ( window );
}

/* program logic

	Create buttons that set the label status.
	
	When butten is pressed for next question, create dialog if user hasn't gotten all questions right by checking labels.
	
*/

/* function to find image names

	search directory of csv file for all names that begin with image prefix
 */

/* function to process csv file

	create header listing

	go row by row, use header to figure out what to do

	skip blanks, so there can be unused questions for items, eg rocks don't have luster but minerals do
 */

int main ( int    argc,
           char **argv )
{
	
    GtkApplication *app;
    int status;

    app = gtk_application_new ( "org.gtk.example", G_APPLICATION_FLAGS_NONE );
    g_signal_connect ( app, "activate", G_CALLBACK ( activate ), NULL );
    status = g_application_run ( G_APPLICATION ( app ), argc, argv );
    g_object_unref ( app );

    return status;
}
