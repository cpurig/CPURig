/* CPURig
 * Copyright (c) 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2020 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *   Copyright 2023 duggavo        <https://github.com/duggavo>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "base/net/tools/NetBuffer.h"
#include "base/kernel/constants.h"
#include "base/net/tools/MemPool.h"


#include <cassert>
#include <uv.h>


namespace cpurig {


static MemPool<CPURIG_NET_BUFFER_CHUNK_SIZE, CPURIG_NET_BUFFER_INIT_CHUNKS> *pool = nullptr;


inline MemPool<CPURIG_NET_BUFFER_CHUNK_SIZE, CPURIG_NET_BUFFER_INIT_CHUNKS> *getPool()
{
    if (!pool) {
        pool = new MemPool<CPURIG_NET_BUFFER_CHUNK_SIZE, CPURIG_NET_BUFFER_INIT_CHUNKS>();
    }

    return pool;
}


} // namespace cpurig


char *cpurig::NetBuffer::allocate()
{
    return getPool()->allocate();
}


void cpurig::NetBuffer::destroy()
{
    if (!pool) {
        return;
    }

    assert(pool->freeSize() == pool->size());

    delete pool;
    pool = nullptr;
}


void cpurig::NetBuffer::onAlloc(uv_handle_t *, size_t, uv_buf_t *buf)
{
    buf->base = getPool()->allocate();
    buf->len  = CPURIG_NET_BUFFER_CHUNK_SIZE;
}


void cpurig::NetBuffer::release(const char *buf)
{
    if (buf == nullptr) {
        return;
    }

    getPool()->deallocate(buf);
}


void cpurig::NetBuffer::release(const uv_buf_t *buf)
{
    if (buf->base == nullptr) {
        return;
    }

    getPool()->deallocate(buf->base);
}
