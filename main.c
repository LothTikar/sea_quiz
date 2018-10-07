#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

const char *WINDOW_NAME = "Sea Quiz";

struct Question {
    char *question; /* ptr to header, do not free */
    char *answer; /* stores answer, free this when done */
};

struct Item {
    int num_questions;
    int num_hints;
    int num_images;
    struct Question *questions;
    char **hints;
    char **images; /* image filenames, give to GTK for creating image widgets via filename */
};

void free_ptr_array(unsigned int size, void **array)
{
    int i;

    if(array != NULL) {
        for(i = 0; i < size; ++i)
            free(array[i]);

        free(array);
    }
}

void free_item_contents(struct Item item)
{
    int i;

    if(item.questions != NULL) {
        for(i = 0; i < item.num_questions; ++i)
            free((item.questions + i)->answer);

        free(item.questions);
    }

    free_ptr_array(item.num_hints, (void **)item.hints);
    free_ptr_array(item.num_images, (void **)item.images);
}

int num_items;
struct Item *items;

int header_size;
char **header; /* only copy of header, do not free until program completion */

static void activate(GtkApplication *app,
                     gpointer        user_data)
{
    GtkWidget *window;
    GtkWidget *label;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), WINDOW_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    label = gtk_label_new("No quiz file loaded.\nPlease specify in command line arguments.");
    gtk_container_add(GTK_CONTAINER(window), label);

    gtk_widget_show_all(window);
}

/*  program logic

	Create buttons that set the label status.

	When butten is pressed for next question, create dialog if user hasn't
	gotten all questions right by checking labels.

*/

/*  function to find image names

	search directory of csv file for all names that begin with image prefix
*/

void free_items()
{
    int i;

    if(items != NULL) {
        for(i = 0; i < num_items; ++i)
            free_item_contents(items[i]);

        free(items);
    }
}

void free_global_ptrs(void)
{
    free_ptr_array(header_size, (void **)header);
    free_items();
}

/*  function to process csv file

	create header listing

	go row by row, use header to figure out what to do

	skip blanks, so there can be unused questions for items, eg rocks don't
	have luster but minerals do
*/

static void open(GApplication *application,
                 gpointer      files,
                 gint          n_files,
                 gchar        *hint,
                 gpointer      user_data)
{
    printf("%s\n", hint);
    printf("%d\n", n_files);
}

int main(int    argc,
         char **argv)
{
    GtkApplication *app;
    int status;

    num_items = 0;
    items = NULL;

    header_size = 0;
    header = NULL;

    app = gtk_application_new("net.lothtikar.sea_quiz", G_APPLICATION_HANDLES_OPEN);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    g_signal_connect(app, "open", G_CALLBACK(open), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    free_global_ptrs();

    return status;
}
