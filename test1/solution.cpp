#include <stdio.h>

#include <climits>
#include <deque>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef struct {
  int mNumber;
  int mQuantity;
  int mPrice;
} Order;

typedef struct {
  int mStock;
  bool isBuy;
  int mPrice;
} Header;

vector<multimap<int, Order, greater<int>>> buy_list(6);
vector<multimap<int, Order>> sell_list(6);

map<int, Header> header_map;

int BP[6];
int minPrice[6];

void init() {
  // TC마다 반복
  for (int i = 0; i < 6; i++) {
    if (buy_list[i].size() != 0) {
      buy_list[i].clear();
    }
    if (sell_list[i].size() != 0) {
      sell_list[i].clear();
    }
  }

  for (int i = 0; i < 6; i++) {
    BP[i] = 0;
    minPrice[i] = INT_MAX;
  }

  if (header_map.size() != 0) {
    header_map.clear();
  }
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice) {
  multimap<int, Order, greater<int>> *m_buy_list = &buy_list[mStock];
  multimap<int, Order> *m_sell_list = &sell_list[mStock];
  Order order = {mNumber, mQuantity, mPrice};

  Header header;
  header.mStock = mStock;
  header.isBuy = true;
  header.mPrice = mPrice;

  // sell_list가 비어있다면 buy_list에 바로 추가, 단 순서에 유의해 넣기
  if (m_sell_list->size() == 0) {
    // sell_list가 비어있는 경우

    header_map.insert(make_pair(mNumber, header));
    m_buy_list->insert(make_pair(mPrice, order));

    return order.mQuantity;

  } else {
    // sell_list가 존재하는 경우

    multimap<int, Order>::iterator i = m_sell_list->begin();

    // 가능한 거래 수행
    while ((order.mQuantity != 0) && (order.mPrice >= (*i).second.mPrice) &&
           (i != m_sell_list->end())) {
      if (order.mQuantity >= (*i).second.mQuantity) {
        order.mQuantity -= (*i).second.mQuantity;
        // m_trade_list->push_back((*i).mPrice);
        if ((*i).second.mPrice < minPrice[mStock]) {
          minPrice[mStock] = (*i).second.mPrice;
        } else if (BP[mStock] < ((*i).second.mPrice - minPrice[mStock])) {
          BP[mStock] = (*i).second.mPrice - minPrice[mStock];
        }

        header_map.erase((*i).second.mNumber);
        m_sell_list->erase(i);
        i = m_sell_list->begin();
      } else {
        (*i).second.mQuantity -= order.mQuantity;
        // m_trade_list->push_back((*i).mPrice);
        if ((*i).second.mPrice < minPrice[mStock]) {
          minPrice[mStock] = (*i).second.mPrice;
        } else if (BP[mStock] < ((*i).second.mPrice - minPrice[mStock])) {
          BP[mStock] = (*i).second.mPrice - minPrice[mStock];
        }
        order.mQuantity = 0;

        return order.mQuantity;
      }
    }

    // 가능한 거래 완료 && 남은 수량 존재
    if (order.mQuantity != 0) {
      header_map.insert(make_pair(mNumber, header));
      m_buy_list->insert(make_pair(mPrice, order));
    }

    return order.mQuantity;
  }
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice) {
  multimap<int, Order, greater<int>> *m_buy_list = &buy_list[mStock];
  multimap<int, Order> *m_sell_list = &sell_list[mStock];
  Order order = {mNumber, mQuantity, mPrice};

  Header header;
  header.mStock = mStock;
  header.isBuy = false;
  header.mPrice = mPrice;

  if (m_buy_list->size() == 0) {
    // buy_list가 비어있다면 sell_list에 바로 추가, 단 순서에 유의해 넣기
    header_map.insert(make_pair(mNumber, header));
    m_sell_list->insert(make_pair(mPrice, order));
    return order.mQuantity;
  } else {
    // buy_list가 존재하는 경우

    multimap<int, Order, greater<int>>::iterator i = m_buy_list->begin();

    // 가능한 거래 수행
    while ((order.mQuantity != 0) && (order.mPrice <= (*i).second.mPrice) &&
           (i != m_buy_list->end())) {
      if (order.mQuantity >= (*i).second.mQuantity) {
        order.mQuantity -= (*i).second.mQuantity;
        // m_trade_list->push_back((*i).mPrice);
        if ((*i).second.mPrice < minPrice[mStock]) {
          minPrice[mStock] = (*i).second.mPrice;
        } else if (BP[mStock] < ((*i).second.mPrice - minPrice[mStock])) {
          BP[mStock] = (*i).second.mPrice - minPrice[mStock];
        }

        header_map.erase((*i).second.mNumber);
        m_buy_list->erase(i);
        i = m_buy_list->begin();
        // i = m_buy_list->erase(i);
      } else {
        (*i).second.mQuantity -= order.mQuantity;
        // m_trade_list->push_back((*i).mPrice);
        if ((*i).second.mPrice < minPrice[mStock]) {
          minPrice[mStock] = (*i).second.mPrice;
        } else if (BP[mStock] < ((*i).second.mPrice - minPrice[mStock])) {
          BP[mStock] = (*i).second.mPrice - minPrice[mStock];
        }
        order.mQuantity = 0;

        return order.mQuantity;
      }
    }

    // 가능한 거래 완료 && 남은 수량 존재
    if (order.mQuantity != 0) {
      header_map.insert(make_pair(mNumber, header));
      m_sell_list->insert(make_pair(mPrice, order));
    }

    return order.mQuantity;
  }
}

void cancel(int mNumber) {
  if (header_map.find(mNumber) == header_map.end()) {
    return;
  }
  Header header = (*(header_map.find(mNumber))).second;

  if (header.isBuy) {
    multimap<int, Order, greater<int>> *m_list = &buy_list[header.mStock];

    if (m_list->empty()) {
      return;
    }

    multimap<int, Order, greater<int>>::iterator start;
    multimap<int, Order, greater<int>>::iterator end;
    multimap<int, Order, greater<int>>::iterator mid;
    multimap<int, Order, greater<int>>::iterator i;

    // start(lower_bound)
    start = m_list->lower_bound(header.mPrice);
    // end(upper_bound)
    end = m_list->upper_bound(header.mPrice);
    // binary search (start-end)
    if (start == end) {
      if ((*(start)).second.mNumber == mNumber) {
        m_list->erase(start);
      }
    } else {
      for (i = start; i != end; ++i) {
        if ((*(start)).second.mNumber == mNumber) {
          m_list->erase(start);
          break;
        }
      }
      return;
    }
  } else {
    multimap<int, Order> *m_list = &sell_list[header.mStock];

    if (m_list->empty()) {
      return;
    }

    multimap<int, Order>::iterator start;
    multimap<int, Order>::iterator end;
    multimap<int, Order>::iterator mid;
    multimap<int, Order>::iterator i;

    // start(lower_bound)
    start = m_list->lower_bound(header.mPrice);
    // end(upper_bound)
    end = m_list->upper_bound(header.mPrice);
    // binary search (start-end)
    if (start == end) {
      if ((*(start)).second.mNumber == mNumber) {
        m_list->erase(start);
      }
    } else {
      for (i = start; i != end; ++i) {
        if ((*(start)).second.mNumber == mNumber) {
          m_list->erase(start);
          break;
        }
      }
      return;
    }
  }
}

int bestProfit(int mStock) { return BP[mStock]; }