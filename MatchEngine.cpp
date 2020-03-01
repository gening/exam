#include <iostream>
#include <vector>
#include <string>

enum class Side : char {
    Buy = 'B',
    Sell = 'S'
};

enum class OrderType {
    Limit,
    IOC, //Immediate-Or-Cancel
};

struct Order {
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
          int qty) {
        this->orderId = orderId;
        this->side = side;
        this->symbol = symbol;
        this->orderType = orderType;
        this->price = price;
        this->qty = qty;
    }
    
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
        return orderType == OrderType::Limit;
    }
};

class OrderBook {
protected:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;

    void insert(const Order& order) {
        if (order.qty > 0) {
            std::vector<Order>& orders = (order.side == Side::Buy ? buyOrders : sellOrders);
            auto it = orders.begin();
            for ( ; it != orders.end(); ++it) {
                if ((!order.hasPrice() && (*it).hasPrice()) ||
                    (order.side == Side::Buy && order.price > (*it).price) ||
                    (order.side == Side::Sell && order.price < (*it).price)) {
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
        std::vector<Order>& opposites = (order.side == Side::Buy ? sellOrders : buyOrders);
        while (!opposites.empty() && order.qty > 0 &&
               (!order.hasPrice() ||
                (order.side == Side::Sell && order.price <= opposites[0].price) ||
                (order.side == Side::Buy && order.price >= opposites[0].price))) {
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
        std::vector<Order>& orders = (side == Side::Buy ? buyOrders : sellOrders);
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if ((*it).orderId == orderId) {
                orders.erase(it);
                deleted = true;
                break;
            }
        }
        return deleted;
    }

    void print(const Side side) {
        // Format: "Side: [..., ...]"
        std::vector<Order>& orders = (side == Side::Buy ? buyOrders : sellOrders);
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
    ~OrderBook() = default;

    void addOrder(Order& order) {
        match(order);
        if (order.orderType != OrderType::IOC) {
            insert(order);
        }
    }

    bool deleteOrder(const std::string& orderId) {
        bool deleted = deleteOrder(orderId, Side::Sell);
        if (!deleted) {
            deleted = deleteOrder(orderId, Side::Buy);
        }
        return deleted;
    }

    void print() {
        print(Side::Buy);
        print(Side::Sell);
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
                orderType = OrderType::Limit;
            }
            Order order(orderId, (Side) side, symbol, orderType, std::stoi(price), qty);
            // std::cout << "debug : " << order.toString();
            orderBook.addOrder(order);
            // std::cout << " " << order.toString() << std::endl;
        } else if (action == "CXL") {
            std::cin >> orderId;
            orderBook.deleteOrder(orderId);
        }
        // std::cout << "debug : "; orderBook.print();

        std::cin >> action;
    }

    orderBook.print();
    return 0;
}