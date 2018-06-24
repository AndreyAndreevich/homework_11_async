#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include "async.h"

using Commands = std::vector<std::string>;

BOOST_AUTO_TEST_SUITE(test_async)

    BOOST_AUTO_TEST_CASE(test_connect) {
        std::size_t bulk = 5;
        void* h;
        BOOST_CHECK_NO_THROW(h = async::connect(bulk));
        BOOST_CHECK_THROW(async::connect(-1),std::exception);
        BOOST_CHECK_THROW(async::connect(0),std::exception);
    }

////////////////////////////////////////////////////////////////////////////////////////////////

    BOOST_AUTO_TEST_CASE(test_receive) {
        auto h1 = async::connect(2);
        BOOST_CHECK_NO_THROW(async::receive(h1,"1", 1));
        BOOST_CHECK_THROW(async::receive(nullptr,"1", 1),std::exception);
        int i = 5;
        auto h2 = reinterpret_cast<void*>(&i);
        BOOST_CHECK_THROW(async::receive(h2,"1", 1),std::exception);
        BOOST_CHECK_THROW(async::receive(h1,"1", 2),std::exception);
        BOOST_CHECK_THROW(async::receive(h1,"11", 1),std::exception);
        BOOST_CHECK_THROW(async::receive(h1,"11", -1),std::exception);

        async::receive(h1,"2\n", 2);
        async::receive(h1,"3\n", 2);
    }

////////////////////////////////////////////////////////////////////////////////////////////////

    BOOST_AUTO_TEST_CASE(test_disconnect) {
        auto h = async::connect(2);
        BOOST_CHECK_NO_THROW(async::receive(h,"1", 1));
        BOOST_CHECK_NO_THROW(async::disconnect(h));
        BOOST_CHECK_NO_THROW(async::disconnect(h));
        BOOST_CHECK_THROW(async::disconnect(nullptr),std::exception);
    }

////////////////////////////////////////////////////////////////////////////////////////////////

    BOOST_AUTO_TEST_CASE(tusk)
    {
        std::size_t bulk = 5;
        auto h = async::connect(bulk);
        auto h2 = async::connect(bulk);
        async::receive(h, "1", 1);
        async::receive(h2, "1\n", 2);
        async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
        async::receive(h, "b\nc\nd\n}\n89\n", 11);
        async::disconnect(h);
        async::disconnect(h2);
    }

BOOST_AUTO_TEST_SUITE_END()