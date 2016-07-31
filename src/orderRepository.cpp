#include <iostream>
#include <set>
#include <boost/thread/lock_guard.hpp>

#include "Commodity.h"
#include "Dealer.h"
#include "orderRepository.h"
#include "OrderNotFoundException.h"

namespace cms {
    namespace orderRepository {
        std::map<OrderID, Order*> orderList;
        std::map<COMMODITIES_TYPES_ENUM::_enumerated, std::map<OrderID, Order*> > commodityIDX;
        std::map<std::pair<COMMODITIES_TYPES_ENUM::_enumerated, DEALERS_IDS_ENUM::_enumerated>, std::map<OrderID, Order*> > commodityDealerIDX;

        static OrderID progressiveOrderNumber = 1;
        boost::mutex mtx;

        Order &findOne(OrderID i) {
            boost::lock_guard<boost::mutex> guard(mtx);
            if (orderList.find(i) != orderList.end()) {
                return *orderList[i];
            } else {
                throw OrderNotFoundException("UNKNOWN_ORDER");
            }
        }

        OrderID add(Order o) {
            boost::lock_guard<boost::mutex> guard(mtx);
            Order* order = new Order(o);
            OrderID orderID = progressiveOrderNumber++;
            orderList.insert(std::pair<OrderID, Order*>(orderID, order));
            commodityIDX[o.getCommodity()].insert(std::pair<OrderID, Order*>(orderID, order));
            std::pair<COMMODITIES_TYPES_ENUM::_enumerated, DEALERS_IDS_ENUM::_enumerated> cd(o.getCommodity(), o.getDealer());
            commodityDealerIDX[cd].insert(std::pair<OrderID, Order*>(orderID, order));
            return orderID;
        }

        const std::map<OrderID, Order*> &list() {
            boost::lock_guard<boost::mutex> guard(mtx);
            return orderList;
        }

        const std::map<OrderID, Order*> &list(COMMODITIES_TYPES_ENUM::_enumerated c){
            boost::lock_guard<boost::mutex> guard(mtx);
            return commodityIDX[c];
        };

        const std::map<OrderID, Order*> &list(COMMODITIES_TYPES_ENUM::_enumerated c, DEALERS_IDS_ENUM::_enumerated d){
            boost::lock_guard<boost::mutex> guard(mtx);
            std::pair<COMMODITIES_TYPES_ENUM::_enumerated, DEALERS_IDS_ENUM::_enumerated> cd(c,d);
            return commodityDealerIDX[cd];
        };

        void remove(OrderID i) {
            boost::lock_guard<boost::mutex> guard(mtx);
            if (orderList.find(i) != orderList.end()) {
                delete orderList[i];
                commodityIDX[orderList[i]->getCommodity()].erase(i);
                std::pair<COMMODITIES_TYPES_ENUM::_enumerated, DEALERS_IDS_ENUM::_enumerated> cd(orderList[i]->getCommodity(), orderList[i]->getDealer());
                commodityDealerIDX[cd].erase(i);
                orderList.erase(i);
            } else {
                throw OrderNotFoundException("UNKNOWN_ORDER");
            }
        }
    }
}