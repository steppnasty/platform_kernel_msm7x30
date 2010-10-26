#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list_sort.h>
#include <linux/slab.h>
#include <linux/list.h>

#define MAX_LIST_LENGTH_BITS 20

/*
 * Returns a list organized in an intermediate format suited
 * to chaining of merge() calls: null-terminated, no reserved or
 * sentinel head node, "prev" links not maintained.
 */
static struct list_head *merge(void *priv,
				int (*cmp)(void *priv, struct list_head *a,
					struct list_head *b),
				struct list_head *a, struct list_head *b)
{
	struct list_head head, *tail = &head;

	while (a && b) {
		/* if equal, take 'a' -- important for sort stability */
		if ((*cmp)(priv, a, b) <= 0) {
			tail->next = a;
			a = a->next;
		} else {
			tail->next = b;
			b = b->next;
		}
		tail = tail->next;
	}
	tail->next = a?:b;
	return head.next;
}

/*
 * Combine final list merge with restoration of standard doubly-linked
 * list structure.  This approach duplicates code from merge(), but
 * runs faster than the tidier alternatives of either a separate final
 * prev-link restoration pass, or maintaining the prev links
 * throughout.
 */
static void merge_and_restore_back_links(void *priv,
				int (*cmp)(void *priv, struct list_head *a,
					struct list_head *b),
				struct list_head *head,
				struct list_head *a, struct list_head *b)
{
	struct list_head *tail = head;

	while (a && b) {
		/* if equal, take 'a' -- important for sort stability */
		if ((*cmp)(priv, a, b) <= 0) {
			tail->next = a;
			a->prev = tail;
			a = a->next;
		} else {
			tail->next = b;
			b->prev = tail;
			b = b->next;
		}
		tail = tail->next;
	}
	tail->next = a ? : b;

	do {
		/*
		 * In worst cases this loop may run many iterations.
		 * Continue callbacks to the client even though no
		 * element comparison is needed, so the client's cmp()
		 * routine can invoke cond_resched() periodically.
		 */
		(*cmp)(priv, tail->next, tail->next);

		tail->next->prev = tail;
		tail = tail->next;
	} while (tail->next);

	tail->next = head;
	head->prev = tail;
}

/**
 * list_sort - sort a list
 * @priv: private data, opaque to list_sort(), passed to @cmp
 * @head: the list to sort
 * @cmp: the elements comparison function
 *
 * This function implements "merge sort", which has O(nlog(n))
 * complexity.
 *
 * The comparison function @cmp must return a negative value if @a
 * should sort before @b, and a positive value if @a should sort after
 * @b. If @a and @b are equivalent, and their original relative
 * ordering is to be preserved, @cmp must return 0.
 */
void list_sort(void *priv, struct list_head *head,
		int (*cmp)(void *priv, struct list_head *a,
			struct list_head *b))
{
	struct list_head *part[MAX_LIST_LENGTH_BITS+1]; /* sorted partial lists
						-- last slot is a sentinel */
	int lev;  /* index into part[] */
	int max_lev = 0;
	struct list_head *list;

	if (list_empty(head))
		return;

	memset(part, 0, sizeof(part));

	head->prev->next = NULL;
	list = head->next;

	while (list) {
		struct list_head *cur = list;
		list = list->next;
		cur->next = NULL;

		for (lev = 0; part[lev]; lev++) {
			cur = merge(priv, cmp, part[lev], cur);
			part[lev] = NULL;
		}
		if (lev > max_lev) {
			if (unlikely(lev >= ARRAY_SIZE(part)-1)) {
				printk_once(KERN_DEBUG "list passed to"
					" list_sort() too long for"
					" efficiency\n");
				lev--;
			}
			max_lev = lev;
		}
		part[lev] = cur;
	}

	for (lev = 0; lev < max_lev; lev++)
		if (part[lev])
			list = merge(priv, cmp, part[lev], list);

	merge_and_restore_back_links(priv, cmp, head, part[max_lev], list);
}
EXPORT_SYMBOL(list_sort);

#ifdef CONFIG_TEST_LIST_SORT

#include <linux/random.h>

struct debug_el {
	struct list_head list;
	int value;
	unsigned serial;
};

static int cmp(void *priv, struct list_head *a, struct list_head *b)
{
	return container_of(a, struct debug_el, list)->value
	     - container_of(b, struct debug_el, list)->value;
}

/*
 * The pattern of set bits in the list length determines which cases
 * are hit in list_sort().
 */
#define TEST_LIST_LEN (512+128+2) /* not including head */

static int __init list_sort_test(void)
{
	int i, count = 1, err = -EINVAL;
	struct debug_el *el;
	struct list_head *cur, *tmp;
	LIST_HEAD(head);

	printk(KERN_DEBUG "list_sort_test: start testing list_sort()\n");

	for (i = 0; i < TEST_LIST_LEN; i++) {
		el = kmalloc(sizeof(*el), GFP_KERNEL);
		if (!el) {
			printk(KERN_ERR "list_sort_test: error: cannot "
					"allocate memory\n");
			goto exit;
		}
		 /* force some equivalencies */
		el->value = random32() % (TEST_LIST_LEN/3);
		el->serial = i;
		list_add_tail(&el->list, &head);
	}

	list_sort(NULL, &head, cmp);

	for (cur = head.next; cur->next != &head; cur = cur->next) {
		struct debug_el *el1;
		int cmp_result;

		if (cur->next->prev != cur) {
			printk(KERN_ERR "list_sort_test: error: list is "
					"corrupted\n");
			goto exit;
		}

		cmp_result = cmp(NULL, cur, cur->next);
		if (cmp_result > 0) {
			printk(KERN_ERR "list_sort_test: error: list is not "
					"sorted\n");
			goto exit;
		}

		el = container_of(cur, struct debug_el, list);
		el1 = container_of(cur->next, struct debug_el, list);
		if (cmp_result == 0 && el->serial >= el1->serial) {
			printk(KERN_ERR "list_sort_test: error: order of "
					"equivalent elements not preserved\n");
			goto exit;
		}
		count++;
	}

	if (count != TEST_LIST_LEN) {
		printk(KERN_ERR "list_sort_test: error: bad list length %d",
				count);
		goto exit;
	}

	err = 0;
exit:
	list_for_each_safe(cur, tmp, &head) {
		list_del(cur);
		kfree(container_of(cur, struct debug_el, list));
	}
	return err;
}
module_init(list_sort_test);
#endif /* CONFIG_TEST_LIST_SORT */
