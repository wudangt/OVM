import ovm
from ovm import expr

def test_const():
    x = expr.ConstExpr(1)
    x + 1
    print(x)

test_const()
