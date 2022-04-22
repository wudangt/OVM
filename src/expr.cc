/*!
 *  Copyright (c) 2016 by Contributors
 * \file expr.cc
 */
#include <ovm/expr.h>
#include <ovm/op.h>
#include <ovm/expr_node.h>

namespace ovm {

Var::Var(std::string name, DataType dtype) {
  auto node_ = std::make_shared<VarNode>();
  node_->name = std::move(name);
  node_->dtype_ = dtype;
}

Expr IntConstant(int64_t value) {
  auto nptr = std::make_shared<IntNode>();
  nptr->value = value;
  return Expr(std::move(nptr));
}

Expr FloatConstant(double value) {
  auto nptr = std::make_shared<FloatNode>();
  nptr->value = value;
  return Expr(std::move(nptr));
}

Expr operator+(Expr lhs, Expr rhs) {
  auto nptr = std::make_shared<BinaryOpNode>(AddOp::Get(), lhs, rhs);
  nptr->Verify();
  return Expr(std::move(nptr));
}

}  // namespace ovm
