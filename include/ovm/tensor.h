/*!
 *  Copyright (c) 2016 by Contributors
 * \file tensor.h
 * \brief Dataflow tensor object
 */
#ifndef OVM_TENSOR_H_
#define OVM_TENSOR_H_

#include "./expr.h"

namespace ovm {

class Tensor {
 private:
  /*! \brief The shape of the tensor */
  /*! \brief source expression */
  Expr src_expr;
};


}  // namespace ovm
#endif  // OVM_TENSOR_H_
