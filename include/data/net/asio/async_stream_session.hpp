// Copyright (c) 2023 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_NET_ASIO_ASYNC_STREAM_SESSION
#define DATA_NET_ASIO_ASYNC_STREAM_SESSION

#include <data/net/asio/async_message_queue.hpp>
#include <data/net/asio/async_wait_for_message.hpp>
#include <data/tools.hpp>

namespace data::net::asio {

    template <typename derived_session, typename async_stream, typename word>
    struct async_stream_session : session<const std::basic_string<word> &>, std::enable_shared_from_this<derived_session> {

        async_message_queue<async_stream, word> Queue;

        void send (const std::basic_string<word> &x) final override {
            Queue.write (x);
        }

        async_stream_session (ptr<async_stream> x, error_handler errors) : Queue {x, errors} {}

        void wait_for_message (
            receive_handler<derived_session, std::basic_string_view<word>> handler,
            error_handler errors) {
            async_wait_for_message<async_stream, word> (Queue.Stream, handler (this->shared_from_this ()), errors);
        }

    };

}

#endif


