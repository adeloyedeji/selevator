#include "precomp.h"

#define MAX_THREADS 4

static GHashTable* elevator_db = NULL;
static GThreadPool* worker_pool = NULL;
static struct dispatch_service* dispatch = NULL;

static void 
init_db(struct dispatch_startup_message* ds_msg)
{
    dispatch->state = DISPATCH_STATE_INIT;

    elevator_db = g_hash_table_new_full(
        ds_msg->hash_fn, 
        ds_msg->hash_match_fn, 
        ds_msg->cleanup_fn, 
        NULL);

    for(int i = 0; i < ds_msg->instance_count; ++i)
    {
        gpointer key = (gpointer) elevator_init();
        g_hash_table_add(elevator_db, key);
    }

    dispatch->state = DISPATCH_STATE_RUNNING;
}

static void handle_startup_request(struct dispatch_message* d_msg)
{
    if (DISPATCH_MESSAGE_VALIDATE(d_msg, struct dispatch_startup_message))
        init_db(DISPATCH_MESSAGE_PAYLOAD(d_msg));
}

static void handle_shutdown_request(struct dispatch_message* d_msg)
{
    if (DISPATCH_MESSAGE_VALIDATE(d_msg, struct dispatch_shutdown_message))
        dispatch_shutdown();
}

static void handle_generic_event(struct dispatch_message* d_msg)
{
    const gchar* domain = "G_GENERIC_EVENT";
    g_log(
        domain,
        G_LOG_LEVEL_INFO,
        "This is a generic event. To be handled later."
    );
}

static void 
worker_pool_fn(gpointer event, gpointer u_data)
{
    struct dispatch_message* d_msg = (struct dispatch_message*)event;
    
    switch(d_msg->type)
    {
        case DISPATCH_EVENT_STARTING_UP:
            handle_startup_request(d_msg);
            break;
        case DISPATCH_EVENT_SHUTTING_DOWN:
            handle_shutdown_request(d_msg);
            break;
        case DISPATCH_EVENT_CONSOLE_EVENT:
            handle_generic_event(d_msg);
            break;
        case DISPATCH_EVENT_SERVICE_REQUEST:
            handle_generic_event(d_msg);
            break;
        default:
            handle_generic_event(d_msg);
            break;
    }

    g_free(d_msg);
}

void
dispatch_init(void)
{
    GError* err = NULL;

    dispatch = (struct dispatch_service*)g_try_malloc0(sizeof(struct dispatch_service));
    if (!dispatch)
    {
        // const gchar* domain_char = "G_MEMORY_ERROR";
        // GQuark domain = g_quark_from_string(domain_char);
        g_error("g_try_malloc0(): failed to allocate memory for struct dispatch_service");
        // err = g_error_new(
        //     domain, 
        //     -ENOMEM, 
        //     "g_try_malloc0(): failed to allocate memory for struct dispatch_service");
        // return;
    }

    dispatch->max_threads = MAX_THREADS;
    dispatch->thread_pool_worker_fn = worker_pool_fn;
    dispatch->state = DISPATCH_STATE_IDLE;

    worker_pool = g_thread_pool_new(
                    dispatch->thread_pool_worker_fn,
                    dispatch,
                    dispatch->max_threads,
                    0,
                    &err);
    
    if (err != NULL)
    {
        fprintf(stderr, "Unable to create worker thread pool. Error: %s\n", err->message);
        goto quit_init;
    }

    struct dispatch_startup_message* startup_msg = (struct dispatch_startup_message*)
                                                        g_try_malloc0(sizeof(struct dispatch_startup_message));
    if (startup_msg)
    {
        startup_msg->instance_count = SELEVATOR_ELEVATOR_INSTANCE;
        startup_msg->hash_fn = elevator_hash;
        startup_msg->hash_match_fn = elevator_hash_equal;
        startup_msg->cleanup_fn = elevator_cleanup;

        struct dispatch_message* d_msg = (struct dispatch_message*)g_try_malloc0(sizeof(struct dispatch_message));
        if (!d_msg)
        {
            g_free(startup_msg);
            goto quit_init;
        }

        d_msg->type = DISPATCH_EVENT_STARTING_UP;
        d_msg->len = sizeof(struct dispatch_message);
        memcpy(DISPATCH_MESSAGE_PAYLOAD(d_msg), (void*)startup_msg, sizeof(struct dispatch_startup_message));
    
        g_thread_pool_push(worker_pool, d_msg, &err);

        if (err != NULL)
        {
            fprintf(stderr, "Unable to initialize dispatch service database. Error: %s\n", err->message);
            g_free(startup_msg);
            g_error_free(err);
            return;
        }

        const gchar* init_domain = "G_INIT_EVENT";
        g_log(
            init_domain,
            G_LOG_LEVEL_INFO,
            "Dispatch service successfully started ..."
        );

        return;
    }

quit_init:
    g_free(dispatch);
    g_error_free(err);
}

void
dispatch_request(uint8_t floor)
{

}

void
dispatch_shutdown(void)
{
    dispatch->state = DISPATCH_STATE_CLEANUP;
    
    g_hash_table_remove_all(elevator_db);
    g_thread_pool_free(worker_pool, 1, 1);

    dispatch->state = DISPATCH_STATE_DOWN;
    g_free(dispatch);
}

void
dispatch_print_all(void)
{
    g_hash_table_foreach(elevator_db, elevator_display, NULL);
}