//
// Copyright 2014 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_LIBUHD_USRP_N230_UDP_FW_CTRL_IFACE_HPP
#define INCLUDED_LIBUHD_USRP_N230_UDP_FW_CTRL_IFACE_HPP

#include <uhd/types/wb_iface.hpp>
#include <uhd/transport/udp_simple.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>

namespace uhd { namespace usrp { namespace n230 {

class n230_fw_ctrl_iface : public uhd::wb_iface
{
public:
    n230_fw_ctrl_iface(
        uhd::transport::udp_simple::sptr udp_xport,
        const uint16_t product_id,
        const bool verbose);
    virtual ~n230_fw_ctrl_iface();

    // -- uhd::wb_iface --
    void poke32(const wb_addr_type addr, const uint32_t data);
    uint32_t peek32(const wb_addr_type addr);
    void flush();

    static uhd::wb_iface::sptr make(
        uhd::transport::udp_simple::sptr udp_xport,
        const uint16_t product_id,
        const bool verbose = true);
    // -- uhd::wb_iface --

    static std::vector<std::string> discover_devices(
        const std::string& addr_hint, const std::string& port,
        uint16_t product_id);

    static uint32_t get_iface_id(
        const std::string& addr, const std::string& port,
        uint16_t product_id);

private:
    void _poke32(const wb_addr_type addr, const uint32_t data);
    uint32_t _peek32(const wb_addr_type addr);
    void _flush(void);

    const uint16_t               _product_id;
    const bool                          _verbose;
    uhd::transport::udp_simple::sptr    _udp_xport;
    uint32_t                     _seq_num;
    boost::mutex                        _mutex;

    static const size_t NUM_RETRIES = 3;
};

}}} //namespace

#endif // INCLUDED_LIBUHD_USRP_N230_UDP_FW_CTRL_IFACE_HPP
