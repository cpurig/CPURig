/* CPURig
 * Copyright 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2021 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
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

#ifndef CPURIG_IBASELISTENER_H
#define CPURIG_IBASELISTENER_H


#include "base/tools/Object.h"


namespace cpurig {


class Config;


class IBaseListener
{
public:
    CPURIG_DISABLE_COPY_MOVE(IBaseListener)

    IBaseListener()             = default;
    virtual ~IBaseListener()    = default;

    virtual void onConfigChanged(Config *config, Config *previousConfig) = 0;
};


} /* namespace cpurig */


#endif // CPURIG_IBASELISTENER_H
