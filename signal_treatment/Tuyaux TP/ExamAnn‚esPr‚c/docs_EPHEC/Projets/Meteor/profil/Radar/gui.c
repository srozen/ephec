#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "globales.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

/**
*
* Ce fichier contient des portions de
* codes provenant de :
*
* http://library.gnome.org/devel/gtk/stable/
* http://fr.wikibooks.org/wiki/Programmation_GTK_plus_Widgets_s%C3%A9lections_de_fichiers
*
**/

void destroy(GtkWidget *widget, gpointer *data){
   gtk_widget_destroy(widget);
   gtk_main_quit ();
}

char * gui_file_chooser(char defaultPath[100],char * title,int action){

   GtkWidget *filew;

   filew = gtk_file_chooser_dialog_new(title,NULL,action,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,NULL);

   gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(filew),"/home");

   if (gtk_dialog_run (GTK_DIALOG (filew)) == GTK_RESPONSE_ACCEPT){
        if(action == GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER){
            strcpy(dossier_sortie,(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filew))));
        }
        else if(action == GTK_FILE_CHOOSER_ACTION_OPEN){
            strcpy(fichier_entree,(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filew))));
        }
   }
   else{
        gtk_widget_destroy(filew);
        exit(0);
   }

   gtk_widget_destroy(filew);
   return dossier_sortie;
}

int gui_progress_bar_init(GtkWidget *pProgress,gchar * title,gchar * progressText){
   GtkWidget * pWindow;
   GtkWidget * pMainVBox;

   pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
   gtk_window_set_title(GTK_WINDOW(pWindow),title);
   gtk_window_set_default_size(GTK_WINDOW(pWindow), 300, 35);
   gtk_container_set_border_width(GTK_CONTAINER(pWindow), 2);

   pMainVBox = gtk_vbox_new(TRUE, 0);
   gtk_container_add(GTK_CONTAINER(pWindow), pMainVBox);

   pProgress = gtk_progress_bar_new();
   gtk_box_pack_start(GTK_BOX(pMainVBox), pProgress, TRUE, FALSE, 0);
   gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pProgress),GTK_PROGRESS_LEFT_TO_RIGHT);

   gtk_widget_show(pWindow);
   gtk_widget_show(pMainVBox);
   gtk_widget_show(pProgress);


   gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pProgress),progressText);
   gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pProgress),0.0);
   while (gtk_events_pending())
            gtk_main_iteration();

   gtk_grab_add(pProgress);

   return pProgress;
}

void gui_progress_bar_increase(GtkWidget *pProgress,gdouble progress,gchar * progressPercentText){

   if(gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(pProgress) < 1)){
        //gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pProgress),progressPercentText);
        printf("\nDebug gui_progress_bar_increase : ligne 96\n");
        getchar();
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pProgress), progress); /* Modification de la valeur de la barre de progression */
        printf("\nDebug gui_progress_bar_increase : ligne 99\n");
        getchar();
        while (gtk_events_pending())
            gtk_main_iteration();
        printf("\nDebug gui_progress_bar_increase : ligne 103\n");
        getchar();
   }
}

int gui_yes_no_No_action(GtkWidget *widget,GtkWindow * window){
    destroy(window,NULL);
    gtk_main_quit();
    yesNoAnswer = 2;
    return yesNoAnswer;
}

int gui_yes_no_Yes_action(GtkWidget *widget,GtkWindow * window){
    destroy(window,NULL);
    gtk_main_quit();
    yesNoAnswer = 1;
    return yesNoAnswer;
}

void gui_yes_no_dialog(char question[100],char buttonLeft[50],char buttonRight[50]){
    GtkWidget * window;
    GtkWidget * label;
    GtkWidget * yesButton;
    GtkWidget * noButton;

    window = gtk_dialog_new();
    label = gtk_label_new (question);

    yesButton = gtk_button_new();
    noButton = gtk_button_new();

    gtk_button_set_label(GTK_BUTTON(yesButton),buttonLeft);
    gtk_button_set_label(GTK_BUTTON(noButton),buttonRight);

    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area), yesButton,
                    TRUE, TRUE, 10);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area), noButton,
                    TRUE, TRUE, 10);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->vbox), label, TRUE,
                    TRUE, 0);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gui_yes_no_No_action),window);
    g_signal_connect(G_OBJECT(noButton), "clicked", G_CALLBACK(gui_yes_no_No_action),window);
    g_signal_connect(G_OBJECT(yesButton), "clicked", G_CALLBACK(gui_yes_no_Yes_action),window);

    gtk_widget_show (yesButton);
    gtk_widget_show (noButton);
    gtk_widget_show (label);
    gtk_widget_show (window);

    gtk_main();

    return EXIT_SUCCESS;
}

//void on_OKButton_clicked(GtkWidget *widget, gpointer *data){
//
//}
//
//GtkWidget* create_AudioTriggerMeanPowerParams(){
//  GtkWidget *AudioTriggerMeanPowerParams;
//  GdkPixbuf *AudioTriggerMeanPowerParams_icon_pixbuf;
//  GtkWidget *vbox1;
//  GtkWidget *image1;
//  GtkWidget *hseparator1;
//  GtkWidget *PrecisionLabel;
//  GtkWidget *hscale1;
//  GtkWidget *hseparator2;
//  GtkWidget *SeuilLabel;
//  GtkWidget *hbox1;
//  GtkWidget *MaxLabel;
//  GtkWidget *hscale2;
//  GtkWidget *hbox2;
//  GtkWidget *MinLabel;
//  GtkWidget *hscale3;
//  GtkWidget *hseparator3;
//  GtkWidget *hbuttonbox1;
//  GtkWidget *OKButton;
//  GtkWidget *alignment1;
//  GtkWidget *hbox3;
//  GtkWidget *image2;
//  GtkWidget *label6;
//  GtkWidget *ResetParams;
//  GtkWidget *alignment2;
//  GtkWidget *hbox4;
//  GtkWidget *image3;
//  GtkWidget *label7;
//
//  AudioTriggerMeanPowerParams = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//  gtk_widget_set_size_request (AudioTriggerMeanPowerParams, 400, 300);
//  gtk_container_set_border_width (GTK_CONTAINER (AudioTriggerMeanPowerParams), 1);
//  gtk_window_set_title (GTK_WINDOW (AudioTriggerMeanPowerParams), _("Parametrage"));
//  AudioTriggerMeanPowerParams_icon_pixbuf = create_pixbuf ("radarIcon.png");
//  if (AudioTriggerMeanPowerParams_icon_pixbuf)
//    {
//      gtk_window_set_icon (GTK_WINDOW (AudioTriggerMeanPowerParams), AudioTriggerMeanPowerParams_icon_pixbuf);
//      gdk_pixbuf_unref (AudioTriggerMeanPowerParams_icon_pixbuf);
//    }
//
//  vbox1 = gtk_vbox_new (FALSE, 7);
//  gtk_widget_show (vbox1);
//  gtk_container_add (GTK_CONTAINER (AudioTriggerMeanPowerParams), vbox1);
//  gtk_container_set_border_width (GTK_CONTAINER (vbox1), 2);
//
//  image1 = create_pixmap (AudioTriggerMeanPowerParams, "paramLogo.png");
//  gtk_widget_show (image1);
//  gtk_box_pack_start (GTK_BOX (vbox1), image1, TRUE, TRUE, 0);
//
//  hseparator1 = gtk_hseparator_new ();
//  gtk_widget_show (hseparator1);
//  gtk_box_pack_start (GTK_BOX (vbox1), hseparator1, TRUE, TRUE, 0);
//
//  PrecisionLabel = gtk_label_new (_("Precision de la detection :"));
//  gtk_widget_show (PrecisionLabel);
//  gtk_box_pack_start (GTK_BOX (vbox1), PrecisionLabel, FALSE, FALSE, 0);
//  gtk_misc_set_alignment (GTK_MISC (PrecisionLabel), 0.2, 0.5);
//  gtk_label_set_width_chars (GTK_LABEL (PrecisionLabel), 30);
//
//  hscale1 = gtk_hscale_new (GTK_ADJUSTMENT (gtk_adjustment_new (100, 10, 250, 2, 0, 0)));
//  gtk_widget_show (hscale1);
//  gtk_box_pack_start (GTK_BOX (vbox1), hscale1, TRUE, TRUE, 0);
//  gtk_scale_set_value_pos (GTK_SCALE (hscale1), GTK_POS_LEFT);
//
//  hseparator2 = gtk_hseparator_new ();
//  gtk_widget_show (hseparator2);
//  gtk_box_pack_start (GTK_BOX (vbox1), hseparator2, TRUE, TRUE, 0);
//
//  SeuilLabel = gtk_label_new (_("Seuils de detection :"));
//  gtk_widget_show (SeuilLabel);
//  gtk_box_pack_start (GTK_BOX (vbox1), SeuilLabel, FALSE, FALSE, 0);
//  gtk_misc_set_alignment (GTK_MISC (SeuilLabel), 0.2, 0.5);
//  gtk_misc_set_padding (GTK_MISC (SeuilLabel), 0, 10);
//  gtk_label_set_width_chars (GTK_LABEL (SeuilLabel), 30);
//
//  hbox1 = gtk_hbox_new (FALSE, 0);
//  gtk_widget_show (hbox1);
//  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, FALSE, FALSE, 0);
//
//  MaxLabel = gtk_label_new (_("Maximum "));
//  gtk_widget_show (MaxLabel);
//  gtk_box_pack_start (GTK_BOX (hbox1), MaxLabel, FALSE, FALSE, 0);
//
//  hscale2 = gtk_hscale_new (GTK_ADJUSTMENT (gtk_adjustment_new (4, 0, 50, 2, 0, 0)));
//  gtk_widget_show (hscale2);
//  gtk_box_pack_start (GTK_BOX (hbox1), hscale2, TRUE, TRUE, 0);
//  gtk_scale_set_value_pos (GTK_SCALE (hscale2), GTK_POS_RIGHT);
//
//  hbox2 = gtk_hbox_new (FALSE, 0);
//  gtk_widget_show (hbox2);
//  gtk_box_pack_start (GTK_BOX (vbox1), hbox2, TRUE, TRUE, 0);
//
//  MinLabel = gtk_label_new (_("Minimum "));
//  gtk_widget_show (MinLabel);
//  gtk_box_pack_start (GTK_BOX (hbox2), MinLabel, FALSE, FALSE, 0);
//
//  hscale3 = gtk_hscale_new (GTK_ADJUSTMENT (gtk_adjustment_new (1, 0, 50, 0, 0, 0)));
//  gtk_widget_show (hscale3);
//  gtk_box_pack_start (GTK_BOX (hbox2), hscale3, TRUE, TRUE, 0);
//  gtk_scale_set_value_pos (GTK_SCALE (hscale3), GTK_POS_RIGHT);
//
//  hseparator3 = gtk_hseparator_new ();
//  gtk_widget_show (hseparator3);
//  gtk_box_pack_start (GTK_BOX (vbox1), hseparator3, TRUE, TRUE, 0);
//
//  hbuttonbox1 = gtk_hbutton_box_new ();
//  gtk_widget_show (hbuttonbox1);
//  gtk_box_pack_start (GTK_BOX (vbox1), hbuttonbox1, TRUE, TRUE, 0);
//
//  OKButton = gtk_button_new ();
//  gtk_widget_show (OKButton);
//  gtk_container_add (GTK_CONTAINER (hbuttonbox1), OKButton);
//  GTK_WIDGET_SET_FLAGS (OKButton, GTK_CAN_DEFAULT);
//
//  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);
//  gtk_widget_show (alignment1);
//  gtk_container_add (GTK_CONTAINER (OKButton), alignment1);
//
//  hbox3 = gtk_hbox_new (FALSE, 2);
//  gtk_widget_show (hbox3);
//  gtk_container_add (GTK_CONTAINER (alignment1), hbox3);
//
//  image2 = gtk_image_new_from_stock ("gtk-apply", GTK_ICON_SIZE_BUTTON);
//  gtk_widget_show (image2);
//  gtk_box_pack_start (GTK_BOX (hbox3), image2, FALSE, FALSE, 0);
//
//  label6 = gtk_label_new_with_mnemonic (_("OK"));
//  gtk_widget_show (label6);
//  gtk_box_pack_start (GTK_BOX (hbox3), label6, FALSE, FALSE, 0);
//
//  ResetParams = gtk_button_new ();
//  gtk_widget_show (ResetParams);
//  gtk_container_add (GTK_CONTAINER (hbuttonbox1), ResetParams);
//  GTK_WIDGET_SET_FLAGS (ResetParams, GTK_CAN_DEFAULT);
//
//  alignment2 = gtk_alignment_new (0.5, 0.5, 0, 0);
//  gtk_widget_show (alignment2);
//  gtk_container_add (GTK_CONTAINER (ResetParams), alignment2);
//
//  hbox4 = gtk_hbox_new (FALSE, 2);
//  gtk_widget_show (hbox4);
//  gtk_container_add (GTK_CONTAINER (alignment2), hbox4);
//
//  image3 = gtk_image_new_from_stock ("gtk-refresh", GTK_ICON_SIZE_BUTTON);
//  gtk_widget_show (image3);
//  gtk_box_pack_start (GTK_BOX (hbox4), image3, FALSE, FALSE, 0);
//
//  label7 = gtk_label_new_with_mnemonic (_("Reset"));
//  gtk_widget_show (label7);
//  gtk_box_pack_start (GTK_BOX (hbox4), label7, FALSE, FALSE, 0);
//
//  g_signal_connect ((gpointer) OKButton, "clicked",
//                    G_CALLBACK (on_OKButton_clicked),
//                    NULL);
//
//  /* Store pointers to all widgets, for use by lookup_widget(). */
//  GLADE_HOOKUP_OBJECT_NO_REF (AudioTriggerMeanPowerParams, AudioTriggerMeanPowerParams, "AudioTriggerMeanPowerParams");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, vbox1, "vbox1");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, image1, "image1");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hseparator1, "hseparator1");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, PrecisionLabel, "PrecisionLabel");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hscale1, "hscale1");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hseparator2, "hseparator2");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, SeuilLabel, "SeuilLabel");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hbox1, "hbox1");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, MaxLabel, "MaxLabel");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hscale2, "hscale2");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hbox2, "hbox2");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, MinLabel, "MinLabel");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hscale3, "hscale3");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hseparator3, "hseparator3");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hbuttonbox1, "hbuttonbox1");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, OKButton, "OKButton");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, alignment1, "alignment1");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hbox3, "hbox3");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, image2, "image2");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, label6, "label6");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, ResetParams, "ResetParams");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, alignment2, "alignment2");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, hbox4, "hbox4");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, image3, "image3");
//  GLADE_HOOKUP_OBJECT (AudioTriggerMeanPowerParams, label7, "label7");
//
//  return AudioTriggerMeanPowerParams;
//}
//
//void gui_audio_trigger(){
//   GtkWidget *AudioTriggerMeanPowerParams;
//
//   AudioTriggerMeanPowerParams = create_AudioTriggerMeanPowerParams ();
//   gtk_widget_show (AudioTriggerMeanPowerParams);
//
//   gtk_main ();
//   return 0;
//}

void gui_init(int argc,char *argv[]){
  #ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
  #endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  //gtk_add_pixmap_directory ("../img");
}
