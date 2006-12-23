#ifndef _GSB_PAYMENT_METHOD_CONFIG_H
#define _GSB_PAYMENT_METHOD_CONFIG_H (1)

/** Columns for payment methods tree */
enum payment_methods_columns {
    PAYMENT_METHODS_NAME_COLUMN = 0,
    PAYMENT_METHODS_NUMBERING_COLUMN,
    PAYMENT_METHODS_DEFAULT_COLUMN,
    PAYMENT_METHODS_TYPE_COLUMN,
    PAYMENT_METHODS_VISIBLE_COLUMN,
    PAYMENT_METHODS_ACTIVABLE_COLUMN,
    PAYMENT_METHODS_NUMBER_COLUMN,
    PAYMENT_METHODS_ACCOUNT_COLUMN,
    NUM_PAYMENT_METHODS_COLUMNS,
};


/* START_INCLUDE_H */
#include "gsb_payment_method_config.h"
/* END_INCLUDE_H */

/* START_DECLARATION */
GtkWidget *gsb_payment_method_config_create ( void );
/* END_DECLARATION */
#endif
