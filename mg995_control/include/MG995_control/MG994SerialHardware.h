#ifndef VWBOTSERIALHARDWARE_H_
#define VWBOTSERIALHARDWARE_H_

#include <cstdint>
#include <cstring>
#include <queue>
#include <MG995_control/BoostSerialCommunicator.h>
#include <MG995_control/utils.h>
namespace vwpp
{
    class MG995SerialHardware
    {
    public:
        MG995SerialHardware(std::string model_, std::string port_, int baud_,
                            int msg_length_,
                            boost_serial_base::flow_control::type fc_type_ = boost_serial_base::flow_control::none,
                            boost_serial_base::parity::type pa_type_ = boost_serial_base::parity::none,
                            boost_serial_base::stop_bits::type st_type = boost_serial_base::stop_bits::one);
        virtual ~MG995SerialHardware();

        struct Velocity2D
        {
        public:
            float x;
            float y;
            float yaw;
        };
        float key;

        int sendMessage_velocity(Velocity2D vel_);
        int sendMessage_key(bool key_);
    private:

        std::string model;
        std::string port;
        const int baud;
        const int msg_length;

        boost_serial_base::flow_control::type fc_type;
        boost_serial_base::parity::type pa_type;
        boost_serial_base::stop_bits::type st_type;

        BoostSerialCommunicator* boost_serial_communicator;

        lock_t mutex{};

        const uint8_t* msg_stop;
        const uint8_t* msg_start;

    }; // class VwbotSerialHardware

} // namespace vwpp

#endif
