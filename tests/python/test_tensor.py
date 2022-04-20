import ovm

def test_tensor():
    A = ovm.Tensor(2, name='A')
    B = ovm.Tensor(2, name='B')
    T = ovm.Tensor(3, lambda i, j, k: A(i, k) * B(j, k),
                   shape=(A.shape[0], B.shape[0], A.shape[1]))
    print(ovm.format_str(T.expr))

def test_tensor_inputs():
    A = ovm.Tensor(2, name='A')
    B = ovm.Tensor(2, name='B')
    T = ovm.Tensor(3, lambda i, j, k: A(i, k) * B(j, k),
                   shape=(A.shape[0], B.shape[0], A.shape[1]))
    assert(T.input_tensors() == [A, B])

def test_tensor_reduce():
    A = ovm.Tensor(2, name='A')
    B = ovm.Tensor(2, name='B')
    T = ovm.Tensor(3, lambda i, j, k: A(i, k) * B(j, k),
                   shape=(A.shape[0], B.shape[0], A.shape[1]))
    rd = ovm.RDom(ovm.Range(A.shape[1]))
    C = ovm.Tensor(2, lambda i, j: ovm.reduce_sum(T(i, j, rd.index[0]), rdom=rd),
                   shape=(A.shape[0], B.shape[0]))
    print(ovm.format_str(C.expr))

if __name__ == "__main__":
    test_tensor_inputs()
    test_tensor_reduce()
