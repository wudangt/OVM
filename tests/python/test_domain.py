import ovm

def test_range_infer():
    x = ovm.Var('x')
    y = ovm.Var('y')
    t = ovm.Var('t')
    z = x + y + t
    zr = ovm.infer_range(z, {x: ovm.Range(10, 20), y : ovm.Range(10, 11)})
    assert str(zr) == "((t0 + 20), (t0 + 30))"

def test_tensor_dom_infer():
    A = ovm.Tensor(2, name='A')
    B = ovm.Tensor(2, name='B')
    T = ovm.Tensor(3, lambda i, j, k: A(i, k) * B(j, k),
                   shape=(A.shape[0], B.shape[0], A.shape[1]))
    rd = ovm.RDom(ovm.Range(A.shape[1]))
    C = ovm.Tensor(2, lambda i, j: ovm.reduce_sum(T(i, j, rd.index[0]), rdom=rd),
                   shape=(A.shape[0], B.shape[0]))

    cdom = [ovm.Range(0, 10), ovm.Range(1, 11)]
    tdom = C.infer_input_domains(cdom, inputs=[T])[T]
    assert str(tdom[0]) == "(0, 10)"


if __name__ == "__main__":
    test_range_infer()
    test_tensor_dom_infer()
