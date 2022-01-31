#define MAX_NODE 10000

struct Node {
  int data;
  Node* prev;
  Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
  node[nodeCnt].data = data;
  node[nodeCnt].prev = nullptr;
  node[nodeCnt].next = nullptr;
  return &node[nodeCnt++];
}

void init() {
  nodeCnt = 0;
  node[nodeCnt].prev = nullptr;
  node[nodeCnt].next = nullptr;
  head = &node[nodeCnt];
  nodeCnt++;
}

void addNode2Head(int data) {
  node[nodeCnt].data = data;
  node[nodeCnt].prev = head;
  node[nodeCnt].next = head->next;
  if (node[nodeCnt].next != nullptr) {
    node[nodeCnt].next->prev = &node[nodeCnt];
  }
  head->next = &node[nodeCnt];
  nodeCnt++;
}

void addNode2Tail(int data) {
  Node* ptr = head;

  while (ptr->next) {
    ptr = ptr->next;
  }

  node[nodeCnt].data = data;
  node[nodeCnt].prev = ptr;
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
  node[nodeCnt].prev = ptr;
  node[nodeCnt].next = ptr->next;
  if (node[nodeCnt].next != nullptr) {
    node[nodeCnt].next->prev = &node[nodeCnt];
  }
  ptr->next = &node[nodeCnt];
  nodeCnt++;
}

int findNode(int data) {
  Node* ptr = head->next;

  int i = 1;
  while (ptr) {
    if (ptr->data == data) {
      break;
    }
    i++;
    ptr = ptr->next;
  }

  if (ptr != nullptr && ptr->data == data) {
    return i;
  } else {
    return 0;
  }
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
    Node* tmp = ptr->next;

    ptr->next = tmp->next;

    if (ptr->next != nullptr) {
      ptr->next->prev = ptr;
    }
  }
}

int getList(int output[MAX_NODE]) {
  int i = 0;
  for (Node* ptr = head->next; ptr != nullptr; ptr = ptr->next) {
    output[i++] = ptr->data;
  }
  return i;
}

int getReversedList(int output[MAX_NODE]) {
  Node* ptr = head;

  while (ptr->next) {
    ptr = ptr->next;
  }

  int i = 0;
  for (; ptr != head; ptr = ptr->prev) {
    output[i++] = ptr->data;
  }
  return i;
}