import B.B;
import source.Base;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        System.out.println("输入被聚合类的size:");
        Scanner scanner = new Scanner(System.in);
        B b = new B(scanner.nextInt());


        Base base = new Base();
        base.showallclassname(b);
        base.showfunname(b);

        base.showallclassname(b.getA(0));
        base.showfunname(b.getA(0));

        for (int i = 0; i < b.getSize(); ++i)
            System.out.println("b.getA(" + i + ").getA():" + b.getA(i).getA());
        b.setA(0, base.ran());
        System.out.println("b.setA(0, base.ran())");

        System.out.println("这次使用了被聚合类对象反向访问聚合类对象读取");
        System.out.println("b.getA(0).getFromBoss():" + b.getA(0).getFromBoss());
        System.out.println("读取结果正确");
        System.out.println("b.getA(0).getA():" + b.getA(0).getA());

        System.out.println();
        System.out.println("size = 99999时:");
        B bb = new B(99999);
        //内存开销很大
    }
}
