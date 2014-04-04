#ifndef TRIE_HPP_96C08F53_5BC8_4B0D_AEE9_188291ED1D25
#define TRIE_HPP_96C08F53_5BC8_4B0D_AEE9_188291ED1D25

#include<set>
#include<vector>
#include<functional>
#include<algorithm>

namespace MNB {

template<typename T, typename V, typename Cmp,typename Items>
class Node;

template<typename T, typename V, typename Cmp, typename Items>
class NodeItem {
  private:
    typedef Node<T, V, Cmp, Items> NodeKlass;
    typedef NodeItem<T, V, Cmp, Items> NodeItemKlass;

  public:
    NodeItem(const T& endSymbol, const T& key)
      : endSymbol_(endSymbol), key_(key), pChilds_(nullptr) {}

    virtual ~NodeItem() { delete pChilds_; }

    bool operator<(const NodeItemKlass& rhs) const {
      return Cmp()(this->key_, rhs.key_);
    }

    bool operator<(const T& rhskey) const {
      return Cmp()(this->key_, rhskey);
    }

    bool operator==(const NodeItemKlass& rhs) const {
      return !Cmp()(this->key_, rhs.key_) && !Cmp()(rhs.key_, this->key_);
    } 

    bool operator==(const T& rhskey) const {
      return !Cmp()(this->key_, rhskey) && !Cmp()(rhskey, this->key_);
    }

    bool operator!=(const NodeKlass& rhs) const {
      return !(*this == rhs);
    }

    bool operator!=(const T& rhsKey) const {
      return !(*this == rhsKey);
    }

    void set(const T& key) {
      key_ = key;
    }
    const T& get() const {
      return key_;
    }

    const NodeKlass* getChilds() const {
      return pChilds_;
    }

    NodeKlass* getChilds() {
      return pChilds_;
    }

    NodeKlass* getOrMakeChilds(NodeKlass* pParent) {
      makeChilds(pParent);
      return pChilds_;
    }

  private:
    void makeChilds(NodeKlass* pParent) {
      if (!pChilds_) {
        pChilds_ = new NodeKlass(endSymbol_, pParent);
      }
    }
    //DISALLOW_COPY_AND_ASSIGN(NodeItem);

  private:
    T endSymbol_;
    T key_;
    NodeKlass* pChilds_;
};

template<typename T, typename V, typename Cmp, typename Items>
class EndNodeItem : public NodeItem<T, V, Cmp, Items> {
  private:
    typedef NodeItem<T, V, Cmp, Items> ParentKlass;

  public:
    EndNodeItem(const T& endSymbol, const T& key)
      : ParentKlass(endSymbol, key) {}
    EndNodeItem(const T& endSymbol, const T& key, const V& val)
      : ParentKlass(endSymbol, key),
      value_(val) {}

    void set(const T& key, const V& val) {
      ParentKlass::set(key);
      value_ = val;
    }

    const V& getValue() const {
      return value_;
    }

  private:
    //DISALLOW_COPY_AND_ASSIGN(EndNodeItem);
  private:
    V value_;
};

template<typename T, typename V, typename Cmp, typename Items>
class NodeItemPtrCmp {
  private:
    typedef NodeItem<T, V, Cmp, Items> NodeItemKlass;

  public:
    bool operator()(const NodeItemKlass* pLHS, const NodeItemKlass* pRHS) const {
      return *pLHS < *pRHS;
    }
};

template<typename T, typename V, typename Cmp, typename Items>
class Node {
  public:
    typedef NodeItem<T, V, Cmp, Items> NodeItemKlass;
    typedef EndNodeItem<T, V, Cmp, Items> EndNodeItemKlass;
    typedef Node<T, V, Cmp, Items> NodeKlass;

  public:
    class ConstIterator {
      private:
        typedef std::pair<const T*, const V*> KeyValuePair;
        typedef typename NodeKlass::ItemContainerConstIter ItemContainerConstIter;

      public:
        ConstIterator(const NodeKlass* pNode, const NodeKlass* pRoot, const T* key = nullptr, bool moveToEnd = false)
          : pRootNode_(pRoot), pCurrentNode_(pNode), checkLeft_(false), checkRight_(false),
          endReached_(false) {
            if (!pRoot) {
              pRootNode_ = pNode;
            }
            pushNode(pNode, key, moveToEnd);
            if (!moveToEnd) {
              this->next();
            }
          }
        ConstIterator(const ConstIterator& rhs)
          : pRootNode_(rhs.pRootNode_), pCurrentNode_(rhs.pCurrentNode_), currentPos_(rhs.currentPos_),
          keyStack_(rhs.keyStack_), checkLeft_(rhs.checkLeft_), checkRight_(rhs.checkRight_), endReached_(rhs.endReached_) {
            if (!keyStack_.empty() ) {
              keyValuePair_ = std::make_pair(&keyStack_[0], rhs.keyValuePair_.second);
            }
          }

        ConstIterator& operator=(const ConstIterator& rhs) {
          if (this != &rhs) {
            pRootNode_ = rhs.pRootNode_;
            pCurrentNode_ = rhs.pCurrentNode_;
            currentPos_ = rhs.currentPos_;
            checkLeft_ = rhs.checkLeft_;
            checkRight_ = rhs.checkRight_;
            endReached_ = rhs.endReached_;
            if (!keyStack_.empty() ) {
              keyValuePair_ = std::make_pair(&keyStack_[0], rhs.keyValuePair_.second);
            }
          }
        }

        const KeyValuePair& operator*() const {
          return this->keyValuePair_;
        }

        const KeyValuePair* operator->() const {
          return &(this->keyValuePair_);
        }

        bool operator==(const ConstIterator& rhs) const {
          return this->equal(rhs);
        }

        bool operator!=(const ConstIterator& rhs) const {
          return !(*this == rhs);
        }

        ConstIterator operator++(int) {
          ConstIterator iter = *this;
          ++(*this);
          return iter;
        }

        ConstIterator& operator++() {
          this->next();
          return *this;
        }

        ConstIterator operator--(int) {
          ConstIterator iter = *this;
          --(*this);
          return iter;
        }

        ConstIterator& operator--() {
          this->prev();
          return *this;
        }
      private:
        bool isEnd() const {
          return (pRootNode_ == pCurrentNode_
              && currentPos_ == pCurrentNode_->items_.end() );
        }

        bool isLeftmost() const {
          return pRootNode_ == pCurrentNode_
            && currentPos_ == pCurrentNode_->items_.begin();
        }

        bool equal(const ConstIterator& rhs) const {
          if (isEnd() && rhs.isEnd() ) {
            return true;
          }
          if (pCurrentNode_ == rhs.pCurrentNode_ && currentPos_ == rhs.currentPos_) {
            return true;
          }
          return false;
        }

        void pushNode(const NodeKlass* pNode, const T* key = nullptr, bool moveToEnd=false) {
          pCurrentNode_ = pNode;
          checkLeft_ = false;
          if (moveToEnd) {
            currentPos_ = pCurrentNode_->items_.end();
            endReached_ = true;
            checkRight_ = false;
          }
          else {
            if (key) {
              for (int i = 0; key[i] != pNode->endSymbol(); ++i) {
                keyStack_.push_back(key[i]);
              }
            }
            currentPos_ = pNode->items_.begin();
            checkRight_ = true;
          }
        }

        void prev() {
          if (!pCurrentNode_->items_.empty() && currentPos_ == pCurrentNode_->items_.end() ) {
            --currentPos_;
          }
          bool newNode = false;
          bool oldNode = false;
          while(endReached_ || isLeftmost() ) {
            endReached_ = false;
            ItemContainerConstIter iterBegin = pCurrentNode_->items_.begin();
            if (!keyStack_.empty() ) {
              if (keyStack_.back() == pCurrentNode_->endSymbol() ) {
                keyStack_.pop_back();
                currentPos_ = pCurrentNode_->items_.begin();
                if (isLeftmost() ) {
                  break;
                }
              }
            }
            if (!newNode && !keyStack_.empty() ) {
              if (checkLeft_) {
                  pCurrentNode_ = pCurrentNode_->parent();
                  currentPos_ = pCurrentNode_->items_.find(keyStack_.back());
                  iterBegin = pCurrentNode_->items_.begin();
                  keyStack_.pop_back();
                  checkLeft_ = false;
                  if (currentPos_ != iterBegin) {
                      --currentPos_;
                      oldNode = false;
                  } else {
                      oldNode = true;
                  }
              }
              else {
                ItemContainerConstIter iter = pCurrentNode_->items_.find(pCurrentNode_->endSymbol());
                if (iter != pCurrentNode_->items_.end()) {
                    currentPos_ = iter;
                    const NodeItemKlass& item = *(const NodeItemKlass *)(*currentPos_);
                    keyStack_.push_back(item.get());
                    keyValuePair_.first = &(keyStack_[0]);
                    keyValuePair_.second = &(((const EndNodeItemKlass &)item).getValue());
                    checkLeft_ = true;
                    return;
                } else {
                    pCurrentNode_ = pCurrentNode_->parent();
                    currentPos_ = pCurrentNode_->items_.find(keyStack_.back());
                    iterBegin = pCurrentNode_->items_.begin();
                    keyStack_.pop_back();
                    checkLeft_ = false;
                    if (currentPos_ != iterBegin) {
                        --currentPos_;
                        oldNode = false;
                    } else {
                        oldNode = true;
                    }
                }
              }
            }
            newNode = false;
            for (; currentPos_ != iterBegin; --currentPos_) {
                if (*currentPos_) {
                    const NodeItemKlass &item = *(const NodeItemKlass *) *currentPos_;
                    if (item != pCurrentNode_->endSymbol()) {
                        keyStack_.push_back(item.get());
                        pushNode(item.getChilds(), 0, true);
                        --currentPos_;
                        newNode = true;
                        break;
                    }
                }
                oldNode = false;
            }
            if (!newNode && !oldNode) {
              if (currentPos_ != pCurrentNode_->items_.end()) {
                if (*currentPos_) {
                  const NodeItemKlass &item = *(const NodeItemKlass *) *currentPos_;
                  if (item != pCurrentNode_->endSymbol()) {
                    keyStack_.push_back(item.get());
                    pushNode(item.getChilds(), 0, true);
                    --currentPos_;
                    newNode = true;
                  }
                }
              }
            }
          }
          currentPos_ = pCurrentNode_->items_.end();
          endReached_ = true;
        }

        void next() {
          while(!isEnd() ) {
            ItemContainerConstIter itEnd = pCurrentNode_->items_.end();
            if (!keyStack_.empty() && keyStack_.back() == pCurrentNode_->endSymbol() ) {
              keyStack_.pop_back();
              currentPos_ = pCurrentNode_->items_.begin();
            }
            if (currentPos_ == itEnd && !keyStack_.empty() ) {
              pCurrentNode_ = pCurrentNode_->parent();
              currentPos_ = pCurrentNode_->items_.find(keyStack_.back() );
              keyStack_.pop_back();
              itEnd = pCurrentNode_->items_.end();
              ++currentPos_;
            }
            for(; currentPos_ != itEnd; ++currentPos_) {
              if (checkRight_) {
                checkRight_ = false;
                ItemContainerConstIter endSymbolIter = pCurrentNode_->items_.find(pCurrentNode_->endSymbol() );
                if (endSymbolIter != itEnd) {
                  currentPos_ = endSymbolIter;
                  const NodeItemKlass& item = *(const NodeItemKlass*) *currentPos_;
                  keyStack_.push_back(item.get() );
                  keyValuePair_.first = &(keyStack_[0]);
                  keyValuePair_.second = &(((const EndNodeItemKlass&)item).getValue());
                  checkLeft_ = true;
                  return;
                }
              }
              if(*currentPos_) {
                const NodeItemKlass& curItem = *(NodeItemKlass*) *currentPos_;
                if (curItem != pCurrentNode_->endSymbol() ) {
                  keyStack_.push_back(curItem.get() );
                  pushNode(curItem.getChilds() );
                  break;
                }
              }
            }
          }
          endReached_ = true;
        }
      private:
        friend class Node<T, V, Cmp, Items>;
        const NodeKlass* pRootNode_;
        const NodeKlass* pCurrentNode_;
        ItemContainerConstIter currentPos_;
        bool checkLeft_;
        bool checkRight_;
        bool endReached_;
        std::vector<T> keyStack_;
        KeyValuePair keyValuePair_;
    };

    class Iterator : public ConstIterator {
      private:
        typedef std::pair<const T*, V*> MutableKeyValuePair;

      public:
        Iterator(NodeKlass* nodePtr, NodeKlass* rootPtr, const T* key, bool moveToEnd=false)
          : ConstIterator(nodePtr, rootPtr, key, moveToEnd) {}
        MutableKeyValuePair& operator*() {
          return getPair();
        }

        MutableKeyValuePair* operator->() {
          return &(getPair() );
        }

        Iterator operator++(int) {
          Iterator iter = this;
          ++(*this);
          return *this;
        }

        Iterator& operator++() {
          this->next();
          return *this;
        }

        Iterator operator--(int) {
          Iterator iter = this;
          --(*this);
          return *this;
        }

        Iterator& operator--() {
          this->prev();
          return *this;
        }

      private:
        MutableKeyValuePair& getPair() {
          mutableKV_.first = this->keyValuePair_.first;
          mutableKV_.second = const_cast<V*>(this->keyValuePair_.second);
          return mutableKV_;
        }

      private:
        MutableKeyValuePair mutableKV_;
    };

  public:
    Node(const T& endSymbol, NodeKlass* parentNodePtr = nullptr)
      :items_(endSymbol), endSymbol_(endSymbol), size_(0),
      pParent_(parentNodePtr) {}

    ~Node() {
      clear();
    }

    T endSymbol() const {
      return endSymbol_;
    }

    void clear() {
      std::for_each(items_.begin(), items_.end(), ItemDeleter);
      items_.clear();
      size_ = 0;
    }

    bool empty() const {
      return items_.size() == 0U;
    }

    int size() const {
      return size_;
    }

    std::pair<Iterator, bool> insert(const T* key, const V& val) {
      std::pair<Iterator, bool> rv(end(), false);
      int i = 0;
      NodeKlass* nodePtr = this;
      while(true) {
        std::pair<typename Items::Item*, bool> itemPair = nodePtr->items_.insertItem(key[i]);
        NodeItemKlass* itemPtr = itemPair.first;
        if (itemPair.second) {
          rv.first = Iterator(nodePtr, this, key);
          break;
        }
        if (!itemPtr) {
          break;
        } else if (key[i] == endSymbol_) {
          ((EndNodeItemKlass*)itemPtr)->set(key[i], val);
          rv.first = Iterator(nodePtr, this, key);
          rv.second = true;
          ++size_;
          break;
        } else {
          nodePtr = itemPtr->getOrMakeChilds(nodePtr);
        }
        ++i;
      }
      return rv;
    }

    bool erase(Iterator pos) {
      bool rv = false;
      if (pos.pCurrentNode_ && pos.currentPos_ != pos.pCurrentNode_->items_.end() ) {
        rv = erase(const_cast<NodeKlass*>(pos.pCurrentNode_), pos->first);
      }
      return rv;
    }

    bool erase(const T* key) {
      NodeKlass* nodePtr = nodeWithKey(key);
      bool rv = false;
      if (nodePtr) {
        rv = erase(nodePtr, key);
      }
      return rv;
    }

    const V* get(const T* key) const {
      return const_cast<NodeKlass*>(this)->get(key);
    }

    V* get(const T* key) {
      NodeKlass* nodePtr = nodeWithKey(key);
      if (nodePtr) {
        NodeItemKlass* itemPtr = nodePtr->items_.getItem(endSymbol_);
        return &((EndNodeItemKlass*)itemPtr)->getValue();
      }
      return nullptr;
    }

    bool hasKey(const T* key) const {
      return get(key) != nullptr;
    }

    const NodeKlass* parent() const {
      return pParent_;
    }

    NodeKlass* parent() {
      return pParent_;
    }

    ConstIterator begin() const {
      return ConstIterator(this, this);
    }

    ConstIterator end() const {
      return ConstIterator(this, this, nullptr, true);
    }

    Iterator begin() {
      return Iterator(this, this);
    }

    Iterator end() {
      return Iterator(this, this, nullptr, true);
    }

    ConstIterator find(const T* key) const {
      NodeKlass* nodePtr = const_cast<NodeKlass*>(this)->nodeWithKey(key);
      if (!nodePtr) {
        return ConstIterator(this, this, nullptr, true);
      }
      else {
        return ConstIterator(nodePtr, this, key);
      }
    }

    Iterator find(const T* key) {
      NodeKlass * nodePtr = this->nodeWithKey(key);
      if (!nodePtr) {
          return Iterator(this, this, 0, true);
      } else {
          return Iterator(nodePtr, this, key);
      }
    }

    ConstIterator startWith(const T* prefix) const {
      const NodeKlass* nodePtr = const_cast<NodeKlass*>(this)->nodeWithKey(prefix);
      if (!nodePtr) {
        return ConstIterator(this, this, nullptr, true);
      }
      else {
        return ConstIterator(nodePtr, nodePtr, prefix);
      }
    }

    Iterator startWith(const T* prefix) {
      const NodeKlass* nodePtr = const_cast<NodeKlass*>(this)->nodeWithKey(prefix);
      if (!nodePtr) {
        return Iterator(this, this, nullptr, true);
      }
      else {
        return Iterator(const_cast<NodeKlass*>(nodePtr), const_cast<NodeKlass*>(nodePtr), prefix);
      }
    }

  private:
    static void ItemDeleter(NodeItemKlass* itemPtr) {
      delete itemPtr;
    }

    NodeKlass* nodeWithKey(const T* key) {
      return const_cast<NodeKlass*>(const_cast<NodeKlass*>(this)->nodeWithKey(key));
    }

    const NodeKlass* nodeWithKey(const T* key) const {
      const NodeKlass* nodePtr = nodeWithPrefix(key);
      if (nodePtr && nodePtr->items_.getItem(endSymbol_) ) {
        return nodePtr;
      }
      return nullptr;
    }

    const NodeKlass* nodeWithPrefix(const T *prefix) const {
        int i=0;
        const NodeKlass * nodePtr = this;

        while (nodePtr) {
            if (prefix[i] == endSymbol_) {
                return nodePtr;
            }
            const NodeItemKlass *itemPtr = nodePtr->items_.getItem(prefix[i]);
            if (!itemPtr) {
                break;
            }

            nodePtr = itemPtr->getChilds();
            ++i;
        }
        return 0;
    }

    bool erase(NodeKlass* nodePtr, const T* key) {
        bool erased = false;
        int keyIndex = 0;

        if (nodePtr && key) {
            bool finished = false;
            int count = 0;
            erased = true;

            if (!keyIndex) {
                while (key[keyIndex] != nodePtr->endSymbol()) {
                    ++ keyIndex;
                }
            }

            while (nodePtr && !finished && erased) {
                ItemContainerIter iterEnd = nodePtr->items_.end();

                count = 0;
                for (ItemContainerIter iter = nodePtr->items_.begin(); iter != iterEnd; ++iter) {
                    if (*iter != 0) {
                        ++count;
                    }
                }

                if (count > 1) {
                    erased = nodePtr->items_.eraseItem(key[keyIndex]);
                    finished = true;
                } else if (count == 1) {
                    erased = nodePtr->items_.eraseItem(key[keyIndex]);
                }

                --keyIndex;
                nodePtr = nodePtr->parent();
            }

        }
        if (erased) {
            --size_;
        }
        return erased;
    }

    //DISALLOW_COPY_AND_ASSIGN(Node);
  private:
    typedef typename Items::iterator ItemContainerIter;
    typedef typename Items::const_iterator ItemContainerConstIter;

    Items items_;
    const T endSymbol_;
    int size_;
    NodeKlass* pParent_;
};

template<typename T, typename V, typename Cmp>
class SetItems {
  public:
    typedef NodeItem<T, V, Cmp, SetItems<T, V, Cmp>> Item;
    typedef std::set<Item*, NodeItemPtrCmp<T, V, Cmp, SetItems<T, V, Cmp>>> Items;
    typedef typename Items::iterator iterator;
    typedef typename Items::const_iterator const_iterator;
    typedef Node<T, V, Cmp, SetItems<T, V, Cmp>> NodeKlass;
    typedef typename NodeKlass::NodeItemKlass NodeItemKlass;
    typedef typename NodeKlass::EndNodeItemKlass EndNodeItemKlass;

  public:
    SetItems(const T& endSymbol)
      : endSymbol_(endSymbol) {}

    const_iterator find(const T& key) const {
      return const_cast<SetItems<T, V, Cmp>* >(this)->find(key);
    }

    iterator find(const T& key) {
      Item tmp(endSymbol_, key);
      return items_.find(&tmp);
    }

    iterator begin() {
      return items_.begin();
    }

    const_iterator begin() const {
      return items_.begin();
    }

    iterator end() {
      return items_.end();
    }

    const_iterator end() const {
      return items_.end();
    }

    bool isEmpty() const {
      return items_.isEmpty();
    }

    void clear() {
      return items_.clear();
    }

    std::pair<Item*, bool> insertItem(const T& key) {
      std::pair<Item*, bool> rv(nullptr, false);
      Item tmp(endSymbol_, key);
      iterator iter = items_.find(&tmp);
      if (iter == items_.end() ) {
        Item* v = createNodeItem(key);
        items_.insert(v);
        rv.first = v;
      }
      else {
        rv.first = (Item*)(*iter);
        if (key == endSymbol_) {
          rv.second = true;
        }
      }
      return rv;
    }

    const Item* getItem(const T& key) const {
      return const_cast<SetItems*>(this)->getItem(key);
    }

    Item* getItem(const T& key) {
      Item tmp(endSymbol_, key);
      iterator iter = items_.find(&tmp);
      if (iter == items_.end() ) {
        return nullptr;
      }
      return (Item*)(*iter);
    }

    NodeItemKlass* createNodeItem(const T& key) {
      if (key == endSymbol_) {
        return new NodeItemKlass(endSymbol_, key);
      }
      else {
        return new NodeItemKlass(endSymbol_, key);
      }
    }

  private:
    const T endSymbol_;
    Items items_;
};

template<typename T, typename V,
  typename Cmp = std::less<T>, typename Items = SetItems<T, V, Cmp>>
class Trie {
  public:
    typedef typename Node<T, V, Cmp, Items>::Iterator Iterator;
    typedef typename Node<T, V, Cmp, Items>::ConstIterator ConstIterator;

  public:
    /*
     * @param endSymbol: mark the end of key input
     */
    Trie(const T& endSymbol)
      :root_(endSymbol) {}

    /*
     * @param key:inserted key which should be termiated by end symbol
     * @param vlaue: 
     * @return pair::first set to the Iterator points to the element and pair::second to true is
     * key is newly inserted, false otherwise
     */
    std::pair<Iterator, bool>
      insert(const T* key, const V& value) {
        return root_.insert(key, value);
      }

    bool erase(const T* key) {
      return root_.erase(key);
    }

    const V* get(const T* key) const {
      return root_.get(key);
    }

    V* get(const T* key) {
      return root_.get(key);
    }

    V& operator[](const T* key) {
      return *(insert(key, V()).first->second);
    }

    bool hasKey(const T* key) {
      return root_.hasKey(key);
    }

    bool isEmpty() const {
      return root_.isEmpty();
    }

    int size() const {
      return root_.size();
    }

    void clear() {
      return root_.clear();
    }

    /*
     * Retrieve Iterator to the elements with common prefix
     * @param prefix: part of the key which should be searched, should be termiated by end symbol
     */
    Iterator startWith(const T* prefix) {
      return root_.startWith(prefix);
    }

    ConstIterator startWith(const T* prefix) const {
      return root_.startWith(prefix);
    }

    T endSymbol() const {
      return root_.endSymbol();
    }

    Iterator begin() {
      return root_.begin();
    }
    
    ConstIterator begin() const {
      return root_.begin();
    }

    Iterator end() {
      return root_.end();
    }

    ConstIterator end() const {
      return root_.end();
    }

    Iterator find(const T* key) {
      return root_.find(key);
    }

    ConstIterator find(const T* key) const {
      return root_.find(key);
    }

  private:
    //DISALLOW_COPY_AND_ASSIGN(Trie);

  private:
    Node<T, V, Cmp, Items> root_;
};

}

#endif /* TRIE_HPP_96C08F53_5BC8_4B0D_AEE9_188291ED1D25 */

//http://stackoverflow.com/questions/794601/prefix-search-in-a-radix-tree-patricia-trie
//https://code.google.com/p/patl/source/browse/#svn%2Ftrunk%2Fuxn%2Fpatl
