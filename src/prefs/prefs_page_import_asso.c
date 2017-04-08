/* *******************************************************************************/
/*                                 GRISBI                                        */
/*              Programme de gestion financière personnelle                      */
/*                              license : GPLv2                                  */
/*                                                                               */
/*     Copyright (C)    2000-2008 Cédric Auger (cedric@grisbi.org)               */
/*                      2003-2008 Benjamin Drieu (bdrieu@april.org)              */
/*          2008-2017 Pierre Biava (grisbi@pierre.biava.name)                    */
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
#include "config.h"
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <glib/gstdio.h>
#include <glib/gi18n.h>

/*START_INCLUDE*/
#include "prefs_page_import_asso.h"
#include "gsb_file.h"
#include "structures.h"
#include "utils_prefs.h"
#include "erreur.h"

/*END_INCLUDE*/

/*START_EXTERN*/
/*END_EXTERN*/

typedef struct _PrefsPageImportAssoPrivate   PrefsPageImportAssoPrivate;

struct _PrefsPageImportAssoPrivate
{
	GtkWidget *			vbox_import_asso;

    GtkWidget *			checkbutton_;
	GtkWidget *			eventbox_;
    GtkWidget *         spinbutton_n;
    GtkWidget *         filechooserbutton_;

};

G_DEFINE_TYPE_WITH_PRIVATE (PrefsPageImportAsso, prefs_page_import_asso, GTK_TYPE_BOX)

/******************************************************************************/
/* Private functions                                                          */
/******************************************************************************/
/**
 * Création de la page de gestion des import_asso
 *
 * \param prefs
 *
 * \return
 */
static void prefs_page_import_asso_setup_import_asso_page (PrefsPageImportAsso *page)
{
	PrefsPageImportAssoPrivate *priv;

	devel_debug (NULL);

	priv = prefs_page_import_asso_get_instance_private (page);

    /* set the variables for account */
    //~ gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (priv->checkbutton_),
								  //~ conf.);
	/* set spinbutton value */
	//~ gtk_spin_button_set_value (GTK_SPIN_BUTTON (priv->spinbutton_),
							   //~ conf.);

    /* Connect signal */
    //~ g_signal_connect (priv->eventbox_,
					  //~ "button-press-event",
					  //~ G_CALLBACK (utils_prefs_page_eventbox_clicked),
					  //~ priv->checkbutton_);

    //~ g_signal_connect (priv->checkbutton_,
					  //~ "toggled",
					  //~ G_CALLBACK (utils_prefs_page_checkbutton_changed),
					  //~ &conf.);

    /* callback for spinbutton_ */
    //~ g_object_set_data (G_OBJECT (priv->spinbutton_),
                       //~ "button", priv->checkbutton_);
	//~ g_object_set_data (G_OBJECT (priv->checkbutton_),
                       //~ "spinbutton", priv->spinbutton_);

    //~ g_signal_connect (priv->spinbutton_,
					  //~ "value-changed",
					  //~ G_CALLBACK (utils_prefs_spinbutton_changed),
					  //~ &conf.);

    /* connect the signal for filechooserbutton_backup */
    //~ g_signal_connect (G_OBJECT (priv->filechooserbutton_backup),
                      //~ "selection-changed",
                      //~ G_CALLBACK (utils_prefs_page_dir_chosen),
                      //~ "backup_path");
}

/******************************************************************************/
/* Fonctions propres à l'initialisation des fenêtres                          */
/******************************************************************************/
static void prefs_page_import_asso_init (PrefsPageImportAsso *page)
{
	gtk_widget_init_template (GTK_WIDGET (page));

	prefs_page_import_asso_setup_import_asso_page (page);
}

static void prefs_page_import_asso_dispose (GObject *object)
{
	G_OBJECT_CLASS (prefs_page_import_asso_parent_class)->dispose (object);
}

static void prefs_page_import_asso_class_init (PrefsPageImportAssoClass *klass)
{
	G_OBJECT_CLASS (klass)->dispose = prefs_page_import_asso_dispose;

	gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass),
												 "/org/gtk/grisbi/ui/prefs_pages_import_asso.ui");

	//~ gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), PrefsPageImportAsso, vbox_import_asso);
	//~ gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), PrefsPageImportAsso, checkbutton_);
	//~ gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), PrefsPageImportAsso, eventbox_);
	//~ gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), PrefsPageImportAsso, spinbutton_);
	//~ gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), PrefsPageImportAsso, filechooserbutton_);
}

/******************************************************************************/
/* Public functions                                                           */
/******************************************************************************/
PrefsPageImportAsso * prefs_page_import_asso_new (GrisbiPrefs *win)
{
  return g_object_new (PREFS_PAGE_IMPORT_ASSO_TYPE, NULL);
}

/**
 *
 *
 * \param
 *
 * \return
 **/
/* Local Variables: */
/* c-basic-offset: 4 */
/* End: */

