/*!
 *  Copyright (c) 2016 by Contributors
 * \file expr_node.cc
 */
#include <ovm/expr_node.h>
#include <memory>

namespace ovm {

OVM_REGISTER_NODE_TYPE(VarNode);
OVM_REGISTER_NODE_TYPE(IntNode);
OVM_REGISTER_NODE_TYPE(FloatNode);
OVM_REGISTER_NODE_TYPE(UnaryOpNode);
OVM_REGISTER_NODE_TYPE(BinaryOpNode);

}  // namespace ovm
