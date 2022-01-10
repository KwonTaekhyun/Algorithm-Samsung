#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
    int mNumber;
    int mQuantity;
    int mPrice;
} Order;

vector<vector<Order> > buy_list(6);
vector<vector<Order> > sell_list(6);
vector<vector<int> > trade_list(6);
vector<int> order_list;

void init()
{
    // TC마다 반복
    for (int i = 0; i < 6; i++)
    {
        if (buy_list[i].size() != 0)
        {
            buy_list[i].clear();
        }
        if (sell_list[i].size() != 0)
        {
            sell_list[i].clear();
        }
        if (trade_list[i].size() != 0)
        {
            trade_list[i].clear();
        }
    }

    if (order_list.size() != 0)
    {
        order_list.clear();
    }
    order_list.push_back(0);
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{
    vector<Order> *m_buy_list = &buy_list[mStock];
    vector<Order> *m_sell_list = &sell_list[mStock];
    vector<int> *m_trade_list = &trade_list[mStock];
    Order order = {mNumber, mQuantity, mPrice};

    order_list.push_back(mStock);

    // sell_list가 비어있다면 buy_list에 바로 추가, 단 순서에 유의해 넣기
    if (m_sell_list->size() == 0)
    {
        // sell_list가 비어있는 경우

        if (m_buy_list->size() == 0)
        {
            m_buy_list->push_back(order);
        }
        else
        {
            for (vector<Order>::iterator i = m_buy_list->begin(); i < m_buy_list->end(); i++)
            {
                if (order.mPrice > (*i).mPrice)
                {
                    m_buy_list->insert(i, order);
                    return order.mQuantity;
                }
                else
                {
                    // 항상 주문 번호가 unique하게 증가하므로 이전 주문번호 뒤에 삽입할 수 있다
                    continue;
                }
            }

            m_buy_list->push_back(order);
        }
    }
    else
    {
        // sell_list가 존재하는 경우

        vector<Order>::iterator i = m_sell_list->begin();

        // 가능한 거래 수행
        while ((order.mQuantity != 0) && (order.mPrice >= (*i).mPrice) && (i < m_sell_list->end()))
        {
            if (order.mQuantity >= (*i).mQuantity)
            {
                order.mQuantity -= (*i).mQuantity;
                m_trade_list->push_back((*i).mPrice);

                i = m_sell_list->erase(i);
            }
            else
            {
                (*i).mQuantity -= order.mQuantity;
                m_trade_list->push_back((*i).mPrice);
                order.mQuantity = 0;

                return order.mQuantity;
            }
        }

        // 가능한 거래 완료 && 남은 수량 존재
        if (order.mQuantity != 0)
        {
            for (vector<Order>::iterator i = m_buy_list->begin(); i < m_buy_list->end(); i++)
            {
                if (order.mPrice > (*i).mPrice)
                {
                    m_buy_list->insert(i, order);
                    return order.mQuantity;
                }
                else
                {
                    // 항상 주문 번호가 unique하게 증가하므로 이전 주문번호 뒤에 삽입할 수 있다
                    continue;
                }
            }

            m_buy_list->push_back(order);
        }
    }

    return order.mQuantity;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    vector<Order> *m_buy_list = &buy_list[mStock];
    vector<Order> *m_sell_list = &sell_list[mStock];
    vector<int> *m_trade_list = &trade_list[mStock];
    Order order = {mNumber, mQuantity, mPrice};

    order_list.push_back(mStock);

    if (m_buy_list->size() == 0)
    {
        // buy_list가 비어있다면 sell_list에 바로 추가, 단 순서에 유의해 넣기

        if (m_sell_list->size() == 0)
        {
            m_sell_list->push_back(order);
        }
        else
        {
            for (vector<Order>::iterator i = m_sell_list->begin(); i < m_sell_list->end(); i++)
            {
                if (order.mPrice < (*i).mPrice)
                {
                    m_sell_list->insert(i, order);
                    return order.mQuantity;
                }
                else
                {
                    // 항상 주문 번호가 unique하게 증가하므로 이전 주문번호 뒤에 삽입할 수 있다
                    continue;
                }
            }

            m_sell_list->push_back(order);
        }
    }
    else
    {
        // buy_list가 존재하는 경우

        vector<Order>::iterator i = m_buy_list->begin();

        // 가능한 거래 수행
        while ((order.mQuantity != 0) && (order.mPrice <= (*i).mPrice) && (i < m_buy_list->end()))
        {
            if (order.mQuantity >= (*i).mQuantity)
            {
                order.mQuantity -= (*i).mQuantity;
                m_trade_list->push_back((*i).mPrice);

                i = m_buy_list->erase(i);
            }
            else
            {
                (*i).mQuantity -= order.mQuantity;
                m_trade_list->push_back((*i).mPrice);
                order.mQuantity = 0;

                return order.mQuantity;
            }
        }

        // 가능한 거래 완료 && 남은 수량 존재
        if (order.mQuantity != 0)
        {
            for (vector<Order>::iterator i = m_sell_list->begin(); i < m_sell_list->end(); i++)
            {
                if (order.mPrice < (*i).mPrice)
                {
                    m_sell_list->insert(i, order);
                    return order.mQuantity;
                }
                else
                {
                    // 항상 주문 번호가 unique하게 증가하므로 이전 주문번호 뒤에 삽입할 수 있다
                    continue;
                }
            }

            m_sell_list->push_back(order);
        }
    }

    return order.mQuantity;
}

void cancel(int mNumber)
{
    int mStock = order_list[mNumber];

    vector<Order> *m_buy_list = &buy_list[mStock];
    vector<Order> *m_sell_list = &sell_list[mStock];

    for (vector<Order>::iterator i = m_buy_list->begin(); i < m_buy_list->end(); i++)
    {
        if ((*i).mNumber == mNumber)
        {
            m_buy_list->erase(i);
            return;
        }
        else
        {
            continue;
        }
    }
    for (vector<Order>::iterator i = m_sell_list->begin(); i < m_sell_list->end(); i++)
    {
        if ((*i).mNumber == mNumber)
        {
            m_sell_list->erase(i);
            return;
        }
        else
        {
            continue;
        }
    }
}

int bestProfit(int mStock)
{
    vector<int> *m_trade_list = &trade_list[mStock];
    int BP = 0;
    int min = trade_list[mStock][0];

    for (vector<int>::iterator i = m_trade_list->begin(); i < m_trade_list->end(); i++)
    {
        if ((*i) < min)
        {
            min = *i;
        }
        else if (BP < ((*i) - min))
        {
            BP = (*i) - min;
        }
        else
        {
            continue;
        }
    }

    return BP;
}