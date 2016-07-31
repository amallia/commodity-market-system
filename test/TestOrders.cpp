#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Orders

#include <boost/test/unit_test.hpp>
#include <boost/thread/thread.hpp>
#include <boost/utility.hpp>

#include "Dealer.h"
#include "Side.h"
#include "Commodity.h"

#include "Order.h"
#include "orderRepository.h"
#include "OrderNotFoundException.h"

namespace cms {
    namespace test {


        bool unknownOrder(OrderNotFoundException const &ex) {
            BOOST_CHECK_EQUAL(ex.what(), "UNKNOWN_ORDER");
            return true;
        }


        BOOST_AUTO_TEST_CASE(orders) {

            // New order
            Order o1(DEALERS_IDS_ENUM::DB, SIDES_TYPES_ENUM::BUY,
                     COMMODITIES_TYPES_ENUM::GOLD, 1000000, 1174.6);

            // Add order
            OrderID id = orderRepository::add(o1);
            BOOST_CHECK_EQUAL(id, 1);
            // Retrieve order
            Order o2 = orderRepository::findOne(id);
            BOOST_CHECK_EQUAL(o1.getDealer(), o2.getDealer());
            BOOST_CHECK_EQUAL(o1.getSide(), o2.getSide());
            BOOST_CHECK_EQUAL(o1.getCommodity(), o2.getCommodity());
            BOOST_CHECK_EQUAL(o1.getAmount(), o2.getAmount());
            BOOST_CHECK_EQUAL(o1.getPrice(), o2.getPrice());

            // Add second order
            BOOST_CHECK_EQUAL(orderRepository::add(o2), id + 1);

            // Reduce order amount
            o1.reduce(300000);
            BOOST_CHECK_EQUAL(o1.getAmount(), 700000);

            // Find non existing order
            BOOST_CHECK_EXCEPTION(orderRepository::findOne(10), OrderNotFoundException, unknownOrder);

            // Get orders list
            std::map<OrderID, Order*> orderlist = orderRepository::list();
            BOOST_CHECK_EQUAL(orderlist.size(), 2);

            // Remove order
            orderRepository::remove(2);
            orderlist = orderRepository::list();
            BOOST_CHECK_EQUAL(orderlist.size(), 1);
            orderRepository::remove(1);
            orderlist = orderRepository::list();
            BOOST_CHECK_EQUAL(orderlist.size(), 0);

            // Remove non existing order
            BOOST_CHECK_EXCEPTION(orderRepository::remove(20), OrderNotFoundException, unknownOrder);

            boost::thread_group group;
            for (OrderID i = 0; i < 10000; ++i) {
                group.create_thread(boost::bind(&orderRepository::add, o1));
            }
            group.join_all();

            BOOST_CHECK_EQUAL(orderRepository::list().size(), 10000);
            orderlist = orderRepository::list();
            for (std::map<OrderID, Order*>::iterator it = orderlist.begin(); it != boost::prior(orderlist.end()); ++it) {
                BOOST_CHECK_EQUAL(boost::next(it)->first - it->first, 1);
            }

            for (std::map<OrderID, Order*>::iterator it = orderlist.begin(); it != orderlist.end(); ++it) {
                group.create_thread(boost::bind(&orderRepository::remove, it->first));
            }
            group.join_all();
            BOOST_CHECK_EQUAL(orderRepository::list().size(), 0);


        }
    }
}
