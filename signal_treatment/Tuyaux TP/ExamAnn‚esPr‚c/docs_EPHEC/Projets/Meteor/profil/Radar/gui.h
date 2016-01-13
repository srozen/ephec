#include <gtk/gtk.h>


void destroy(GtkWidget *widget, gpointer *data);
char * gui_file_chooser(char defaultPath[100],char * title,int action);
int gui_init_progress_bar(GtkWidget *pProgress,gchar * title,int argc,char * argv[]);
void gui_increase_progress_bar(GtkWidget *pProgress,gdouble progress);
int gui_yes_no_No_action(GtkWidget *widget, gpointer *data);
int gui_yes_no_Yes_action(GtkWidget *widget, gpointer *data);
void gui_yes_no_dialog(char question[100],char buttonLeft[50],char buttonRight[50]);
GtkWidget* create_AudioTriggerMeanPowerParams (void);
void gui_audio_trigger();
void gui_init(int argc,char *argv[]);
