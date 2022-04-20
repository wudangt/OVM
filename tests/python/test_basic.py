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


def test_simplify():
    a = ovm.Var('a')
    b = ovm.Var('b')
    e1 = a * (2 + 1) + b * 1
    e2 = a * (2 + 1) - b * 1
    e3 = ovm.max(a * 3.3 + 5, 3 + 3.3 * a)
    e4 = a - a
    assert ovm.format_str(ovm.simplify(e1)) == '((%s * 3) + %s)' % (a.name, b.name)
    assert ovm.format_str(ovm.simplify(e2)) == '((%s * 3) + (%s * -1))' % (a.name, b.name)
    assert ovm.format_str(ovm.simplify(e3)) == '((%s * 3.3) + 5)' % (a.name)
    assert ovm.format_str(ovm.simplify(e4)) == '0'

if __name__ == "__main__":
    test_simolify()
    test_basic()
    test_bind()
    
