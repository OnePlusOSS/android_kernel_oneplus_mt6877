/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2018-2020 Oplus. All rights reserved.
 */

#ifndef __ION_TRACK_H
#define __ION_TRACK_H

static struct ion_device *internal_dev = NULL;

static inline void update_internal_dev(struct ion_device *dev)
{
	if (!internal_dev)
		internal_dev = dev;
}

#endif /* __ION_TRACK_H */
