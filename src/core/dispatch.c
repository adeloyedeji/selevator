#include "precomp.h"

static GHashTable* elevator_db = NULL;

void
dispatch_init(void)
{
    elevator_db = g_hash_table_new_full(elevator_hash, elevator_hash_equal, elevator_cleanup, NULL);

    for(int i = 0; i < SELEVATOR_ELEVATOR_INSTANCE; ++i)
    {
        gpointer key = (gpointer) elevator_init();
        g_hash_table_add(elevator_db, key);
    }
}

void
dispatch_request(uint8_t floor)
{

}

void
dispatch_shutdown(void)
{
    g_hash_table_remove_all(elevator_db);
}

void
dispatch_print_all(void)
{
    g_hash_table_foreach(elevator_db, elevator_display, NULL);
}