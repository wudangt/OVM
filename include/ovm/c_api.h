/*!
 *  Copyright (c) 2016 by Contributors
 * \file c_api.h
 * \brief C API of OVM DSL
 */
#ifndef OVM_C_API_H_
#define OVM_C_API_H_

#ifdef __cplusplus
#define OVM_EXTERN_C extern "C"
#else
#define OVM_EXTERN_C
#endif

/*! \brief OVM_DLL prefix for windows */
#ifdef _WIN32
#ifdef OVM_EXPORTS
#define OVM_DLL OVM_EXTERN_C __declspec(dllexport)
#else
#define OVM_DLL OVM_EXTERN_C __declspec(dllimport)
#endif
#else
#define OVM_DLL OVM_EXTERN_C
#endif

/*! \brief handle to node creator */
typedef void* NodeCreatorHandle;
/*! \brief handle to node */
typedef void* NodeHandle;

OVM_DLL int OVMNodeCreatorGet(const char* node_type,
                              NodeCreatorHandle *handle);

OVM_DLL int OVMNodeCreate(NodeCreatorHandle handle,
                          int num_child_ref,
                          const char* child_ref_keys,
                          NodeHandle* child_node_refs,
                          int num_attrs,
                          const char* attr_keys,
                          const char* attr_vals,
                          NodeHandle* handle);

OVM_DLL int OVMNodeGetAttr(const char* key,
                           const char** value);

OVM_DLL int OVMNodeGetChildNodeRef(const char* key,
                                   NodeHandle* out);

#endif  // OVM_C_API_H_
