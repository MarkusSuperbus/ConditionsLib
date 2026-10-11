#include "Cons.hpp"

namespace testing::utils {

auto Cons::cons(uint64_t root, ConsPtr &&left, ConsPtr &&right)
    -> std::unique_ptr<Cons> {
  return std::make_unique<Cons>(PrivateMarker{}, root, std::move(left),
                                std::move(right));
}

auto Cons::leaf(uint64_t label) -> ConsPtr {
  return std::make_unique<Cons>(PrivateMarker{}, label, nullptr, nullptr);
}

auto Cons::IsLeaf() const -> bool {
  return left_ == nullptr && right_ == nullptr;
}

auto Cons::FromVbf(BruteForce::BinaryDecisionTreePointer other) -> ConsPtr {
  if (other->IsLeaf()) {
    return Cons::leaf(other->value_);
  }
  return Cons::cons(other->value_, FromVbf(std::move(other->left_)),
                    FromVbf(std::move(other->right_)));
}

auto Cons::operator==(const Cons &other) const -> bool {
  const bool rootEqual = root_ == other.root_;
  if (!rootEqual) {
    return false;
  }
  const bool leftEqual =
      (left_ == nullptr && other.left_ == nullptr) || (*left_ == *other.left_);
  if (!leftEqual) {
    return false;
  }
  const bool rightEqual = (right_ == nullptr && other.right_ == nullptr) ||
                          (*right_ == *other.right_);
  return rightEqual;
}

auto cons(uint64_t root, Cons::ConsPtr &&left, Cons::ConsPtr &&right)
    -> Cons::ConsPtr {
  return Cons::cons(root, std::move(left), std::move(right));
}

auto leaf(uint64_t label) -> Cons::ConsPtr { return Cons::leaf(label); }

void PrintTo(const Cons::ConsPtr &foo, std::ostream *os) {
  if (foo == nullptr) {
    *os << "nil";
  } else {
    PrintTo(*foo, os);
  }
}

void PrintTo(const Cons &foo, std::ostream *os) {
  if (foo.IsLeaf()) {
    *os << foo.root_;
    return;
  } else {
    *os << "(cons ";
    PrintTo(foo.left_, os);
    *os << " ";
    PrintTo(foo.right_, os);
    *os << ")";
  }
}

;

} // namespace testing::utils
