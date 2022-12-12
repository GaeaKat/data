// Copyright (c) 2022 Katrina Knight
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef DATA_NETWORKING_WEBSOCKET_CLIENT
#define DATA_NETWORKING_WEBSOCKET_CLIENT

#include "data/types.hpp"
#include <data/networking/session.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>
#include "URL.hpp"
namespace data::networking::HTTP::Websocket {
	namespace beast = boost::beast;         // from <boost/beast.hpp>
	namespace http = beast::http;           // from <boost/beast/http.hpp>
	namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
	namespace net = boost::asio;            // from <boost/asio.hpp>
	using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
	namespace io = boost::asio;
	using io_error = boost::system::error_code;



	template <typename T>
	class session : virtual public networking::session<bytes_view>, protected std::enable_shared_from_this<session<T>> {
		tcp::resolver resolver_;
		websocket::stream<T> ws_;
		ptr<io::streambuf> Buffer;
		std::string host_;
		std::string port_;
		std::string target_;
		bool secure_;

		// begin waiting for the next message asynchronously.
		void wait_for_message();
		virtual void handle_error(const io_error &err);

	  public:
		explicit session(net::io_context& ioc,std::string host, std::string port, std::string target, bool secure);
//		: resolver_(net::make_strand(ioc))
//		, ws_(net::make_strand(ioc))
//		{
//		}

		void send(bytes_view) final override;
		virtual ~session();

	};


	session<tcp::socket> connect(std::string host, std::string port, std::string target);
	session<beast::ssl_stream<tcp::socket>> connect_secure(std::string host, std::string port, std::string target);
}


#endif // DATA_NETWORKING_WEBSOCKET_CLIENT
