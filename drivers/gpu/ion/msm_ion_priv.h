/*
 * drivers/gpu/ion/ion_priv.h
 *
 * Copyright (C) 2011 Google, Inc.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _MSM_ION_PRIV_H
#define _MSM_ION_PRIV_H

#include <linux/ion.h>
#include <linux/rbtree.h>

/**
 * struct mem_map_data - represents information about the memory map for a heap
 * @node:		rb node used to store in the tree of mem_map_data
 * @addr:		start address of memory region.
 * @addr:		end address of memory region.
 * @size:		size of memory region
 * @client_name:	name of the client who owns this buffer.
 *
 */
struct mem_map_data {
	struct rb_node node;
	ion_phys_addr_t addr;
	ion_phys_addr_t addr_end;
	unsigned long size;
	const char *client_name;
};

#define ION_CP_ALLOCATE_FAIL -1
#define ION_RESERVED_ALLOCATE_FAIL -1

/**
 * ion_do_cache_op - do cache operations.
 *
 * @client - pointer to ION client.
 * @handle - pointer to buffer handle.
 * @uaddr -  virtual address to operate on.
 * @offset - offset from physical address.
 * @len - Length of data to do cache operation on.
 * @cmd - Cache operation to perform:
 *		ION_IOC_CLEAN_CACHES
 *		ION_IOC_INV_CACHES
 *		ION_IOC_CLEAN_INV_CACHES
 *
 * Returns 0 on success
 */
int ion_do_cache_op(struct ion_client *client, struct ion_handle *handle,
			void *uaddr, unsigned long offset, unsigned long len,
			unsigned int cmd);

int ion_heap_allow_secure_allocation(enum ion_heap_type type);

int ion_heap_allow_heap_secure(enum ion_heap_type type);

int ion_heap_allow_handle_secure(enum ion_heap_type type);

/**
 * ion_create_chunked_sg_table - helper function to create sg table
 * with specified chunk size
 * @buffer_base:	The starting address used for the sg dma address
 * @chunk_size:			The size of each entry in the sg table
 * @total_size:			The total size of the sg table (i.e. the sum of the
 *			entries). This will be rounded up to the nearest
 *			multiple of `chunk_size'
 */
struct sg_table *ion_create_chunked_sg_table(phys_addr_t buffer_base,
					size_t chunk_size, size_t total_size);
#endif /* _MSM_ION_PRIV_H */
