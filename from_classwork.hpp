#include <tuple>

template< class T >
struct BiTree
{
  T val;
  BiTree< T > *lt, *rt, *parent;
};

template< class T >
BiTree< T >* nextAscending(BiTree< T >* root)
{
  if (!root)
  {
    return nullptr;
  }
  BiTree< T >* next = root;
  if (next->rt)
  {
    next = next->rt;
    while (next->lt)
    {
      next = next->lt;
    }
  }
  else
  {
    BiTree< T >* parent;
  }
}

enum Dir
{
  fall_left,
  parent
};

template< class T >
std::pair< size_t, BiTree< T >* > fallLeft(BiTree< T >* root)
{
  size_t path = 0;
  while (root->lt)
  {
    root = root->lt;
    path++;
  }
  return {path, root};
}

template< class T >
std::pair< size_t, BiTree< T >* > Parent(BiTree< T >* root)
{
  if (!root) return {0, nullptr};
  size_t path = 0;
  BiTree< T >* parent = root->parent;
  while (parent && parent->lt != root)
  {
    root = parent;
    parent = root->parent;
    path++;
  }
  return {path, parent};
}

template< class T >
std::tuple< Dir, size_t, BiTree< T >* > nextStruct(BiTree< T >* root)
{
  if (root->rt)
  {
    auto result = fallLeft(root->rt);
    return {Dir::fall_left, result.first, result.second};
  }
  auto result = Parent(root);
  return {Dir::parent, result.first, result.second};
}

template< class T >
bool isEqualStruct(BiTree< T >* lhs, BiTree< T >* rhs)
{
  auto lhs_begin = fallLeft(lhs);
  auto rhs_begin = fallLeft(rhs);
  if (lhs_begin.first != rhs_begin.first)
  {
    return false;
  }
  auto ln = nextStruct(lhs_begin.second);
  auto rn = nextStruct(rhs_begin.second);
  while (std::get< 0 >(ln) == std::get< 0 >(rn) && std::get< 1 >(ln) == std::get< 1 >(rn) && std::get< 2 >(ln) && std::get< 2 >(rn))
  {
    ln = nextStruct(std::get< 2 >(ln));
    rn = nextStruct(std::get< 2 >(rn));
  }
  return ln == rn;
}

template< class T >
bool includedSructStart(BiTree< T >* lhs_root, BiTree< T >* pattern)
{
  auto next_pattern = nextStruct(pattern);
  std::pair< size_t, BiTree< T >* > next_lhs;
  if (std::get< 0 >(next_pattern) == Dir::fall_left)
  {
    next_lhs = fallLeft(lhs_root);
  }
  else
  {
    next_lhs = Parent(lhs_root);
  }
  while (std::get< 1 >(next_pattern) == std::get< 1 >(next_lhs) && std::get< 2 >(next_pattern) && next_lhs.second)
  {
    if (std::get< 0 >(next_pattern) == Dir::fall_left)
    {
      if (next_lhs.second->rt)
      {
        next_lhs = fallLeft(next_lhs.second->rt);
      }
      else
      {
        return false;
      }
    }
    else
    {
      next_lhs = Parent(next_lhs.second);
    }
  }
  return !std::get< 2 >(next_pattern) && std::get< 1 >(next_pattern) == next_lhs.first;
}

template< class T >
bool includedStruct(BiTree< T >* lhs, BiTree< T >* pattern)
{
  pattern = fallLeft(pattern).second;
  lhs = fallLeft(lhs).second;
  while (lhs)
  {
    if (includedSructStart(lhs, pattern))
    {
      return true;
    }
    lhs = std::get< 2 >(nextStruct(lhs));
  }
  return false;
}
