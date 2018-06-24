#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include "Storage.h"

using Commands = std::vector<std::string>;

BOOST_AUTO_TEST_SUITE(test_storage)

    BOOST_AUTO_TEST_CASE(get_test) {
        int id;
        BOOST_CHECK_NO_THROW(id = Storage::Instance().addHandler(2));
        BOOST_CHECK_NO_THROW(Storage::Instance().getHandler(id));
        BOOST_CHECK_THROW(Storage::Instance().getHandler(0),std::exception);
        BOOST_CHECK_THROW(Storage::Instance().getHandler(-5),std::exception);
        BOOST_CHECK_THROW(Storage::Instance().getHandler(1000),std::exception);
    }

////////////////////////////////////////////////////////////////////////////////////////////////

    BOOST_AUTO_TEST_CASE(remove_test) {
        int id;
        BOOST_CHECK_NO_THROW(id = Storage::Instance().addHandler(2));
        BOOST_CHECK_NO_THROW(Storage::Instance().removeHandler(id));
        BOOST_CHECK_NO_THROW(Storage::Instance().removeHandler(id));
        BOOST_CHECK_NO_THROW(Storage::Instance().removeHandler(0));
        BOOST_CHECK_NO_THROW(Storage::Instance().removeHandler(-5));
        BOOST_CHECK_NO_THROW(Storage::Instance().removeHandler(1000));
    }

////////////////////////////////////////////////////////////////////////////////////////////////

    BOOST_AUTO_TEST_CASE(add_and_remove_test) {
        struct TestStorage : public Storage {
          TestStorage() = default;
          int size() {
            return data.size();
          }
        };
        
        int id1;
        int id2;
        TestStorage storage;
        BOOST_CHECK_EQUAL(storage.size(),0);
        BOOST_CHECK_NO_THROW(id1 = storage.addHandler(2));
        BOOST_CHECK_EQUAL(storage.size(),1);
        BOOST_CHECK_NO_THROW(id2 = storage.addHandler(3));
        BOOST_CHECK_EQUAL(storage.size(),2);
        BOOST_CHECK_NO_THROW(storage.removeHandler(id1));
        BOOST_CHECK_EQUAL(storage.size(),1);
        BOOST_CHECK_NO_THROW(storage.removeHandler(id2));
        BOOST_CHECK_EQUAL(storage.size(),0);
    }

BOOST_AUTO_TEST_SUITE_END()