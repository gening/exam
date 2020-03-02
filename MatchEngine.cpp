#include <iostream>
#include <vector>
#include <string>

enum class Side : char {
    BUY = 'B',
    SELL = 'S'
};

enum class OrderType {
    LIMIT,
    IOC, //Immediate-Or-Cancel
};

class Order {
public:
    std::string orderId;
    Side side;
    std::string symbol;
    OrderType orderType;
    int price;
    int qty;

    Order(std::string& orderId,
          Side side,
          std::string& symbol,
          OrderType orderType,
          int price,
          int qty)
          : orderId(orderId)
          , side(side)
          , symbol(symbol)
          , orderType(orderType)
          , price(price)
          , qty(qty)
          {};

    virtual ~Order() = default;
    
    std::string toString() const {
        // Format: 'qty@price#orderId'
        std::string ret = "'";
        ret += std::to_string(qty);
        ret += "@";
        ret += hasPrice() ? std::to_string(price) : "NaN";
        ret += "#";
        ret += orderId;
        ret += "'";
        return ret;
    }

    bool hasPrice() const {
        return orderType == OrderType::LIMIT;
    }
};

class OrderBook {
protected:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;

    void insert(Order& order) {
        if (order.qty > 0) {
            std::vector<Order>& orders = (order.side == Side::BUY ? buyOrders : sellOrders);
            auto it = orders.begin();
            for ( ; it != orders.end(); ++it) {
                if ((!order.hasPrice() && (*it).hasPrice()) ||
                    (order.side == Side::BUY && order.price > (*it).price) ||
                    (order.side == Side::SELL && order.price < (*it).price)) {
                    orders.insert(it, order);
                    break;
                }
            }

            if (it == orders.end()) {
                orders.insert(it, order);
            }
        }
    }

    void match(Order& order) {
        // Locate opposite orders
        std::vector<Order>& opposites = (order.side == Side::BUY ? sellOrders : buyOrders);
        while (!opposites.empty() && order.qty > 0 &&
               (!order.hasPrice() ||
                (order.side == Side::SELL && order.price <= opposites[0].price) ||
                (order.side == Side::BUY && order.price >= opposites[0].price))) {
            // matched
            if (order.qty < opposites[0].qty) {
                opposites[0].qty -= order.qty;
                order.qty = 0;
            } else {
                order.qty -= opposites[0].qty;
                opposites[0].qty = 0;
                opposites.erase(opposites.begin());
            }
        }
    }

    bool deleteOrder(const std::string& orderId, const Side side) {
        bool deleted = false;
        std::vector<Order>& orders = (side == Side::BUY ? buyOrders : sellOrders);
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if ((*it).orderId == orderId) {
                orders.erase(it);
                deleted = true;
                break;
            }
        }
        return deleted;
    }

    void print(const Side side) const {
        // Format: "Side: [..., ...]"
        const std::vector<Order>& orders = (side == Side::BUY ? buyOrders : sellOrders);
        std::cout << (char)side << ": [";
        for (int i = 0; i < orders.size(); i++) {
            std::cout << orders[i].toString();
            if (i != orders.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

public:
    OrderBook() = default;

    OrderBook(const OrderBook&) = delete;
    OrderBook(OrderBook&&) = delete;

    ~OrderBook() = default;

    void addOrder(Order& order) {
        match(order);
        if (order.orderType != OrderType::IOC) {
            insert(order);
        }
    }

    bool deleteOrder(const std::string& orderId) {
        bool deleted = deleteOrder(orderId, Side::SELL);
        if (!deleted) {
            deleted = deleteOrder(orderId, Side::BUY);
        }
        return deleted;
    }

    void print() const {
        print(Side::BUY);
        print(Side::SELL);
    }
};

int main() {
    OrderBook orderBook;

    std::string action, orderId, symbol, price;
    char side;
    OrderType orderType;
    int qty;
    
    // Input format:
    // SUB ivxv B foo 7 450
    // SUB abcd S foo NaN 1000
    // CXL xyzw
    // END
    std::cin >> action;
    while (action != "END") {
        if (action == "SUB") {
            std::cin >> orderId >> side >> symbol >> price >> qty;
            if (price == "NaN") {
                price = "0";
                orderType = OrderType::IOC;
            } else {
                orderType = OrderType::LIMIT;
            }
            Order order(orderId, (Side) side, symbol, orderType, std::stoi(price), qty);
            std::cout << "debug : New Single Order " << order.toString();
            // Here must support copy-constructor to maintain its member values.
            orderBook.addOrder(order);
            std::cout << " " << order.toString() << std::endl;
            // `order` instance is out of scope and will be destroyed, unless we use `new` to initialise an object.
        } else if (action == "CXL") {
            std::cin >> orderId;
            orderBook.deleteOrder(orderId);
        }
        std::cout << "debug : Order Book" << std::endl; orderBook.print();

        std::cin >> action;
    }

    orderBook.print();
    return 0;
}

/*
SUB OID1 B foo  7  450
SUB OID2 B foo 10 1000
SUB OID3 S foo 12  400
SUB OID4 S foo 12  250
SUB OID5 B foo  6  500
SUB OID6 S foo 11  200
SUB OID7 B foo 10  350
END
 */