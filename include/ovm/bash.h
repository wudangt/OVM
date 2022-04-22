/*!
 *  Copyright (c) 2016 by Contributors
 * \file base.h
 * \brief Defines the base data structure
 */
#ifndef OVM_BASE_H_
#define OVM_BASE_H_

#include <dmlc/logging.h>
#include <dmlc/registry.h>
#include <string>
#include <memory>
#include <functional>
#include <typeinfo>


namespace ovm {

// forward declaration
class Node;
class NodeRef;
class UnaryOp;
class BinaryOp;

/*! \brief list of all supported data types */
enum DataType {
  kUnknown,
  kInt32,
  kFloat32
};

/*!
 * \brief List of subset node types used for quick runtime switch.
 *
 * \note The value of NodeType is not used for serialization type_key is used instead.
 * \note is_type  and type_key can be used to do type checking for all types
 * \note kOtherNodes could mean more than one node type.
 */
enum NodeType {
  kVarNode,
  kIntNode,
  kFloatNode,
  kUnaryOpNode,
  kBinaryOpNode,
  kReduceNode,
  kTensorReadNode,
  kOtherNodes
};

/*!
 * \brief Visitor class to each node content.
 *  The content is going to be called for each field.
 */
class AttrVisitor {
 public:
//! \cond Doxygen_Suppress
  virtual void Visit(const char* key, double* value) = 0;
  virtual void Visit(const char* key, int64_t* value) = 0;
  virtual void Visit(const char* key, DataType* value) = 0;
  virtual void Visit(const char* key, std::string* value) = 0;
  virtual void Visit(const char* key, const UnaryOp** value) = 0;
  virtual void Visit(const char* key, const BinaryOp** value) = 0;
//! \endcond
};

/*!
 * \brief A function to be applied when visit each NodeRef Field.
 * \param ref The child to be visited.
 */
using FNodeRefVisit = std::function<void(const char* key, NodeRef* ref)>;

/*!
 * \brief base class of node container in DSL AST.
 *  All object's internal is stored as std::shared_ptr<Node>
 */
class Node {
 public:
  /*! \brief virtual destructor */
  virtual ~Node();
  /*! \return The unique type key of the node */
  virtual const char* type_key() const = 0;
  /*! \brief verify the correctness of node struct after it get mutated by visitor */
  virtual void Verify() const {}
  /*!
   * \brief Apply visitor to each field of the Node
   *  Visitor could mutate the content of the node.
   *  override if Node contains attribute fields.
   * \param visitor The visitor
   */
  virtual void VisitAttrs(AttrVisitor* visitor) {}
  /*!
   * \brief Apply visitor to each field of the Node
   *  Visitor could mutate the content of the node.
   *  override if Node contains NodeRefFields.
   * \param visitor The visitor
   */
  virtual void VisitNodeRefFields(FNodeRefVisit visitor) {}
  /*!
   * \tparam NodeType the type to be checked.
   * \return whether the stored type is node type
   */
  template<typename TNode>
  inline bool is_type() const;
  /*! \return the node type */
  inline NodeType node_type() const;

 protected:
  // node ref can see this
  friend class NodeRef;
  /*! \brief the node type enum */
  NodeType node_type_{kOtherNodes};
};

/*! \brief base class of all node reference object */
class NodeRef {
 public:
  /*!
   * \return typed pointer of the node
   * \tparam TNode the type of the node.
   */
  template<typename TNode>
  inline const TNode* Get() const;
  /*! \return wheyjer the expression is null */
  inline bool is_null() const;

 protected:
  NodeRef() = default;
  explicit NodeRef(std::shared_ptr<Node> node) : node_(node) {}
  /*! \brief the internal node */
  std::shared_ptr<Node> node_;
};

/*! \brief typedef the factory function of data iterator */
using NodeFactory = std::function<std::shared_ptr<Node> ()>;

/*!
 * \brief Registry entry for DataIterator factory functions.
 */
struct NodeFactoryReg
    : public dmlc::FunctionRegEntryBase<NodeFactoryReg,
                                        NodeFactory> {
};

#define OVM_REGISTER_NODE_TYPE(TypeName)                                \
  DMLC_REGISTRY_REGISTER(::ovm::NodeFactoryReg, NodeFactoryReg, TypeName) \
  .set_body([]() { return std::make_shared<TypeName>(); })

// implementations of inline functions after this
inline NodeType Node::node_type() const {
  return node_type_;
}

template<typename TNode>
inline bool Node::is_type() const {
  const std::type_info& tinfo = typeid(*this);
  if (&typeid(TNode) == &tinfo) return true;
  return typeid(TNode) == tinfo;
}

template<typename TNode>
inline const TNode* NodeRef::Get() const {
  CHECK(node_->is_type<TNode>())
      << " type inconsistent, expected " << typeid(TNode).name()
      << " given " << typeid(*this).name();
  return static_cast<const TNode*>(node_.get());
}

inline bool NodeRef::is_null() const {
  return node_.get() == nullptr;
}

}  // namespace ovm
#endif  // OVM_BASE_H_
