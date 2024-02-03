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

#ifndef CPURIG_CUDABACKEND_H
#define CPURIG_CUDABACKEND_H


#include <utility>


#include "backend/common/interfaces/IBackend.h"
#include "base/tools/Object.h"


namespace cpurig {


class Controller;
class CudaBackendPrivate;
class Miner;


class CudaBackend : public IBackend
{
public:
    CPURIG_DISABLE_COPY_MOVE_DEFAULT(CudaBackend)

    CudaBackend(Controller *controller);

    ~CudaBackend() override;

protected:
    bool isEnabled() const override;
    bool isEnabled(const Algorithm &algorithm) const override;
    const Hashrate *hashrate() const override;
    const String &profileName() const override;
    const String &type() const override;
    void execCommand(char command) override;
    void prepare(const Job &nextJob) override;
    void printHashrate(bool details) override;
    void printHealth() override;
    void setJob(const Job &job) override;
    void start(IWorker *worker, bool ready) override;
    void stop() override;
    bool tick(uint64_t ticks) override;

#   ifdef CPURIG_FEATURE_API
    rapidjson::Value toJSON(rapidjson::Document &doc) const override;
    void handleRequest(IApiRequest &request) override;
#   endif

#   ifdef CPURIG_FEATURE_BENCHMARK
    inline Benchmark *benchmark() const override        { return nullptr; }
    inline void printBenchProgress() const override     {}
#   endif

private:
    CudaBackendPrivate *d_ptr;
};


} /* namespace cpurig */


#endif /* CPURIG_CUDABACKEND_H */