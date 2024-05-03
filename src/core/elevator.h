#ifndef __SE_ELEVATOR_H__
#define __SE_ELEVATOR_H__

#if defined(__cplusplus)
extern "C" {
#endif

struct elevator;

struct elevator* elevator_init(void);
void elevator_enable(GHashTable* db, struct elevator* el);
void elevator_disable(GHashTable* db, struct elevator* el);
void elevator_destroy(struct elevator* el);
void elevator_print(struct elevator* el);
guint elevator_hash(gconstpointer k);
gboolean elevator_hash_equal(gconstpointer a, gconstpointer b);
void elevator_cleanup(gpointer data);
void elevator_display(gpointer key, gpointer value, gpointer user_data);

#if defined(__cplusplus)
}
#endif 


#endif //__SE_ELEVATOR_H__