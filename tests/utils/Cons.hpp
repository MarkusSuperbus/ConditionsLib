#include "ConditionsLib/enumeration_algorithm/BruteForce.hpp"

namespace testing::utils {

/// Class for creating trees using a convenient syntax.
struct Cons {
private:
  struct PrivateMarker {};

public:
  using ConsPtr = std::unique_ptr<Cons>;
  ConsPtr left_;
  ConsPtr right_;
  uint64_t root_;
  /// Internal constructor of a lisp-like "cons" cell: a \p root label together
  /// with two subtrees \p left and \p right. Both parameters may be empty, but
  /// trees derived form VBFs are only valid if either both are empty or both
  /// are not.
  Cons(PrivateMarker, uint64_t root, ConsPtr &&left, ConsPtr &&right)
      : root_{root}, left_{std::move(left)}, right_{std::move(right)} {}

  /// Create a tree with \p root and a \p left and \p right subtree.
  static auto cons(uint64_t root, ConsPtr &&left, ConsPtr &&right)
      -> std::unique_ptr<Cons>;

  /// Create a leaf with \p label (the subtrees are null pointers).
  static auto leaf(uint64_t label) -> ConsPtr;

  /// Check if this is a leaf: both children are null pointers.
  auto IsLeaf() const -> bool;

  /// Derive Cons representation from VectorialBooleanFunction.
  static auto FromVbf(BruteForce::BinaryDecisionTreePointer other) -> ConsPtr;

  /// Compare for equality: the two shapes and all labels are identical.
  auto operator==(const Cons &other) const -> bool;
};

// Expose functions for construction in a more convenient way
// E.g., using namespace testing::utils, you can just write cons instead of
// Cons::cons

/// Create a tree with \p root and a \p left and \p right subtree.
auto cons(uint64_t root, Cons::ConsPtr &&left, Cons::ConsPtr &&right)
    -> Cons::ConsPtr;

/// Create a leaf with \p label (the subtrees are null pointers).
auto leaf(uint64_t label) -> Cons::ConsPtr;

/// GoogleTest function for pretty-printing arguments on error
void PrintTo(const Cons::ConsPtr &foo, std::ostream *os);

/// GoogleTest function for pretty-printing arguments on error
void PrintTo(const Cons &foo, std::ostream *os);

} // namespace testing::utils
