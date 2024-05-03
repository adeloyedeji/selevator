#include "precomp.h"

#define MAX_WEIGHT              2000
#define MAX_FLOOR_NUM           15
#define MAX_SECS_OPEN           30
#define COUNTDOWN_UPPER_LIMIT   5

typedef int weight;
typedef int floor_num;

enum elevator_state {
    ELEVATOR_STATE_IDLE = 0,
    ELEVATOR_STATE_RUNNING,
    ELEVATOR_STATE_WAITING,
    ELEVATOR_STATE_DISABLED
};

struct elevator {
    weight max_weight;
    floor_num floor;
    floor_num destination_floor;
    floor_num max_floor_num;
    gchar* id;
    guint hash_id;
    uint8_t maximum_seconds_open;
    uint8_t countdown_upper_limit;
    enum elevator_state state;
};

char*
elevator_state_to_string(enum elevator_state st)
{
    switch(st)
    {
        case ELEVATOR_STATE_IDLE: return "ELEVATOR_STATE_IDLE";
        case ELEVATOR_STATE_RUNNING: return "ELEVATOR_STATE_RUNNING";
        case ELEVATOR_STATE_WAITING: return "ELEVATOR_STATE_WAITING";
        case ELEVATOR_STATE_DISABLED: return "ELEVATOR_STATE_DISABLED";
        default: return "ELEVATOR_STATE_UNKNOWN";
    }
}

struct elevator*
elevator_init(void)
{
    struct elevator* el = NULL;
    el = (struct elevator*)g_try_malloc0(sizeof(struct elevator));
    if (el)
    {
        el->state = ELEVATOR_STATE_IDLE;
        el->floor = 0;
        el->destination_floor = 0;
        el->max_weight = (weight)MAX_WEIGHT;
        el->max_floor_num = MAX_FLOOR_NUM;
        el->maximum_seconds_open = MAX_SECS_OPEN;
        el->countdown_upper_limit = COUNTDOWN_UPPER_LIMIT;
        el->id = g_uuid_string_random();
        el->hash_id = g_random_int();
    }

    return el;
}

void
elevator_disable(GHashTable* db, struct elevator* el)
{
    if (g_hash_table_contains(db, el))
    {
        el->state = ELEVATOR_STATE_DISABLED;
    }
}

void
elevator_enable(GHashTable* db, struct elevator* el)
{
    if (g_hash_table_contains(db, el))
    {
        el->state = ELEVATOR_STATE_IDLE;
    }
}

void elevator_print(struct elevator* el)
{
#if DEBUG_MODE
    printf("\n"
        "Elevator ID: %s\n"
        "Hash ID: %d\n"
        "Max weight: %dkg\n"
        "State: %s\n"
        "Current floor: %d\n"
        "Maximum floor allowed: %d\n"
        "Destination floor: %d\n"
        "Maximum doors can stay open: %dsecs.\n",
        (char*)el->id,
        el->hash_id,
        el->max_weight,
        elevator_state_to_string(el->state),
        el->floor,
        el->max_floor_num,
        el->destination_floor,
        el->maximum_seconds_open
    );
#endif //_DEBUG_MODE
}

void
elevator_destroy(struct elevator* el)
{
    g_free(el->id);
    g_free(el);
}

guint
elevator_hash(gconstpointer k)
{
    const struct elevator *key = (const struct elevator*)k;

    guint32 hash;
    hash = (guint32) (key->hash_id&0xffffffff);

    return hash;
}

gboolean
elevator_hash_equal(gconstpointer a, gconstpointer b)
{
    const struct elevator *key1 = (const struct elevator*)a;
    const struct elevator *key2 = (const struct elevator*)b;

    return key1->hash_id == key2->hash_id;
}

void
elevator_cleanup(gpointer data)
{
    struct elevator* el = (struct elevator*)data;
    elevator_destroy(el);
}

void
elevator_display(gpointer key, gpointer value, gpointer user_data)
{
    struct elevator* el = (struct elevator*)key;
    elevator_print(el);
}