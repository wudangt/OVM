import ovm

def test_tensor():
    A = ovm.Tensor(2, name='A')
    B = ovm.Tensor(2, name='B')
    T = ovm.Tensor(3, lambda i, j, k: A(i, k) * B(j, k))
    print(ovm.format_str(T.expr))

if __name__ == "__main__":
    test_tensor()
