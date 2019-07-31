#include <MG995_control/BoostSerialCommunicator.h>
#include <iostream>

using namespace vwpp;


BoostSerialCommunicator::BoostSerialCommunicator():
        fd_(-1),
        serial_port(nullptr)
{

}


BoostSerialCommunicator::BoostSerialCommunicator(std::string port_, int baud_,
                                                 boost_serial_base::flow_control::type fc_type_,
                                                 boost_serial_base::parity::type pa_type_,
                                                 boost_serial_base::stop_bits::type st_type_)
{
    BoostSerialCommunicator();


    boost::asio::io_service tmp_io_service;
    serial_port = new boost::asio::serial_port(tmp_io_service);

    try
    {
        serial_port->open(port_);
    }
    catch (boost::system::system_error &error)
    {
        std::cerr << "\033[31m" << "Failed to open port " << port_.c_str()
                  << " with error " << error.what() << "\033[0m" << std::endl;
        exit(1);
    }

    if (!serial_port->is_open())
    {
        std::cerr << "\033[31m" << "Failed to open port " << port_.c_str()
                  << "\033[0m" << std::endl;
        exit(1);
    }


    boost_serial_base::baud_rate baud_option(baud_);
    boost_serial_base::flow_control flow_control_option(fc_type_);
    boost_serial_base::parity parity_option(pa_type_);
    boost_serial_base::stop_bits stop_bits_option(st_type_);

    serial_port->set_option(baud_option);
    serial_port->set_option(flow_control_option);
    serial_port->set_option(parity_option);
    serial_port->set_option(stop_bits_option);


    const char *path = port_.c_str();
    fd_ = open(path, O_RDWR);
    if(fd_ < 0)
    {
        std::cerr << "\033[31m" << "Port Error: " << path
                  << "\033[0m" << std::endl;
        exit(1);
    }

    std::cout << "\033[32m" << "Successfully open serial device: "  << port_
              << "\033[0m" << std::endl;
}


BoostSerialCommunicator::~BoostSerialCommunicator()
{
    ::close(fd_);
}


uint8_t* BoostSerialCommunicator::getMessage(const int msg_length_)
{
    int msg_buf_length = 2*msg_length_;

    uint8_t* tmp = new uint8_t[msg_buf_length];
    read(fd_, tmp, sizeof(uint8_t) * msg_buf_length);

    if (!tmp)
    {
        std::cerr << "\033[31m" << "Don't receive any message!"
                  << "\033[0m" << std::endl;
    }
    return tmp;
}


int BoostSerialCommunicator::sendMessage(const std::vector<uint8_t>& vec_msg_)
{
    auto* msg_buffer = new uint8_t[vec_msg_.size()];
    if (!vec_msg_.empty())
    {
        memcpy(msg_buffer, &vec_msg_[0], vec_msg_.size()*sizeof(uint8_t));
    }
    else
    {
        std::cerr << "\033[31m" << "Send message mustn't be EMPTY!"
                  << "\033[0m" << std::endl;
        return (-1);
    }

    write(fd_, msg_buffer, vec_msg_.size());
    return 1;
}


int BoostSerialCommunicator::fixError(const int header_index_, const int msg_length_)
{
    const int msg_buf_length = 2*msg_length_;

    if (header_index_ > msg_length_ && header_index_ < msg_buf_length)
    {
        // TODO
        // Consider to return the dropped msg.
        uint8_t* dropped_msg = this->getMessage(header_index_ - msg_length_);
        delete[] dropped_msg;

        // Find out the error when receiving data and fixed it, return value -1.
        return -1;
    }

    // No problem, return value 1.
    return 1;
}

