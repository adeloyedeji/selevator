#ifndef __SE_DISPATCH_H__
#define __SE_DISPATCH_H__

#if defined(__cplusplus)
extern "C" {
#endif

enum dispatch_service_state {
    DISPATCH_STATE_IDLE = 0,
    DISPATCH_STATE_INIT,
    DISPATCH_STATE_RUNNING,
    DISPATCH_STATE_ERROR,
    DISPATCH_STATE_CLEANUP,
    DISPATCH_STATE_DOWN
};

enum dispatch_event_type {
    DISPATCH_EVENT_STARTING_UP = 0,
    DISPATCH_EVENT_SHUTTING_DOWN,
    DISPATCH_EVENT_CONSOLE_EVENT,
    DISPATCH_EVENT_SERVICE_REQUEST
};

struct dispatch_service {
    int max_threads;
    void (*thread_pool_worker_fn)(gpointer d, gpointer u_data);
    enum dispatch_service_state state;
};

struct dispatch_message {
    uint8_t type;
    uint8_t len;
    unsigned char message[0];
};

struct dispatch_startup_message {
    int instance_count;
    guint (*hash_fn)(gconstpointer k);
    gboolean (*hash_match_fn)(gconstpointer a, gconstpointer b);
    void (*cleanup_fn)(gpointer data);
};

struct dispatch_shutdown_message {
    int shutdown;
};

#define DISPATCH_MESSAGE_PAYLOAD(m)         \
    (void*)(((struct dispatch_message*)(m))->message)

#define DISPATCH_MESSAGE_VALIDATE(m, s)                             \
    ({                                                              \
        int resp = 1;                                               \
        if (((m)->len != sizeof(s))) {                              \
            fprintf(stderr, "Invalid message: %s\n", __func__);     \
            resp = 0;                                               \
        }                                                           \
        resp;                                                       \
    })

void dispatch_init(void);
void dispatch_request(uint8_t floor);
void dispatch_shutdown(void);
void dispatch_print_all(void);

#if defined(__cplusplus)
}
#endif

#endif //__SE_DISPATCH_H__