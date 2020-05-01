#include <boost/asio.hpp>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) { 

	try {
		if (argc != 2) {
	      std::cerr << "Usage: client <host>" << std::endl;
	      return 1;
	    }

	    boost::asio::io_service io_service;

	    boost::asio::ip::udp::resolver resolver(io_service);
	    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), argv[1], "daytime");
		boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);

		boost::asio::ip::udp::socket socket(io_service);
		socket.open(boost::asio::ip::udp::v4());

		std::array<char, 1> send_buf = { 0 };
		socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

		std::array<char, 128> recv_buf;
		boost::asio::ip::udp::endpoint sender_endpoint;

		size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

		cout.write(recv_buf.data(), len);
	} catch (exception& e) {
		cerr << e.what() << "\n";
	}

	return 0; 
}
