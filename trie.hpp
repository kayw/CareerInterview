#ifndef TRIE_HPP_96C08F53_5BC8_4B0D_AEE9_188291ED1D25
#define TRIE_HPP_96C08F53_5BC8_4B0D_AEE9_188291ED1D25

#include<functional>

template<typename T, typename V, typename Cmp>
class SetItems {
  public:
    typedef NodeItem<T, V, Cmp, SetItems<T, V, Cmp>> Item;
    typedef std::set<Item*, NodeItemPtrCmp<T, V, Cmp, SetItems<T, V, Cmp>> Items;
    typedef typename Items::iterator iterator;
    typedef typename Items::const_iterator const_iterator;
    typedef Node<T, V, Cmp, SetItems<T, V, Cmp>> NodeKlass;
    typedef NodeKlass::NodeItemKlass NodeItemKlass;
    typedef typename NodeKlass::EndNoteItemKlass EndNoteItemKlass;

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
      std::pair<Item*, bol> rv(nullptr, false);
      Item tmp(endSymbol_, key);
      iterator iter = items_.find(&tmp);
      if (iter == items_.end() ) {
        Item* v = createNodeItem(key);
        items_.insert(v);
        rv.first = v;
      }
      else {
        rv.first = (Item*)(*iter);
        if (key == endSymbol) {
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

    ConstIterator startWith(const T* prefix) {
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

    ConstIterator find(const T* key) {
      return root_.find(key);
    }

  private:
    DISALLOW_COPY_AND_ASSIGN(Trie);

  private:
    Node<T, V, Cmp, Items> root_;
};

#endif /* TRIE_HPP_96C08F53_5BC8_4B0D_AEE9_188291ED1D25 */
