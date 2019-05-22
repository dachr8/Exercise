package B;

import source.Base;
import A.A;

public class B {
    private int[] intArray;
    private A[] aArray;
    private int size;
    private A b;

    public B() {
        intArray = new int[1];
    }

    public B(int size) {
        if (size > 0) {
            Base ba = new Base();

            this.size = size;
            intArray = new int[size];
            intArray[0] = ba.ran();
            aArray = new A[size + 1];
            for (int i = 0; i < size; ++i)
                aArray[i] = new A(ba.ran() + 1, this);

            ba.getmem(1);
        }
    }


    public A getA(int i) {
        return aArray[i];
    }

    public void setA(int i, int n) {
        aArray[i].setA(n);
    }

    public int getSize() {
        return size;
    }
}
