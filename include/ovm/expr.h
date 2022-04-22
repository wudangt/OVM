/*!
 *  Copyright (c) 2016 by Contributors
 * \file expr.h
 * \brief Defines the expressions in AST.
 */
#ifndef OVM_EXPR_H_
#define OVM_EXPR_H_

#include <type_traits>
#include "./base.h"

namespace ovm {
// forward declare Expr
class Expr;

/*!
 * \brief create a constant expression
 * \tparam T the value type
 * \param value The value to the constant.
 * \return The created expression
 */
template<typename T,
         typename = typename std::enable_if<std::is_arithmetic<T>::value>::type >
inline Expr constant(T value);

/*!
 * \brief a expression type, holds a ref to root of an AST
 */
class Expr : public NodeRef {
 public:
  /*! \brief default constructor */
  Expr() = default;
  /*!
   * \brief copy constructor
   * \param other the input
   */
  Expr(const Expr& other) = default;  // NOLINT(*)
  /*!
   * \brief move constructor
   * \param other the input
   */
  Expr(Expr&& other) = default;  // NOLINT(*)
  /*!
   * \brief assign operator.
   * \param other the input.
   * \return reference to self
   */
  Expr& operator=(const Expr& other) = default;
  /*!
   * \brief assign move operator.
   * \param other the input.
   * \return reference to self
   */
  Expr& operator=(Expr&& other) = default;
  /*!
   * \brief constructor from constant value
   * \param value the constant value
   * \tparam T The constant type
   */
  template<typename T,
           typename = typename std::enable_if<std::is_arithmetic<T>::value>::type >
  Expr(T value) {  // NOLINT(*)
    *this = std::move(constant<T>(value));
  }
  /*!
   * \brief constructor from node pointer
   * \param nptr Another node shared pointer
   */
  explicit Expr(std::shared_ptr<Node> nptr) : NodeRef(nptr) {}
  /*! \return the expression type of the expression  */
  inline DataType dtype() const;
};

/*! \brief Variable class */
class Var : public Expr {
 public:
  Var(std::string name="", DataType dtype=kInt32);  // NOLINT(*)
};

/*! \brief */
Expr IntConstant(int64_t value);
Expr FloatConstant(int64_t value);
Expr operator+(Expr lhs, Expr rhs);

/*! \brief base of expression node */
class ExprNode : public Node {
 public:
  /*! \brief type of data stored in expression */
  DataType dtype_{kUnknown};
};

// inline implementations
inline DataType Expr::dtype() const {
  return static_cast<const ExprNode*>(node_.get())->dtype_;
}
template<typename T,
         typename = typename std::enable_if<std::is_arithmetic<T>::value>::type >
inline Expr constant(T value) {
  if (std::is_integral<T>::value) {
    return IntConstant(static_cast<int64_t>(value));
  } else {
    return FloatConstant(static_cast<double>(value));
  }
}

}  // namespace ovm
#endif  // OVM_EXPR_H_
