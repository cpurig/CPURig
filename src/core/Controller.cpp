/* CPURig
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
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

#include "core/Controller.h"
#include "backend/cpu/Cpu.h"
#include "core/config/Config.h"
#include "core/Miner.h"
#include "crypto/common/VirtualMemory.h"
#include "net/Network.h"


#ifdef CPURIG_FEATURE_API
#   include "base/api/Api.h"
#   include "hw/api/HwApi.h"
#endif


#include <cassert>


cpurig::Controller::Controller(Process *process) :
    Base(process)
{
}


cpurig::Controller::~Controller()
{
    VirtualMemory::destroy();
}


int cpurig::Controller::init()
{
    Base::init();

    VirtualMemory::init(config()->cpu().memPoolSize(), config()->cpu().hugePageSize());

    m_network = std::make_shared<Network>(this);

#   ifdef CPURIG_FEATURE_API
    m_hwApi = std::make_shared<HwApi>();
    api()->addListener(m_hwApi.get());
#   endif

    return 0;
}

#ifdef CPURIG_FEATURE_MO_BENCHMARK
void cpurig::Controller::pre_start()
{
    m_miner = std::make_shared<Miner>(this);
}
#endif


void cpurig::Controller::start()
{
    Base::start();

    if (m_miner == nullptr) m_miner = std::make_shared<Miner>(this);

    network()->connect();
}


void cpurig::Controller::stop()
{
    Base::stop();

    m_network.reset();

    m_miner->stop();
    m_miner.reset();
}


cpurig::Miner *cpurig::Controller::miner() const
{
    assert(m_miner);

    return m_miner.get();
}


cpurig::Network *cpurig::Controller::network() const
{
    assert(m_network);

    return m_network.get();
}


void cpurig::Controller::execCommand(char command) const
{
    miner()->execCommand(command);
    network()->execCommand(command);
}
