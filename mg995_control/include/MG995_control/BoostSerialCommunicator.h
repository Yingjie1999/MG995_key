#ifndef BOOST_SERIAL_COMMUNICATOR_H_
#define BOOST_SERIAL_COMMUNICATOR_H_

#include <string>
#include <boost/assert.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>


namespace vwpp
{
    typedef boost::asio::serial_port_base boost_serial_base;

    class BoostSerialCommunicator
    {
    public:
        BoostSerialCommunicator();
        BoostSerialCommunicator(std::string port_, int baud_,
                                boost_serial_base::flow_control::type fc_type_ = boost_serial_base::flow_control::none,
                                boost_serial_base::parity::type pa_type_ = boost_serial_base::parity::none,
                                boost_serial_base::stop_bits::type st_type_ = boost_serial_base::stop_bits::one);

        virtual ~BoostSerialCommunicator();

        uint8_t* getMessage(int msg_length_);
        // int sendMessage(const uint8_t* msg_);
        int sendMessage(const std::vector<uint8_t>& vec_msg_);
        int fixError(int header_index_, int msg_length_);

    protected:

    private:
        boost::asio::serial_port* serial_port;
        int fd_;

    }; // class BoostSerialCommunicator

} // namespace vwpp


#endif
