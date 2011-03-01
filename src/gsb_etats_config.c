/* *******************************************************************************/
/*                                 GRISBI                                        */
/*              Programme de gestion financière personnelle                      */
/*                              license : GPLv2                                  */
/*                                                                               */
/*     Copyright (C)    2000-2008 Cédric Auger (cedric@grisbi.org)               */
/*                      2003-2008 Benjamin Drieu (bdrieu@april.org)              */
/*          2008-2010 Pierre Biava (grisbi@pierre.biava.name)                    */
/*          http://www.grisbi.org                                                */
/*                                                                               */
/*     This program is free software; you can redistribute it and/or modify      */
/*     it under the terms of the GNU General Public License as published by      */
/*     the Free Software Foundation; either version 2 of the License, or         */
/*     (at your option) any later version.                                       */
/*                                                                               */
/*     This program is distributed in the hope that it will be useful,           */
/*     but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*     GNU General Public License for more details.                              */
/*                                                                               */
/*     You should have received a copy of the GNU General Public License         */
/*     along with this program; if not, write to the Free Software               */
/*     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                               */
/* *******************************************************************************/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib/gi18n.h>
#include <gtk/gtk.h>


/*START_INCLUDE*/
#include "gsb_etats_config.h"
#include "etats_config.h"
#include "fenetre_principale.h"
#include "navigation.h"

/*
#include "etats_calculs.h"
#include "tiers_onglet.h"
#include "utils.h"
#include "dialog.h"
#include "gsb_calendar_entry.h"
#include "gsb_currency.h"
#include "gsb_data_account.h"
#include "gsb_data_budget.h"
#include "gsb_data_category.h"
#include "gsb_data_fyear.h"
#include "gsb_data_payee.h"
#include "gsb_data_payment.h"
#include "gsb_data_report_amout_comparison.h"
#include "gsb_data_report.h"
#include "gsb_data_report_text_comparison.h"
#include "utils_dates.h"
#include "gsb_real.h"
#include "traitement_variables.h"
#include "utils_str.h"
#include "structures.h"
*/
#include "erreur.h"
/*END_INCLUDE*/


/*START_STATIC*/
static gchar *gsb_etats_config_get_full_path ( const gchar *name );
static GtkWidget *gsb_etats_config_get_report_tree_view ( GtkWidget *paned );
/*END_STATIC*/


/*START_EXTERN*/
extern GtkWidget *notebook_config_etat;
extern GtkWidget *notebook_general;
extern GtkWidget *window;
/*END_EXTERN*/


static GtkTreeStore *report_tree_model = NULL;
static GtkWidget *report_tree_view;


/**
 * affiche la fenetre de personnalisation
 *
 *
 *
 * */
void gsb_etats_config_personnalisation_etat ( void )
{
    GtkBuilder *etat_config_builder = NULL;
    GtkWidget *dialog;
    GtkWidget *paned;
    gchar *filename;
    gint current_report_number;
/*     gint page = 0;  */
    GError *error = NULL;

    /* Creation d'un nouveau GtkBuilder */
    etat_config_builder = gtk_builder_new ( );

    if ( etat_config_builder == NULL )
        return;

    /* Chargement du XML dans etat_config_builder */
    filename = gsb_etats_config_get_full_path ( "gsb_etats_config.ui" );
    printf ("filename = %s\n", filename);

    gtk_builder_add_from_file ( etat_config_builder, filename, &error );
    if ( error != NULL )
    {
        g_free ( filename );
        g_error_free ( error );

        return;
    }

    if ( !( current_report_number = gsb_gui_navigation_get_current_report ( ) ) )
        return;

    if ( gtk_notebook_get_current_page ( GTK_NOTEBOOK ( notebook_general)) != GSB_REPORTS_PAGE )
        gtk_notebook_set_current_page ( GTK_NOTEBOOK ( notebook_general), GSB_REPORTS_PAGE );

    /* Recuparation d'un pointeur sur la fenetre. */
    dialog = GTK_WIDGET ( gtk_builder_get_object ( etat_config_builder, "config_etats_dialog" ) );
    gtk_window_set_transient_for ( GTK_WINDOW ( dialog ), GTK_WINDOW ( window ) );

    g_free ( filename );

    /* Recuparation d'un pointeur sur le gtk_paned. */
    paned = GTK_WIDGET ( gtk_builder_get_object ( etat_config_builder, "dialog_hpaned" ) );

    if ( paned == NULL )
    {
        printf ("erreur paned is NULL\n");
        return;
    }


    /* Recuparation du tree_view. */
    report_tree_view = gsb_etats_config_get_report_tree_view ( paned );





    gtk_widget_show_all ( dialog );

    switch ( gtk_dialog_run ( GTK_DIALOG ( dialog ) ) )
    {
        case GTK_RESPONSE_OK:
            break;

        default:
            break;
    }

    gtk_widget_destroy ( dialog );
}


/**
 * obtient le fichier de l'interface graphique
 *
 *
 *
 * */
gchar *gsb_etats_config_get_full_path ( const gchar *name )
{
    gchar *filename;

#ifdef GRISBI_RUN_IN_SOURCE_TREE
    filename = g_build_filename ( PACKAGE_SOURCE_DIR, "ui", name, NULL );
/*     if ( g_file_test ( filename, G_FILE_TEST_EXISTS ) == FALSE )
 * 	{
 * 		g_free (filename);
 */
		/* Try the local file */
/* 		filename = g_build_filename ( DATADIR, "grisbi", name, NULL );
 * 
 * 		if ( g_file_test ( filename, G_FILE_TEST_EXISTS ) == FALSE )
 * 		{
 * 			g_free ( filename );
 * 
 * 			return NULL;
 * 		}
 * 	}
 */

/* #else
 * 	filename = g_build_filename (DATADIR, "grisbi", name, NULL);
 */
#endif
    return filename;
}


/**
 * retourne le tree_view pour la configuration des états
 *
 *
 *
 * */
GtkWidget *gsb_etats_config_get_report_tree_view ( GtkWidget *paned )
{
    GtkWidget *sw;
    GtkWidget *tree_view;
    GtkTreeViewColumn *column;
    GtkCellRenderer *cell;
    GtkTreeSelection *selection ;

    /* Create model */
    report_tree_model = gtk_tree_store_new ( REPORT_TREE_NUM_COLUMNS,
                        G_TYPE_STRING,
                        G_TYPE_INT,
                        G_TYPE_INT,
                        G_TYPE_INT );

    /* Create container + TreeView */
    sw = gtk_scrolled_window_new ( NULL, NULL );
    gtk_scrolled_window_set_shadow_type ( GTK_SCROLLED_WINDOW ( sw ), GTK_SHADOW_IN );
    gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( sw ),
                        GTK_POLICY_NEVER,
                        GTK_POLICY_AUTOMATIC );

    tree_view = gtk_tree_view_new_with_model  ( GTK_TREE_MODEL ( report_tree_model ) );
    g_object_unref ( G_OBJECT ( report_tree_model ) );

    /* Make column */
    cell = gtk_cell_renderer_text_new ( );
    column = gtk_tree_view_column_new_with_attributes ( "Categories",
                        cell,
                        "text", REPORT_TREE_TEXT_COLUMN,
                        "weight", REPORT_TREE_BOLD_COLUMN,
                        "style", REPORT_TREE_ITALIC_COLUMN,
                        NULL );
    gtk_tree_view_append_column ( GTK_TREE_VIEW ( tree_view ),
                        GTK_TREE_VIEW_COLUMN ( column ) );
    gtk_tree_view_set_headers_visible ( GTK_TREE_VIEW ( tree_view ), FALSE );

    /* Handle select */
    selection = gtk_tree_view_get_selection ( GTK_TREE_VIEW ( tree_view ) );
/*     g_signal_connect ( selection,
 *                         "changed",
 *                         G_CALLBACK ( report_tree_view_selection_changed ),
 *                         report_tree_model);
 */

    /* Choose which entries will be selectable */
/*     gtk_tree_selection_set_select_function ( selection, report_tree_selectable_func, NULL, NULL );  */

    /* Put the tree in the scroll */
    gtk_container_add ( GTK_CONTAINER ( sw ), tree_view );

    /* expand all rows after the treeview widget has been realized */
    g_signal_connect ( tree_view,
                        "realize",
                        G_CALLBACK ( gtk_tree_view_expand_all ),
                        NULL );

    gtk_paned_add1 ( GTK_PANED ( paned ), sw ) ;

    return tree_view;
}


/* Local Variables: */
/* c-basic-offset: 4 */
/* End: */