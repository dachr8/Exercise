package A;

import source.Base;
import B.B;

public final class A {
    private int[] intArray;
    private int size;
    private B boss;

    public A() {
        intArray = new int[1];
    }

    public A(int size, B boss) {
        Base ba = new Base();

        this.size = size;
        this.boss = boss;
        intArray = new int[size];
        for (int i = 0; i < size; ++i)
            intArray[0] = ba.ran();
    }

    // 实现了被聚合类对象反向访问聚合类对象
    public int getFromBoss() {
        return boss.getA(0).getA();
    }

    public int getA() {
        return intArray[0];
    }

    public void setA(int n) {
        intArray[0] = n;
    }

    public int getSize() {
        return size;
    }
}
