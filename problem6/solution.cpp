// #include <iostream>
#define MAX_NODE 10000

struct Node {
  int data;
  Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
  node[nodeCnt].data = data;
  node[nodeCnt].next = nullptr;
  return &node[nodeCnt++];
}

void init() {
  nodeCnt = 0;
  node[nodeCnt].next = nullptr;
  head = &node[nodeCnt];
  nodeCnt++;
}

void addNode2Head(int data) {
  node[nodeCnt].data = data;
  node[nodeCnt].next = head->next;
  head->next = &node[nodeCnt];
  nodeCnt++;
}

void addNode2Tail(int data) {
  Node* ptr = head;

  while (ptr->next) {
    ptr = ptr->next;
  }

  node[nodeCnt].data = data;
  node[nodeCnt].next = nullptr;
  ptr->next = &node[nodeCnt];
  nodeCnt++;
}

void addNode2Num(int data, int num) {
  Node* ptr = head;

  for (int i = 1; i < num; i++) {
    if (ptr->next == nullptr) {
      return;
    }
    ptr = ptr->next;
  }

  node[nodeCnt].data = data;
  node[nodeCnt].next = ptr->next;
  ptr->next = &node[nodeCnt];
  nodeCnt++;
}

void removeNode(int data) {
  Node* ptr = head;

  while (ptr->next) {
    if (ptr->next->data == data) {
      break;
    }
    ptr = ptr->next;
  }

  if (ptr->next != nullptr && ptr->next->data == data) {
    ptr->next = ptr->next->next;
  }
}

int getList(int output[MAX_NODE]) {
  int i = 0;
  for (Node* ptr = head->next; ptr != nullptr; ptr = ptr->next) {
    output[i++] = ptr->data;
  }
  return i;
}