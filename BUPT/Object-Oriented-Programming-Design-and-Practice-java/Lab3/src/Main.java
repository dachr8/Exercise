import source.Base;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);

        System.out.println("基类：B b = new B()");
        B b = new B();
        b.showallclassname();
        b.showfunname();
        System.out.println(" b.getAnInt():" + b.getAnInt());
        System.out.println("标准输入修改成员 b.setAnInt:");
        b.setAnInt(cin.nextInt());
        System.out.println("访问成员 b.getAnInt(true):" + b.getAnInt());
        System.out.println();

        System.out.println("派生类：A a = new A()");
        A a = new A();
        a.showallclassname();
        a.showfunname();
        System.out.println("访问派生类成员 a.getAnInt(false):" + a.getAnInt(false));
        System.out.println("访问基类成员 a.getAnInt(true):" + a.getAnInt(true));
        System.out.println("标准输入修改基类成员 a.setAnInt(cin.nextInt(),false):");
        a.setAnInt(cin.nextInt(),true);
        System.out.println("访问派生类成员 a.getAnInt(false):" + a.getAnInt(false));
        System.out.println("访问基类成员 a.getAnInt(true):" + a.getAnInt(true));
        System.out.println();

        System.out.println("B c= new A();");
        B c= new A();
        c.showallclassname();
        c.showfunname();
        System.out.println(" c.getAnInt():" + c.getAnInt());
        System.out.println("标准输入修改成员 c.setAnInt:");
        c.setAnInt(cin.nextInt());
        System.out.println("访问成员 c.getAnInt():" + c.getAnInt());
    }
}
