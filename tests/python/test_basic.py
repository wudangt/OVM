import ovm
from ovm import expr


def test_bind():
    x = ovm.Var('x')
    y = x + 1
    z = ovm.bind(y, {x: ovm.const(10) + 9})
    assert ovm.format_str(z) == '((10 + 9) + 1)'


def test_basic():
    a = ovm.Var('a')
    b = ovm.Var('b')
    c =  a + b
    assert ovm.format_str(c) == '(%s + %s)' % (a.name, b.name)


if __name__ == "__main__":
    test_basic()
    test_bind()
