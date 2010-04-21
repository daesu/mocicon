//MocIcon. see README for help.
//compile with gcc -Wall -g mocicon.c -o mocicon `pkg-config --cflags --libs gtk+-2.0`
#include <gtk/gtk.h> 

//static char *notify = "bash -c 'notify-send -t 2000 \"$(mocp -Q %artist)\" \"$(mocp -Q %song)\" -i gtk-cdrom'";
static gchar *temp;
//static char *notify = "bash -c echo \"$(mocp -Q %artist)$(mocp -Q %song)\" ";
GtkWidget *menu, *quit_item, *launch_item, *play_item, *stop_item, *start_item, *next_item, *prev_item; 




/*char * query() {
    
    gchar *stdoutput=NULL;
    
		g_spawn_command_line_sync("mocp -Q %artist", &stdoutput, NULL, NULL, NULL);
		temp = g_strconcat(stdoutput, NULL);
		g_spawn_command_line_sync("mocp -Q %song", &stdoutput, NULL, NULL, NULL);
		temp = g_strconcat(temp, " ", stdoutput, NULL);
		g_free(stdoutput);
		return (char *)temp;
}*/
static void send( GtkMenuItem *item, gpointer data) {


		switch(GPOINTER_TO_INT(data)) {
			case 0:
				g_spawn_command_line_async("mocp --play", NULL);
					break;
			case 1:
				g_spawn_command_line_async("mocp --toggle-pause", NULL);
					break;
			case 2:
				g_spawn_command_line_async("mocp --exit", NULL);
					break;
			case 3:
				g_spawn_command_line_async("mocp --next", NULL);
					break;
			case 4:
				g_spawn_command_line_async("mocp --previous", NULL);
					break;
			case 5: 				
			 g_spawn_command_line_async(notify, NULL);			
					break;
			case 6:
				g_spawn_command_line_async("xterm -C mocp", NULL);
					break;
			case 7:

//	    	dialog = gtk_file_chooser_dialog_new( "Select file",  NULL, GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_SAVE, 1, GTK_STOCK_CANCEL, 0, NULL ); 
  //          gtk_dialog_run( GTK_DIALOG( dialog ));

    //    playlist = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( dialog ) ); 
		//g_spawn_command_line_sync("mocp -c",  NULL, NULL, NULL, NULL);
		//g_spawn_command_line_sync(g_strconcat("mocp -a ", playlist),  NULL, NULL, NULL, NULL);
		//g_spawn_command_line_sync("mocp -p",  NULL, NULL, NULL, NULL);        

				break;
		default:
				break;
		}
		g_free(temp);
}

gboolean button_press_cb(GtkStatusIcon *icon, GdkEventButton *ev, gpointer user_data) 
{  
	// I am not entirely sure what to do, double click implementation is possible. say double  click to get info. single click just pause/plays. but it will STILL register the first click, so it would pause and then give info.
    { 
    if(ev->button == 3)
         gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, ev->button, ev->time); 
    } 
      if(ev->button == 2) {
	send(NULL, GINT_TO_POINTER( 5 ));
} 
    if(ev->button == 1)  { 
		send(NULL, GINT_TO_POINTER( 1 ));
			}	
	return FALSE;
} 

static void setup() {
	GtkStatusIcon *icon; 
	gchar *querychar=NULL;
	icon = gtk_status_icon_new_from_stock(GTK_STOCK_MEDIA_PLAY); 
	g_signal_connect(icon,"button-press-event", G_CALLBACK(button_press_cb), NULL); 
	//tooltip

	
	
	menu = gtk_menu_new(); 
		// Create Items
	 start_item = gtk_image_menu_item_new_with_label("Start Server");
	 stop_item  = gtk_image_menu_item_new_with_label("Stop Server");
	 next_item  = gtk_image_menu_item_new_with_label("Next");
	 prev_item  = gtk_image_menu_item_new_with_label("Previous");
	 play_item  = gtk_image_menu_item_new_with_label("Play/Pause");
	 launch_item = gtk_image_menu_item_new_with_label("Launch Moc");
	 quit_item  = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	// Comment this section out if you don't want icons. sorry about the quit, it's stock.
 	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(start_item), gtk_image_new_from_stock(GTK_STOCK_YES, GTK_ICON_SIZE_MENU));
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(stop_item), gtk_image_new_from_stock(GTK_STOCK_NO, GTK_ICON_SIZE_MENU));
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(next_item), gtk_image_new_from_stock(GTK_STOCK_MEDIA_FORWARD, GTK_ICON_SIZE_MENU));
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(prev_item), gtk_image_new_from_stock(GTK_STOCK_MEDIA_REWIND, GTK_ICON_SIZE_MENU));
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(play_item), gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_MENU));
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(launch_item), gtk_image_new_from_stock(GTK_STOCK_EXECUTE, GTK_ICON_SIZE_MENU));
 	g_signal_connect(G_OBJECT(quit_item), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(play_item), "activate", G_CALLBACK(send), GINT_TO_POINTER( 1 ));
	g_signal_connect(G_OBJECT(start_item),"activate", G_CALLBACK(send), GINT_TO_POINTER( 0 ));
	g_signal_connect(G_OBJECT(stop_item), "activate", G_CALLBACK(send), GINT_TO_POINTER( 2 ));
	g_signal_connect(G_OBJECT(next_item), "activate", G_CALLBACK(send), GINT_TO_POINTER( 3 ));
	g_signal_connect(G_OBJECT(prev_item), "activate", G_CALLBACK(send), GINT_TO_POINTER( 4 ));
	g_signal_connect(G_OBJECT(launch_item), "activate", G_CALLBACK(send), GINT_TO_POINTER( 6 ));
        
	 gtk_menu_shell_append(GTK_MENU_SHELL(menu), stop_item); 
	 gtk_menu_shell_append(GTK_MENU_SHELL(menu), start_item); 
  	 gtk_menu_shell_append(GTK_MENU_SHELL(menu), play_item); 
	 gtk_menu_shell_append(GTK_MENU_SHELL(menu), next_item); 	
	 gtk_menu_shell_append(GTK_MENU_SHELL(menu), prev_item); 
	 gtk_menu_shell_append(GTK_MENU_SHELL(menu), launch_item); 	
	 gtk_menu_shell_append(GTK_MENU_SHELL(menu), quit_item); 
 	 // show widgets
        gtk_widget_show_all(menu);
};
 

gint main(gint argc, gchar **argv) 
{ 
    gtk_init(&argc, &argv); 
    setup();
    gtk_main(); 

    return 0; 
}
