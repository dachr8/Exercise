import com.sun.org.apache.xpath.internal.operations.Bool;

public class A extends B {
    private int anInt;

    public A() {
        super();
        this.anInt = super.ran();
    }

    public int getAnInt(boolean boss) {
        return boss ? super.getAnInt() : this.anInt;
    }

    public void setAnInt(int anInt, boolean boss) {
        if (boss)
            super.setAnInt(anInt);
        else
            this.anInt = anInt;
    }
}
// 观察结论:
//          在main函数中以A()构造派生类A后，在A()中通过super()函数构造了基类B，在B()中通过super()函数构造了基类Base
//          构造泛化型多态结构的成员函数列表小，内存开销也较小
//          基类与派生类以及对应覆盖成员的声明符合要求与语法规范
//          多态方法访问两个类对象的设计符合要求与语法规范
//          访问靶向程序呈现的标准输出内容与设计吻合
//