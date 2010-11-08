/*
 *
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *
 */

#include <linux/kernel.h>
#include <linux/mm.h>
#include "osd.h"
#include "logging.h"
#include "ring_buffer.h"


/* #defines */


/* Amount of space to write to */
#define BYTES_AVAIL_TO_WRITE(r, w, z) ((w) >= (r)) ? ((z) - ((w) - (r))) : ((r) - (w))


/*++

Name:
	GetRingBufferAvailBytes()

Description:
	Get number of bytes available to read and to write to
	for the specified ring buffer

--*/
static inline void
GetRingBufferAvailBytes(struct hv_ring_buffer_info *rbi, u32 *read, u32 *write)
{
	u32 read_loc, write_loc;

	/* Capture the read/write indices before they changed */
	read_loc = rbi->ring_buffer->read_index;
	write_loc = rbi->ring_buffer->write_index;

	*write = BYTES_AVAIL_TO_WRITE(read_loc, write_loc, rbi->ring_datasize);
	*read = rbi->ring_datasize - *write;
}

/*++

Name:
	GetNextWriteLocation()

Description:
	Get the next write location for the specified ring buffer

--*/
static inline u32
GetNextWriteLocation(struct hv_ring_buffer_info *ring_info)
{
	u32 next = ring_info->ring_buffer->write_index;

	/* ASSERT(next < ring_info->RingDataSize); */

	return next;
}

/*++

Name:
	SetNextWriteLocation()

Description:
	Set the next write location for the specified ring buffer

--*/
static inline void
SetNextWriteLocation(struct hv_ring_buffer_info *ring_info,
		     u32 next_write_location)
{
	ring_info->ring_buffer->write_index = next_write_location;
}

/*++

Name:
	GetNextReadLocation()

Description:
	Get the next read location for the specified ring buffer

--*/
static inline u32
GetNextReadLocation(struct hv_ring_buffer_info *ring_info)
{
	u32 next = ring_info->ring_buffer->read_index;

	/* ASSERT(next < ring_info->RingDataSize); */

	return next;
}

/*++

Name:
	GetNextReadLocationWithOffset()

Description:
	Get the next read location + offset for the specified ring buffer.
	This allows the caller to skip

--*/
static inline u32
GetNextReadLocationWithOffset(struct hv_ring_buffer_info *ring_info, u32 offset)
{
	u32 next = ring_info->ring_buffer->read_index;

	/* ASSERT(next < ring_info->RingDataSize); */
	next += offset;
	next %= ring_info->ring_datasize;

	return next;
}

/*++

Name:
	SetNextReadLocation()

Description:
	Set the next read location for the specified ring buffer

--*/
static inline void
SetNextReadLocation(struct hv_ring_buffer_info *ring_info,
		    u32 next_read_location)
{
	ring_info->ring_buffer->read_index = next_read_location;
}


/*++

Name:
	GetRingBuffer()

Description:
	Get the start of the ring buffer

--*/
static inline void *
GetRingBuffer(struct hv_ring_buffer_info *ring_info)
{
	return (void *)ring_info->ring_buffer->buffer;
}


/*++

Name:
	GetRingBufferSize()

Description:
	Get the size of the ring buffer

--*/
static inline u32
GetRingBufferSize(struct hv_ring_buffer_info *ring_info)
{
	return ring_info->ring_datasize;
}

/*++

Name:
	GetRingBufferIndices()

Description:
	Get the read and write indices as u64 of the specified ring buffer

--*/
static inline u64
GetRingBufferIndices(struct hv_ring_buffer_info *ring_info)
{
	return (u64)ring_info->ring_buffer->write_index << 32;
}


/*++

Name:
	Dumpring_info()

Description:
	Dump out to console the ring buffer info

--*/
void Dumpring_info(struct hv_ring_buffer_info *ring_info, char *prefix)
{
	u32 bytes_avail_towrite;
	u32 bytes_avail_toread;

	GetRingBufferAvailBytes(ring_info,
	&bytes_avail_toread,
	&bytes_avail_towrite);

	DPRINT(VMBUS,
		DEBUG_RING_LVL,
		"%s <<ringinfo %p buffer %p avail write %u "
		"avail read %u read idx %u write idx %u>>",
		prefix,
		ring_info,
		ring_info->ring_buffer->buffer,
		bytes_avail_towrite,
		bytes_avail_toread,
		ring_info->ring_buffer->read_index,
		ring_info->ring_buffer->write_index);
}


/* Internal routines */

static u32
CopyToRingBuffer(
	struct hv_ring_buffer_info	*ring_info,
	u32				start_write_offset,
	void				*src,
	u32				srclen);

static u32
CopyFromRingBuffer(
	struct hv_ring_buffer_info	*ring_info,
	void				*dest,
	u32				destlen,
	u32				start_read_offset);



/*++

Name:
	RingBufferGetDebugInfo()

Description:
	Get various debug metrics for the specified ring buffer

--*/
void RingBufferGetDebugInfo(struct hv_ring_buffer_info *ring_info,
			    struct hv_ring_buffer_debug_info *debug_info)
{
	u32 bytes_avail_towrite;
	u32 bytes_avail_toread;

	if (ring_info->ring_buffer) {
		GetRingBufferAvailBytes(ring_info,
					&bytes_avail_toread,
					&bytes_avail_towrite);

		debug_info->bytes_avail_toread = bytes_avail_toread;
		debug_info->bytes_avail_towrite = bytes_avail_towrite;
		debug_info->current_read_index =
			ring_info->ring_buffer->read_index;
		debug_info->current_write_index =
			ring_info->ring_buffer->write_index;
		debug_info->current_interrupt_mask =
			ring_info->ring_buffer->interrupt_mask;
	}
}


/*++

Name:
	GetRingBufferInterruptMask()

Description:
	Get the interrupt mask for the specified ring buffer

--*/
u32 GetRingBufferInterruptMask(struct hv_ring_buffer_info *rbi)
{
	return rbi->ring_buffer->interrupt_mask;
}

/*++

Name:
	RingBufferInit()

Description:
	Initialize the ring buffer

--*/
int RingBufferInit(struct hv_ring_buffer_info *ring_info,
		   void *buffer, u32 buflen)
{
	if (sizeof(struct hv_ring_buffer) != PAGE_SIZE)
		return -EINVAL;

	memset(ring_info, 0, sizeof(struct hv_ring_buffer_info));

	ring_info->ring_buffer = (struct hv_ring_buffer *)buffer;
	ring_info->ring_buffer->read_index =
		ring_info->ring_buffer->write_index = 0;

	ring_info->ring_size = buflen;
	ring_info->ring_datasize = buflen - sizeof(struct hv_ring_buffer);

	spin_lock_init(&ring_info->ring_lock);

	return 0;
}

/*++

Name:
	RingBufferCleanup()

Description:
	Cleanup the ring buffer

--*/
void RingBufferCleanup(struct hv_ring_buffer_info *ring_info)
{
}

/*++

Name:
	RingBufferWrite()

Description:
	Write to the ring buffer

--*/
int RingBufferWrite(struct hv_ring_buffer_info *outring_info,
		    struct scatterlist *sglist, u32 sgcount)
{
	int i = 0;
	u32 bytes_avail_towrite;
	u32 bytes_avail_toread;
	u32 totalbytes_towrite = 0;

	struct scatterlist *sg;
	volatile u32 next_write_location;
	u64 prev_indices = 0;
	unsigned long flags;

	for_each_sg(sglist, sg, sgcount, i)
	{
		totalbytes_towrite += sg->length;
	}

	totalbytes_towrite += sizeof(u64);

	spin_lock_irqsave(&outring_info->ring_lock, flags);

	GetRingBufferAvailBytes(outring_info,
				&bytes_avail_toread,
				&bytes_avail_towrite);

	DPRINT_DBG(VMBUS, "Writing %u bytes...", totalbytes_towrite);

	/* Dumpring_info(Outring_info, "BEFORE "); */

	/* If there is only room for the packet, assume it is full. */
	/* Otherwise, the next time around, we think the ring buffer */
	/* is empty since the read index == write index */
	if (bytes_avail_towrite <= totalbytes_towrite) {
		DPRINT_DBG(VMBUS,
			"No more space left on outbound ring buffer "
			"(needed %u, avail %u)",
			totalbytes_towrite,
			bytes_avail_towrite);

		spin_unlock_irqrestore(&outring_info->ring_lock, flags);
		return -1;
	}

	/* Write to the ring buffer */
	next_write_location = GetNextWriteLocation(outring_info);

	for_each_sg(sglist, sg, sgcount, i)
	{
		next_write_location = CopyToRingBuffer(outring_info,
						     next_write_location,
						     sg_virt(sg),
						     sg->length);
	}

	/* Set previous packet start */
	prev_indices = GetRingBufferIndices(outring_info);

	next_write_location = CopyToRingBuffer(outring_info,
					     next_write_location,
					     &prev_indices,
					     sizeof(u64));

	/* Make sure we flush all writes before updating the writeIndex */
	mb();

	/* Now, update the write location */
	SetNextWriteLocation(outring_info, next_write_location);

	/* Dumpring_info(Outring_info, "AFTER "); */

	spin_unlock_irqrestore(&outring_info->ring_lock, flags);
	return 0;
}


/*++

Name:
	RingBufferPeek()

Description:
	Read without advancing the read index

--*/
int RingBufferPeek(struct hv_ring_buffer_info *Inring_info,
		   void *Buffer, u32 buflen)
{
	u32 bytes_avail_towrite;
	u32 bytes_avail_toread;
	u32 next_read_location = 0;
	unsigned long flags;

	spin_lock_irqsave(&Inring_info->ring_lock, flags);

	GetRingBufferAvailBytes(Inring_info,
				&bytes_avail_toread,
				&bytes_avail_towrite);

	/* Make sure there is something to read */
	if (bytes_avail_toread < buflen) {
		/* DPRINT_DBG(VMBUS,
			"got callback but not enough to read "
			"<avail to read %d read size %d>!!",
			bytes_avail_toread,
			BufferLen); */

		spin_unlock_irqrestore(&Inring_info->ring_lock, flags);

		return -1;
	}

	/* Convert to byte offset */
	next_read_location = GetNextReadLocation(Inring_info);

	next_read_location = CopyFromRingBuffer(Inring_info,
						Buffer,
						buflen,
						next_read_location);

	spin_unlock_irqrestore(&Inring_info->ring_lock, flags);

	return 0;
}


/*++

Name:
	RingBufferRead()

Description:
	Read and advance the read index

--*/
int RingBufferRead(struct hv_ring_buffer_info *inring_info, void *buffer,
		   u32 buflen, u32 offset)
{
	u32 bytes_avail_towrite;
	u32 bytes_avail_toread;
	u32 next_read_location = 0;
	u64 prev_indices = 0;
	unsigned long flags;

	if (buflen <= 0)
		return -EINVAL;

	spin_lock_irqsave(&inring_info->ring_lock, flags);

	GetRingBufferAvailBytes(inring_info,
				&bytes_avail_toread,
				&bytes_avail_towrite);

	DPRINT_DBG(VMBUS, "Reading %u bytes...", buflen);

	/* Dumpring_info(Inring_info, "BEFORE "); */

	/* Make sure there is something to read */
	if (bytes_avail_toread < buflen) {
		DPRINT_DBG(VMBUS,
			"got callback but not enough to read "
			"<avail to read %d read size %d>!!",
			bytes_avail_toread,
			buflen);

		spin_unlock_irqrestore(&inring_info->ring_lock, flags);

		return -1;
	}

	next_read_location = GetNextReadLocationWithOffset(inring_info, offset);

	next_read_location = CopyFromRingBuffer(inring_info,
						buffer,
						buflen,
						next_read_location);

	next_read_location = CopyFromRingBuffer(inring_info,
						&prev_indices,
						sizeof(u64),
						next_read_location);

	/* Make sure all reads are done before we update the read index since */
	/* the writer may start writing to the read area once the read index */
	/*is updated */
	mb();

	/* Update the read index */
	SetNextReadLocation(inring_info, next_read_location);

	/* Dumpring_info(Inring_info, "AFTER "); */

	spin_unlock_irqrestore(&inring_info->ring_lock, flags);

	return 0;
}


/*++

Name:
	CopyToRingBuffer()

Description:
	Helper routine to copy from source to ring buffer.
	Assume there is enough room. Handles wrap-around in dest case only!!

--*/
static u32
CopyToRingBuffer(
	struct hv_ring_buffer_info	*ring_info,
	u32				start_write_offset,
	void				*src,
	u32				srclen)
{
	void *ring_buffer = GetRingBuffer(ring_info);
	u32 ring_buffer_size = GetRingBufferSize(ring_info);
	u32 frag_len;

	/* wrap-around detected! */
	if (srclen > ring_buffer_size - start_write_offset) {
		DPRINT_DBG(VMBUS, "wrap-around detected!");

		frag_len = ring_buffer_size - start_write_offset;
		memcpy(ring_buffer + start_write_offset, src, frag_len);
		memcpy(ring_buffer, src + frag_len, srclen - frag_len);
	} else
		memcpy(ring_buffer + start_write_offset, src, srclen);

	start_write_offset += srclen;
	start_write_offset %= ring_buffer_size;

	return start_write_offset;
}


/*++

Name:
	CopyFromRingBuffer()

Description:
	Helper routine to copy to source from ring buffer.
	Assume there is enough room. Handles wrap-around in src case only!!

--*/
static u32
CopyFromRingBuffer(
	struct hv_ring_buffer_info	*ring_info,
	void				*dest,
	u32				destlen,
	u32				start_read_offset)
{
	void *ring_buffer = GetRingBuffer(ring_info);
	u32 ring_buffer_size = GetRingBufferSize(ring_info);

	u32 frag_len;

	/* wrap-around detected at the src */
	if (destlen > ring_buffer_size - start_read_offset) {
		DPRINT_DBG(VMBUS, "src wrap-around detected!");

		frag_len = ring_buffer_size - start_read_offset;

		memcpy(dest, ring_buffer + start_read_offset, frag_len);
		memcpy(dest + frag_len, ring_buffer, destlen - frag_len);
	} else

		memcpy(dest, ring_buffer + start_read_offset, destlen);


	start_read_offset += destlen;
	start_read_offset %= ring_buffer_size;

	return start_read_offset;
}


/* eof */
