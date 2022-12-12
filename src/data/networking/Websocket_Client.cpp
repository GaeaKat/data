// Copyright (c) 2022 Katrina Knight
// Distributed under the Open BSV software license, see the accompanying file LICENSE.
#include <data/networking/Websocket_Client.hpp>
#include <utility>

namespace data::networking::HTTP::Websocket {


	template<typename T>
	session<T>::session(net::io_context &ioc, std::string host, std::string port, std::string target, bool secure) :
		resolver_(net::make_strand(ioc)),
		ws_(net::make_strand(ioc)),
		host_(std::move(host)),
		port_(std::move(port)),
		target_(std::move(target)),
		secure_(secure)
	{
	}

}
