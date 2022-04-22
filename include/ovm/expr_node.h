/*!
 *  Copyright (c) 2016 by Contributors
 * \file expr_node.h
 * \brief Defines the expression nodes in AST.
 */
#ifndef OVM_EXPR_NODE_H_
#define OVM_EXPR_NODE_H_

#include <string>
#include "./domain.h"
#include "./tensor.h"
#include "./expr.h"


namespace ovm {
/*! \brief variable node for symbolic variables */
class VarNode : public ExprNode {
 public:
  /*! \brief hint name of the variable */
  std::string name;
  /*! \brief constructor */
  VarNode() {
    node_type_ = kVarNode;
  }
  const char* type_key() const override {
    return "VarNode";
  }
  void VisitAttrs(AttrVisitor* visitor) override {
    visitor->Visit("name", &name);
  }
};

/*! \brief integer constant node */
class IntNode : public ExprNode {
 public:
  /*! \brief the value field */
  int64_t value;
  /*! \brief constructor */
  IntNode() {
    node_type_ = kIntNode;
    dtype_ = kInt32;
  }
  const char* type_key() const override {
    return "IntNode";
  }
  void VisitAttrs(AttrVisitor* visitor) override {
    visitor->Visit("value", &value);
  }
};

/*! \brief float constant node */
class FloatNode : public ExprNode {
 public:
  /*! \brief the value field */
  double value;
  /*! \brief constructor */
  FloatNode() {
    node_type_ = kFloatNode;
    dtype_ = kFloat32;
  }
  const char* type_key() const override {
    return "IntNode";
  }
  void VisitAttrs(AttrVisitor* visitor) override {
    visitor->Visit("value", &value);
  }
};

/*! \brief Unary mapping operator */
class UnaryOpNode : public ExprNode {
 public:
  /*! \brief The operator */
  const UnaryOp* op;
  /*! \brief The source expression */
  Expr src;
  /*! \brief constructor */
  UnaryOpNode() {
    node_type_ = kUnaryOpNode;
  }
  const char* type_key() const override {
    return "UnaryOpNode";
  }
  void Verify() const override {
    CHECK_EQ(dtype_, src.dtype());
  }
  void VisitAttrs(AttrVisitor* visitor) override {
    visitor->Visit("op", &op);
  }
  void VisitNodeRefFields(FNodeRefVisit fvisit) override {
    fvisit("src", &src);
  }
};

/*! \brief Binary mapping operator */
struct BinaryOpNode : public ExprNode {
 public:
  /*! \brief The operator */
  const BinaryOp* op;
  /*! \brief The left operand */
  Expr lhs;
  /*! \brief The right operand */
  Expr rhs;
  /*! \brief constructor, do not use constructor */
  BinaryOpNode() {
    node_type_ = kBinaryOpNode;
  }
  BinaryOpNode(const BinaryOp* op, Expr lhs, Expr rhs)
      : op(op), lhs(lhs), rhs(rhs) {
    node_type_ = kBinaryOpNode;
    dtype_ = lhs.dtype();
  }
  const char* type_key() const override {
    return "BinaryOpNode";
  }
  void Verify() const override {
    CHECK_EQ(dtype_, lhs.dtype());
    CHECK_EQ(dtype_, rhs.dtype());
  }
  void VisitAttrs(AttrVisitor* visitor) override {
    visitor->Visit("op", &op);
  }
  void VisitNodeRefFields(FNodeRefVisit fvisit) override {
    fvisit("lhs", &lhs);
    fvisit("rhs", &rhs);
  }
};
}  // namespace ovm

#endif  // OVM_EXPR_NODE_H_
